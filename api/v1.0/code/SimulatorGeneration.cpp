#include "../modules/MaxRectsBinPack.h"
#include "class_generate_image.hpp"
#include "stdafx.h"


int main(int argc, char **argv)
{
	GenerateImage m_image_generate;
	//get path form config.txt
	m_image_generate.get_objects_info();

	int n_img_num;
	int n_src_w, n_src_h, n_rot_w, n_rot_h;
	double d_sin_theta, d_cos_theta;
	bool b_rot_flag;
	double d_center_x, d_center_y, d_width, d_height;
	//double d_magni_obj = 1.;
	//double p1[2] = { 0., 0. }, p2[2] = { 0., 0. }, p3[2] = { 0., 0. }, p4[2] = { 0., 0. };
	//double d_leftup_x, d_leftup_y, d_rightup_x, d_rightup_y, d_rightdown_x, d_rightdown_y, d_leftdown_x, d_leftdown_y;
	//
	int iter;
	int n_iter_num;
	int n_start_num;
	std::cout << "Please Enter Number Of Pictures:";
	std::cin >> n_iter_num;
	std::cout << "Please Enter Start Number:";
	std::cin >> n_start_num;

	for (iter = 0; iter < n_iter_num; iter++)
	{
		int n_name_num = n_start_num + iter;
		m_image_generate.read_objects_images();
		std::cout << "ImageProducer Init Done" << std::endl;
		//
		using namespace rbp;

		// Create a bin to pack to, use the bin size from command line.
		MaxRectsBinPack bin;
		int binWidth = m_image_generate._mat_background_bin.cols;
		int binHeight = m_image_generate._mat_background_bin.rows;
		// convert to double for coordinate computation
		double d_backgroundWidth = (double)m_image_generate._mat_background.cols;
		double d_backgroundHeight = (double)m_image_generate._mat_background.rows;
		//
		//std::printf("Initializing bin to size %d x %d.\n", binWidth, binHeight);
		//std::printf("Initializing background to size %d x %d.\n", background.cols, background.rows);
		bin.Init(binWidth, binHeight);

		//save the groundtruth of objects to .txt
		std::fstream output_stream;//define output_stream
		//然后用 output_stream的open函数打开一个文件， ios::out 表示输出,ios::app表示输出到文件尾。
		output_stream.open(m_image_generate._s_labels_path + std::to_string(n_name_num) + ".txt", std::ios::out | std::ios::app);

		// Pack every rectangles.
		for (int i = 0; i < m_image_generate._n_obj_num; i++)
		{	
			cv::Mat mat_rot_matrix;
			//rand_od_n(flag_rotate, 90);
			int n_rot_degree = rand() % 90 + 1;
			b_rot_flag = TRUE;
			int degree = n_rot_degree;
			n_src_w = m_image_generate._vec_mat_obj[i].cols;
			n_src_h = m_image_generate._vec_mat_obj[i].rows;
			//rotate
			m_image_generate.objects_get_rotate_image(m_image_generate._vec_mat_obj[i], m_image_generate._vec_mat_obj[i], degree, 0, d_sin_theta, d_cos_theta, n_rot_w, n_rot_h, mat_rot_matrix);
			m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p1[2 * i], m_image_generate._vec_d_p1[2 * i + 1], mat_rot_matrix, m_image_generate._vec_d_p1[2 * i], m_image_generate._vec_d_p1[2 * i + 1]);
			m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p2[2 * i], m_image_generate._vec_d_p2[2 * i + 1], mat_rot_matrix, m_image_generate._vec_d_p2[2 * i], m_image_generate._vec_d_p2[2 * i + 1]);
			m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p3[2 * i], m_image_generate._vec_d_p3[2 * i + 1], mat_rot_matrix, m_image_generate._vec_d_p3[2 * i], m_image_generate._vec_d_p3[2 * i + 1]);
			m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p4[2 * i], m_image_generate._vec_d_p4[2 * i + 1], mat_rot_matrix, m_image_generate._vec_d_p4[2 * i], m_image_generate._vec_d_p4[2 * i + 1]);
			//
			int rectWidth = m_image_generate._vec_mat_obj[i].cols;
			int rectHeight = m_image_generate._vec_mat_obj[i].rows;
			//std::printf("Packing rectangle of size %d x %d: ", rectWidth, rectHeight);

			// Perform the packing.
			MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = MaxRectsBinPack::RectBestShortSideFit; // This can be changed individually even for each rectangle packed.
			rbp::Rect packedRect = bin.Insert(rectWidth, rectHeight, heuristic);

			// Test success or failure.
			if (packedRect.height > 0)
			{
				//std::printf("Packed to (x,y)=(%d,%d), (w,h)=(%d,%d). Free space left: %.2f%%\n", packedRect.x, packedRect.y, packedRect.width, packedRect.height, 100.f - bin.Occupancy()*100.f);
				cv::Mat mat_roi = m_image_generate._mat_background_bin(cv::Rect(packedRect.x, packedRect.y, packedRect.width, packedRect.height));
				//m_image_generate._vec_mat_roi[i];
				//if spin
				if (m_image_generate._vec_mat_obj[i].cols == packedRect.width)
				{
					//cv::addWeighted(vec_mat_roi[i], 0.0, vec_mat_obj[i], 1, 0, vec_mat_roi[i]);
					if (b_rot_flag == 1)
					{
						m_image_generate.fill_objects_images(m_image_generate._vec_mat_obj[i], m_image_generate._mat_background_bin,packedRect.x,packedRect.y);
					}
					m_image_generate.objects_get_outer_rect(m_image_generate._vec_d_p1[2 * i], m_image_generate._vec_d_p1[2 * i + 1], m_image_generate._vec_d_p2[2 * i], m_image_generate._vec_d_p2[2 * i + 1], m_image_generate._vec_d_p3[2 * i], m_image_generate._vec_d_p3[2 * i + 1], m_image_generate._vec_d_p4[2 * i], m_image_generate._vec_d_p4[2 * i + 1], d_center_x, d_center_y, d_width, d_height);

					cv::addWeighted(mat_roi, 0.0, m_image_generate._vec_mat_obj[i], 1, 0, mat_roi);
				}
				else // Rotated when packing.
				{
					//
					cv::Mat mat_dst_obj;
					//imshow("obj", vec_mat_obj[i]);
					cv::transpose(m_image_generate._vec_mat_obj[i], mat_dst_obj);
					flip(mat_dst_obj, mat_dst_obj, 1);//右旋90°
					//imshow("mat_dst_obj", mat_dst_obj);
					//cv::addWeighted(vec_mat_roi[i], 0.0, mat_dst_obj, 1, 0, vec_mat_roi[i]);
					if (b_rot_flag == 1)
					{
						m_image_generate.fill_objects_images(mat_dst_obj, m_image_generate._mat_background_bin, packedRect.x, packedRect.y);
					}
					cv::Point2d d_center_point = cv::Point2d(0, 0);
					cv::Mat m_rot_90 = cv::getRotationMatrix2D(d_center_point, -90., 1.);
					m_rot_90.at<double>(0, 0) = 0;
					m_rot_90.at<double>(0, 2) += mat_dst_obj.cols;
					m_rot_90.at<double>(1, 0) = 1.;
					m_rot_90.at<double>(1, 1) = 0.;
					m_rot_90.at<double>(1, 2) = 0.;
					//
					m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p1[2 * i], m_image_generate._vec_d_p1[2 * i + 1], m_rot_90, m_image_generate._vec_d_p1[2 * i], m_image_generate._vec_d_p1[2 * i + 1]);
					m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p2[2 * i], m_image_generate._vec_d_p2[2 * i + 1], m_rot_90, m_image_generate._vec_d_p2[2 * i], m_image_generate._vec_d_p2[2 * i + 1]);
					m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p3[2 * i], m_image_generate._vec_d_p3[2 * i + 1], m_rot_90, m_image_generate._vec_d_p3[2 * i], m_image_generate._vec_d_p3[2 * i + 1]);
					m_image_generate.objects_get_rot_point(m_image_generate._vec_d_p4[2 * i], m_image_generate._vec_d_p4[2 * i + 1], m_rot_90, m_image_generate._vec_d_p4[2 * i], m_image_generate._vec_d_p4[2 * i + 1]);
					//
					m_image_generate.objects_get_outer_rect(m_image_generate._vec_d_p1[2 * i], m_image_generate._vec_d_p1[2 * i + 1], m_image_generate._vec_d_p2[2 * i], m_image_generate._vec_d_p2[2 * i + 1], m_image_generate._vec_d_p3[2 * i], m_image_generate._vec_d_p3[2 * i + 1], m_image_generate._vec_d_p4[2 * i], m_image_generate._vec_d_p4[2 * i + 1], d_center_x, d_center_y, d_width, d_height);

					cv::addWeighted(mat_roi, 0.0, mat_dst_obj, 1, 0, mat_roi);
				}
				// x,y,w,h 
				int x1 = packedRect.x + 500;
				int y1 = packedRect.y + 500;
				// sheet
				d_center_x = (x1 + d_center_x) / d_backgroundWidth;
				d_center_y = (y1 + d_center_y) / d_backgroundHeight;
				d_width = d_width / d_backgroundWidth;
				d_height = d_height / d_backgroundHeight;
				// objects
				double d_obj_x = (x1 + packedRect.width * 0.5) / d_backgroundWidth;
				double d_obj_y = (y1 + packedRect.height * 0.5) / d_backgroundHeight;
				double d_obj_w = packedRect.width / d_backgroundWidth;
				double d_obj_h = packedRect.height / d_backgroundHeight;
				if (m_image_generate._vec_n_label[i] != 2)
				{
					output_stream << 0 << " " << d_obj_x << " " << d_obj_y << " " << d_obj_w << " " << d_obj_h << std::endl;
				}
				//output_stream << n_label_num[i] << " " << d_leftup_x << " " << d_leftup_y << " " << d_rightup_x << " " << d_rightup_y << " " << d_rightdown_x << " " << d_rightdown_y << " " << d_leftdown_x << " " << d_leftdown_y << endl;
				if (d_width != 0 && d_height != 0)
				{
					output_stream << 1 << " " << d_center_x << " " << d_center_y << " " << d_width << " " << d_height << std::endl;
				}
			}
			else
			{
				std::printf("Failed! Could not find a proper position to pack this rectangle into. Skipping this one.\n");
			}
		}
		//
		// put the bin into backgroun
		cv::Mat mat_roi_bin = m_image_generate._mat_background(cv::Rect(500, 500, 1400, 1400));
		cv::addWeighted(mat_roi_bin, 0.0, m_image_generate._mat_background_bin, 1, 0, mat_roi_bin);
		//change the brightness
		double d_brightness_num = std::stod(m_image_generate._s_brightness_num);
		cv::convertScaleAbs(m_image_generate._mat_background, m_image_generate._mat_background, d_brightness_num, 0);
		cv::imwrite(m_image_generate._s_images_path + std::to_string(n_name_num) + ".jpg", m_image_generate._mat_background);
		//
		std::cout<<"Done. All rectangles packed in img_"<< n_name_num<<std::endl;
		//std::system("pause");
		m_image_generate._vec_mat_obj.erase(m_image_generate._vec_mat_obj.begin(), m_image_generate._vec_mat_obj.end());//Warning:vector's size and capacity is different!
		m_image_generate._vec_n_label.erase(m_image_generate._vec_n_label.begin(), m_image_generate._vec_n_label.end());
		//m_image_generate._vec_mat_roi.erase(m_image_generate._vec_mat_roi.begin(), m_image_generate._vec_mat_roi.end());
		m_image_generate._vec_d_p1.erase(m_image_generate._vec_d_p1.begin(), m_image_generate._vec_d_p1.end());
		m_image_generate._vec_d_p2.erase(m_image_generate._vec_d_p2.begin(), m_image_generate._vec_d_p2.end());
		m_image_generate._vec_d_p3.erase(m_image_generate._vec_d_p3.begin(), m_image_generate._vec_d_p3.end());
		m_image_generate._vec_d_p4.erase(m_image_generate._vec_d_p4.begin(), m_image_generate._vec_d_p4.end());
	}
	std::printf("DataSet is ready!,Total %d \n", iter);
	std::system("pause");
	return 0;
}
#ifndef CLASS_GENERATE_IMAGE_HPP_
#define CLASS_GENERATE_IMAGE_HPP_

#include "stdafx.h"

class GenerateImage
{
public:
	GenerateImage()
	{};
	~GenerateImage()
	{};

public:
	int _n_mode_num;
	int _n_obj_num_total;
	int _n_obj_num;

	std::string _s_src_path;
	std::string _s_images_path;
	std::string _s_labels_path;
	std::string _s_brightness_num;

	std::vector<int> _vec_mode_num;
	std::vector<int> _vec_obj_num;
	std::vector<int> _vec_n_label;
	std::vector<double> _vec_d_p1;
	std::vector<double> _vec_d_p2;
	std::vector<double> _vec_d_p3;
	std::vector<double> _vec_d_p4;
	std::vector<cv::Mat> _vec_mat_roi;
	std::vector<cv::Mat> _vec_mat_obj;

	cv::Mat _mat_background_bin, _mat_background;

public:
	void get_objects_info()
	{
		std::string s_dst_path_;
		this->get_txt_data(_s_src_path, "SRC_PATH");
		this->get_txt_data(s_dst_path_, "DST_PATH");
		this->get_txt_data(_s_brightness_num, "BRIGHTNESS");
		_s_images_path = s_dst_path_ + "images\\";
		_s_labels_path = s_dst_path_ + "labels\\";
		std::cout << "输入目录: " << _s_src_path << std::endl;
		std::cout << "输出图片目录：" << _s_images_path << std::endl;
		std::cout << "输出图片亮度：" << _s_brightness_num << std::endl;
		std::cout << "输出标签目录：" << _s_labels_path << std::endl;
		//
		//cv::Mat object;
		//cv::Mat m_rot_matrix;
		//cv::Mat backgroundBin, background;
		//cv::Mat backgroundBin_raw = cv::imread(s_src_path + "bin.jpg");
		//cv::Mat background_raw = cv::imread(s_src_path + "background.jpg");
		//cv::Mat m_sheet = imread(s_src_path + "sheet.jpg");
		//
		std::cout << "Please Enter Mode Number..." << std::endl;
		std::cin >> _n_mode_num;
		//int n_label_num[5] = {4, 6, 2, 2 ,5};
		//p_label_num = new int[n_obj_num];
		//std::vector<int> vec_mode_num(_n_mode_num);
		//
		int n_mode_data;
		std::cout << "Please Enter Mode ..." << std::endl;
		for (int n_mode_iter = 0; n_mode_iter < _n_mode_num; n_mode_iter++)
		{
			std::cin >> n_mode_data;
			_vec_mode_num.push_back(n_mode_data);
			std::cout << "Please Enter Next One..." << std::endl;
		}
		std::cout << "Mode : ";
		for (int n_mode_iter = 0; n_mode_iter < _n_mode_num; n_mode_iter++)
		{
			std::cout << _vec_mode_num[n_mode_iter] << " , ";
		}
		std::cout << "    Total: " << _n_mode_num << std::endl;
		//
		std::cout << "Please Enter Object Number..." << std::endl;
		std::cin >> _n_obj_num_total;
		//std::vector<int> vec_obj_num(_n_obj_num_total);

		std::cout << "Please Enter Object..." << std::endl;
		for (int n_obj_iter = 0; n_obj_iter < _n_obj_num_total; n_obj_iter++)
		{
			int n_obj_data;
			std::cin >> n_obj_data;
			_vec_obj_num.push_back(n_obj_data);
			std::cout << "Please Enter Next One..." << std::endl;
		}
		std::cout << "Object : ";
		for (int n_obj_iter = 0; n_obj_iter < _n_obj_num_total; n_obj_iter++)
		{
			std::cout << _vec_obj_num[n_obj_iter] << " , ";
		}
		std::cout << "    Total: " << _n_obj_num_total << std::endl;
	}

	void read_objects_images()
	{
		cv::Mat mat_object;
		int n_img_num;
		int n_rand_num = rand() % _n_mode_num;
		_n_obj_num = _vec_mode_num[n_rand_num];
		double d_magni_obj = 1.;
		double p1[2] = { 0., 0. }, p2[2] = { 0., 0. }, p3[2] = { 0., 0. }, p4[2] = { 0., 0. };
		//
		for (int j = 0; j < _n_obj_num; j++)
		{
			int n_obj_index = rand() % _n_obj_num_total;
			if (_vec_obj_num[n_obj_index] == 2)
			{
				n_img_num = rand() % 42 + 1;
			}
			else
			{
				n_img_num = rand() % 5 + 1;
			}
			std::string s_image_name = _s_src_path + std::to_string(_vec_obj_num[n_obj_index]) + "_" + std::to_string(n_img_num) + ".jpg";
			mat_object = cv::imread(s_image_name);

			_vec_n_label.push_back(_vec_obj_num[n_obj_index]);
			this->objects_add_sheet_image(mat_object, _s_src_path, p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]);
			this->objects_resize_obj_rand(mat_object, mat_object, d_magni_obj);
			_vec_d_p1.push_back(p1[0] * d_magni_obj);
			_vec_d_p1.push_back(p1[1] * d_magni_obj);
			_vec_d_p2.push_back(p2[0] * d_magni_obj);
			_vec_d_p2.push_back(p2[1] * d_magni_obj);
			_vec_d_p3.push_back(p3[0] * d_magni_obj);
			_vec_d_p3.push_back(p3[1] * d_magni_obj);
			_vec_d_p4.push_back(p4[0] * d_magni_obj);
			_vec_d_p4.push_back(p4[1] * d_magni_obj);
			// every pixels'value +1
			this->objects_add_pixel_value(mat_object, 1);
			_vec_mat_obj.push_back(mat_object);
		}
		cv::Mat mat_background_bin_raw = cv::imread(_s_src_path + "bin.jpg");
		cv::Mat mat_background_raw = cv::imread(_s_src_path + "background.jpg");
		_mat_background_bin = mat_background_bin_raw.clone();
		_mat_background = mat_background_raw.clone();
	}

	void get_txt_data(std::string& p_array_, std::string s_flag_name_)
	{
		std::ifstream in("../Release/configs/config.txt");//
		if (!in)
		{
			std::cout << "No such file named config.txt! ";
			exit(0);
		}
		std::string str_file_content, str_content, str_type, addressLine;
		while (getline(in, str_file_content))
		{
			size_t index = str_file_content.find_first_of(":");
			str_type = str_file_content.substr(0, index);
			str_content = str_file_content.substr(index + 1, str_file_content.length());
			if (s_flag_name_ == str_type)
			{
				//next flag "," ,split one more time
				/*index = str_content.find_first_of(',');
				while (string::npos != index)
				{
				*p_array = str_content.substr(0, index);
				str_content = str_content.substr(index + 1, str_content.length());
				index = str_content.find_first_of(',');
				++p_array;
				}*/
				p_array_ = str_content;
			}
		}
	}

	void fill_objects_images(cv::Mat mat_obj_, cv::Mat mat_background_,int n_offset_x_,int n_offset_y_)
	{
		for (int n_rows_iter = 0; n_rows_iter < mat_obj_.rows; n_rows_iter++)
		{
			uchar* pix_value = mat_obj_.ptr<uchar>(n_rows_iter);
			uchar* back_pix_value = mat_background_.ptr<uchar>(n_rows_iter + n_offset_y_);
			for (int n_cols_iter = 0; n_cols_iter < mat_obj_.cols * 3; n_cols_iter++)
			{
				//int flag = pnpoly(4, d_xp_arr, d_yp_arr, (double)n_cols_iter, (double)n_rows_iter);
				//std::cout << flag << std::endl;
				if (pix_value[n_cols_iter] == 0)
				{
					pix_value[n_cols_iter] = back_pix_value[n_cols_iter + n_offset_x_ * 3];
				}
			}
		}
	}

	void objects_get_rot_point(double d_x_, double d_y_, cv::Mat mat_rot_matrix_, double& d_x1_, double& d_y1_)
	{

		//	std::cout << "rot_matrix:" << rot_matrix << std::endl;
		cv::Mat mat_matrix = cv::Mat(cv::Vec3d{ d_x_, d_y_, 1. });
		cv::Mat mat_matrix_dst;
		mat_matrix_dst = mat_rot_matrix_ * mat_matrix;
		d_x1_ = mat_matrix_dst.at<double>(0, 0);
		d_y1_ = mat_matrix_dst.at<double>(1, 0);
	}

	void objects_get_rotate_image(cv::Mat mat_src_, cv::Mat & mat_dst_, int n_degree_, int n_border_value_, double& d_sina_, double& d_cosa_, int& n_rot_w_, int& n_rot_h_, cv::Mat& mat_rot_matrix_)
	{
		n_degree_ = -n_degree_;//warpAffine默认的旋转方向是逆时针，所以加负号表示转化为顺时针
		double angle = n_degree_  * CV_PI / 180.; // 弧度  
		double a = sin(angle), b = cos(angle);
		d_sina_ = -a;
		d_cosa_ = b;
		double width = mat_src_.cols;
		double height = mat_src_.rows;
		//std::cout << "width :" << width << "    " << "height : " << height << std::endl;
		int width_rotate = int(width * fabs(b) + height * fabs(a));
		int height_rotate = int(height * fabs(b) + width * fabs(a));
		n_rot_w_ = width_rotate;
		n_rot_h_ = height_rotate;
		//std::cout << "w :" << rot_w << "    " << "h : " << rot_h << std::endl;
		if (width_rotate <= 20 || height_rotate <= 20)
		{
			width_rotate = 20;
			height_rotate = 20;
		}
		//
		//w = width_rotate;
		//h = height_rotate;
		//旋转数组map
		// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
		// [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
		// 旋转中心
		cv::Point2d center = cv::Point2d(width / 2, height / 2);
		//CvMat map_matrix2 = map_matrix;
		mat_rot_matrix_ = cv::getRotationMatrix2D(center, n_degree_, 1.);//计算二维旋转的仿射变换矩阵
		mat_rot_matrix_.at<double>(0, 2) += (width_rotate - width) / 2;
		mat_rot_matrix_.at<double>(1, 2) += (height_rotate - height) / 2;
		//Mat img_rotate;
		//	rot_matrix = map_matrix;
		//对图像做仿射变换
		//CV_WARP_FILL_OUTLIERS - 填充所有输出图像的象素。
		//如果部分象素落在输入图像的边界外，那么它们的值设定为 fillval.
		//CV_WARP_INVERSE_MAP - 指定 map_matrix 是输出图像到输入图像的反变换，
		int chnnel = mat_src_.channels();
		if (chnnel == 3)
		{
			cv::warpAffine(mat_src_, mat_dst_, mat_rot_matrix_, cv::Size(width_rotate, height_rotate), 1, 0, cv::Scalar(n_border_value_, n_border_value_, n_border_value_));
		}
		else
		{
			cv::warpAffine(mat_src_, mat_dst_, mat_rot_matrix_, cv::Size(width_rotate, height_rotate), 1, 0, n_border_value_);
		}
	}

	void objects_add_pixel_value(cv::Mat mat_src_, int n_add_num_)
	{
		for (int n_rows_iter = 0; n_rows_iter < mat_src_.rows; n_rows_iter++)
		{
			uchar* obj_pix_value = mat_src_.ptr<uchar>(n_rows_iter);
			for (int n_cols_iter = 0; n_cols_iter < mat_src_.cols * 3; n_cols_iter++)
			{
				if (obj_pix_value[n_cols_iter] == 0)
				{
					obj_pix_value[n_cols_iter] = obj_pix_value[n_cols_iter] + n_add_num_;
				}
			}
		}
	}

	void objects_add_sheet_image(cv::Mat mat_src_, std::string s_path_, double& d_x1_, double& d_y1_, double& d_x2_, double& d_y2_, double& d_x3_, double& d_y3_, double& d_x4_, double& d_y4_)
	{
		cv::Mat mat_dst_sheet, rot_matrix;
		int degree, rot_w, rot_h;
		double sina, cosa;
		cv::Mat src_sheet = cv::imread(s_path_ + "sheet.jpg");
		//
		this->objects_add_pixel_value(src_sheet, 1);
		degree = rand() % 90 + 1;
		//
		this->objects_get_rotate_image(src_sheet, mat_dst_sheet, degree, 0, sina, cosa, rot_w, rot_h, rot_matrix);
		if (rot_w < mat_src_.cols && rot_h < mat_src_.rows)
		{
			int sheet_x = rand() % (mat_src_.cols - rot_w);
			int sheet_y = rand() % (mat_src_.rows - rot_h);
			this->fill_objects_images(mat_dst_sheet,mat_src_,sheet_x,sheet_y);
			cv::Mat roi = mat_src_(cv::Rect(sheet_x, sheet_y, rot_w, rot_h));
			cv::addWeighted(roi, 0.0, mat_dst_sheet, 1, 0, roi);
			this->objects_get_rot_point(0, 0, rot_matrix, d_x1_, d_y1_);
			this->objects_get_rot_point(src_sheet.cols, 0, rot_matrix, d_x2_, d_y2_);
			this->objects_get_rot_point(src_sheet.cols, src_sheet.rows, rot_matrix, d_x3_, d_y3_);
			this->objects_get_rot_point(0, src_sheet.rows, rot_matrix, d_x4_, d_y4_);
			d_x1_ = d_x1_ + sheet_x;
			d_x2_ = d_x2_ + sheet_x;
			d_x3_ = d_x3_ + sheet_x;
			d_x4_ = d_x4_ + sheet_x;
			d_y1_ = d_y1_ + sheet_y;
			d_y2_ = d_y2_ + sheet_y;
			d_y3_ = d_y3_ + sheet_y;
			d_y4_ = d_y4_ + sheet_y;
		}
		else
		{
			d_x1_ = 0;
			d_x2_ = 0;
			d_x3_ = 0;
			d_x4_ = 0;
			d_y1_ = 0;
			d_y2_ = 0;
			d_y3_ = 0;
			d_y4_ = 0;
		}
	}

	void objects_resize_obj_rand(cv::Mat mat_src_, cv::Mat& mat_dst_, double& d_magnification_)
	{
		int n_rand_magni = rand() % 7;
		double d_magni = 1.;
		//int n_b_zoom = rand() % 10 + 1;
		d_magni = 1. + 0.1*n_rand_magni;
		d_magnification_ = d_magni;
		//std::cout << "MAGNIFICATION: " << d_magni << std::endl;
		cv::resize(mat_src_, mat_dst_, cv::Size(), d_magni, d_magni, 1);
	}

	void objects_get_outer_rect(double d_x1_, double d_y1_, double d_x2_, double d_y2_, double d_x3_, double d_y3_, double d_x4_, double d_y4_, double& d_x_, double& d_y_, double& d_w_, double& d_h_)
	{
		double d_x_list[4] = { d_x1_, d_x2_, d_x3_, d_x4_ };
		double d_y_list[4] = { d_y1_, d_y2_, d_y3_, d_y4_ };
		std::sort(d_x_list, d_x_list + 4);
		std::sort(d_y_list, d_y_list + 4);
		d_w_ = fabs(d_x_list[3] - d_x_list[0]);
		d_h_ = fabs(d_y_list[3] - d_y_list[0]);
		d_x_ = d_x_list[0] + d_w_ / 2;
		d_y_ = d_y_list[0] + d_h_ / 2;
	}
};
#endif
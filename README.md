# ImageProducer
## Abstract
A tool to produce images  composed by some small object images.
## Description
This tool is based on ```OpenCV``` in ```C++``` mainly.   
You are only required to provide kinds of objects images in shape of **Rectangle** and a background image.   
There are functions description.  
- **Rotate your objects in any  random  or decided degrees.**
  - The four black areas of the triangle will appear after rotated in rectangle.
  - This tool could fill the black areas with background pixels.
- **Output the objects label and location information, (label,center.x,center.y,width,height)**
  - center.x = ((object_TopLeft_corner.x + object.width) / 2) / background.width
  - center.y = (object_TopLeft_corner.y + object.height) / 2) / background.height
  - width = object.width / background.width
  - height = object.height / background.height
  - For example, label file **1.txt** 
  
    2 0.221 0.323 0.7655 0.7322  
    3 0.111 0.972 0.3746 0.9462
    
  ![Image with label](https://github.com/liqisa/ImagesSupport/blob/master/example1.jpg "Image with label")

# ��������������ʹ��ָ��
## 1.���� 
```data``` �ļ����д������ԴͼƬ��������ʽΪ:```label_number.jpg```  
����```2_1.jpg```

## 2.�����ļ�
```configs```�ļ����д�������ļ�```config.txt```  
�������£�
```
SRC_PATH:..\Release\data\   
DST_PATH:..\Release\saves\
BRIGHTNESS:1.0
```
```SRC_PATH``` �������ͼƬ·��  
```DST_PATH``` �����������·��  
```BRIGHTNESS``` ��Ÿ�����������������Ϣ  

## 3.��������
�򿪹��ߺ󣬰�����ʾ�������������������������  
### 3.1 ����Mode Number:
Mode Number ��Ϊ����ͼƬ������ĸ�������Ŀ�ѡ����  
���磺���� ```3``` ��������ͼƬ������������������

### 3.2 ����Mode:
����ÿ�ָ�������ľ������  
���磺Mode Number Ϊ 3 ��ʱ�򣬿��������� 5 6 7  
������ͼƬ�е������������� 5 6 7 ���������ѡ��

### 3.3 ����Object Number:
��������ͼƬ�����������Ŀǰ�� ���ӣ����֣�ũ��ɽȪ�����̣����������֡�  
������ ```5```  
### 3.4 ����Object :
����˳����룺2,3,4,5,6

### 3.5 ��������ͼƬ��������ʼ���

### 3.6 ͼƬ����ʾ All DataSet Done! ���������

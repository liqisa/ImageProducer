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

# 仿真数据生成器使用指南
## 1.样本 
```data``` 文件夹中存放样本源图片，命名格式为:```label_number.jpg```  
例：```2_1.jpg```

## 2.配置文件
```configs```文件夹中存放配置文件```config.txt```  
内容如下：
```
SRC_PATH:..\Release\data\   
DST_PATH:..\Release\saves\
BRIGHTNESS:1.0
```
```SRC_PATH``` 存放样本图片路径  
```DST_PATH``` 存放生成数据路径  
```BRIGHTNESS``` 存放该批生成数据亮度信息  

## 3.数据生成
打开工具后，按照提示进行生成数据配置情况的输入  
### 3.1 输入Mode Number:
Mode Number 即为生成图片中物体的个数情况的可选种类  
例如：键入 ```3``` ，则生成图片中物体个数有三种情况

### 3.2 输入Mode:
输入每种个数情况的具体个数  
例如：Mode Number 为 3 的时候，可依次输入 5 6 7  
则生成图片中的物体个数随机在 5 6 7 三种情况中选择

### 3.3 输入Object Number:
输入样本图片种类的数量，目前有 箱子，可乐，农夫山泉，酸奶，果粒橙五种。  
可输入 ```5```  
### 3.4 输入Object :
任意顺序键入：2,3,4,5,6

### 3.5 输入生成图片数量及起始编号

### 3.6 图片中显示 All DataSet Done! 即生成完成

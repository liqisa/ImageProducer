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
  
  ![Image with label](https://github.com/liqisa/ImagesSupport/blob/master/example1.jpg/auto-orient/strip "Image with label")

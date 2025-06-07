#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_
 
#include "image.h"

class RGBImage : public Image{
private:

  int ***pixels;

public:

  RGBImage();
  RGBImage(int wid,int hei,int ***pixels);
  RGBImage(const RGBImage& other);
  ~RGBImage();
  
  bool LoadImage(string filename);
  void DumpImage(string filename);
  void Display_X_Server();
  void Display_ASCII();
  int getrgbpix(int x, int y, int z);
  void setrgbpix(int x, int y, int z, int value);
  int getWidth();
  int getHeight();
  
  
//========================================  foundamental

  RGBImage *Horizon_flip();
  RGBImage *Mosaic_filter(int filter_num);
  RGBImage *Gaussian_filter(int k_size,double sigma);
  RGBImage *Laplacian_filter();
  
//========================================  extension

  RGBImage *Negative_filter();
  RGBImage *AdjustContrast(double alpha);// alpha = contrast factor
  RGBImage *TiltShifter(int focus_y,int focus_width,int max_blur_radius);
  RGBImage *FisheyeEffect(double distortion);
  RGBImage *OldPhotoEffect();


};

#endif
#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:

  int **pixels;

public:

  GrayImage();
  GrayImage(int wid,int hei,int **intput_pixels);
  ~GrayImage();
  bool LoadImage(string filename);
  void DumpImage(string filename);
  void Display_X_Server();
  void Display_ASCII();
  int getPixel(int x , int y);
  void setPixel(int x ,int y,int value);
  int getWidth();
  int getHeight();
  
//========================================  foundamental

  GrayImage *Horizon_flip();
  GrayImage *Mosaic_filter(int filter_num);
  GrayImage *Gaussian_filter(int k_size,double sigma);
  GrayImage *Laplacian_filter();
  
//========================================  extension

  GrayImage *Negative_filter();
  GrayImage *AdjustContrast(double alpha,int beta);// alpha = constrat ; beta = brightness
  GrayImage *TiltShifter(int focus_y,int focus_width,int max_blur_radius);
  GrayImage *FisheyeEffect(double distortion);
  GrayImage *OldPhotoEffect();
  
//======================================== Just for Gray

  GrayImage *Threshold(int threshold_value);
  
//======================================== tool

  void add_noise(double intensity);

};

#endif
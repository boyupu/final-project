 #include "gray_image.h"
 #include <random>

//constructor

GrayImage::GrayImage() : Image(0,0),pixels(nullptr)
{}

GrayImage::GrayImage(int wid,int hei,int **intput_pixels) : Image(wid,hei)
{

  pixels = new int*[hei];
  for(int y = 0 ; y < hei ; y++){
  
    pixels[y] = new int[wid];
    
    for(int x = 0 ; x < wid ; x++){
    
      pixels[y][x] = intput_pixels[y][x];
    
    }
  }
}

GrayImage::~GrayImage(){

  for(int y = 0 ; y < h ; y++){
  
    delete[] pixels[y];
  
  }
  delete[] pixels;
}

//process

bool GrayImage::LoadImage(string filename){

  pixels = data_loader.Load_Gray(filename,&w,&h);
  return(pixels != nullptr);
  
}

void GrayImage::DumpImage(string filename){

  data_loader.Dump_Gray(w,h,pixels,filename);
  return;
  
}

void GrayImage::Display_X_Server(){

  data_loader.Display_Gray_X_Server(w,h,pixels);
  return;

}

void GrayImage::Display_ASCII(){

  data_loader.Display_Gray_ASCII(w,h,pixels);
  return;

}

int GrayImage::getPixel(int x , int y){


  if(x >= 0 && x < w && y >= 0 && y < h){
  
    return pixels[y][x];
  
  }
  return 0;
}
void GrayImage::setPixel(int x ,int y,int value){

  if(x >= 0 && x < w && y >= 0 && y < h){
  
    pixels[y][x] = value;
  
  }
}

//getwidthgetheight
int GrayImage::getWidth()
{
  return w;
}
int GrayImage::getHeight()
{
  return h;
}

//image_process

//1.Horizon_flip
GrayImage *GrayImage::Horizon_flip(){

  int width = this->w;
  int height = this->h;
  
  int **flippedPixels = new int *[height];
  for(int i = 0 ; i < height ; i++){ 
    flippedPixels[i] = new int [width];
  }
  
  for(int i = 0 ; i < height ; i++){
    for(int j = 0 ; j < width ; j++){
    
      flippedPixels[i][width - 1 - j] = this->pixels[i][j];
    
    }
  }
  
  GrayImage *flippedImage = new GrayImage(width,height,flippedPixels);

  return flippedImage;
}
//===========================

//2.Mosaic_filter
GrayImage *GrayImage::Mosaic_filter(int filter_num){

  int **MosaicPixels = new int *[h];
  for(int y = 0 ; y < h ; y++){
  
    MosaicPixels[y] = new int[w];
  }
  
  for(int y = 0 ; y < h ; y += filter_num){
    for(int x = 0 ; x < w ; x += filter_num){
    
      int cnt = 0;
      int color = 0;
      
      for(int k_y = y ; k_y < y + filter_num ; k_y++){
        for(int k_x = x ; k_x < x + filter_num ; k_x++){
        
          if(k_y < h && k_x < w){
          
            color += pixels[k_y][k_x];
            cnt++;
    
          }    
        }
      }
      
      color /= cnt;
      for(int k_y = y ; k_y < y + filter_num ; k_y++){
        for(int k_x = x ; k_x < x + filter_num ; k_x++){
        
          if(k_y < h && k_x < w){
          
            MosaicPixels[k_y][k_x] = color;
    
          }    
        }
      }
    }
  }

  GrayImage *mosaic_filter = new GrayImage(w,h,MosaicPixels);
  
  return mosaic_filter;
}
//============================

//3.Gaussian_filter
GrayImage  *GrayImage::Gaussian_filter(int k_size,double sigma){

  int **GaussianPixels = new int*[h];
  for(int y = 0 ; y < h ; y++){
  
    GaussianPixels[y] = new int[w];
  
  }

  double **kernel = new double*[k_size];
  for(int n = 0 ; n < k_size ; n++){
  
    kernel[n] = new double[k_size];
  
  }
  
  int center = k_size/2;
  
  double sum = 0.0;
  
  // use formula to get G(x,y)  
  
  for(int y = -center ; y <= center ; y++){
    for(int x = -center ; x <= center ; x++){
    
      double value = (exp(-((x*x+y*y)/sigma*sigma)))  / (2*M_PI*sigma*sigma);
    
      kernel[y+center][x+center] = value;
      
      sum += value;
    
    }
  }
  
  for(int y = 0 ; y < k_size ; y++){
    for(int x = 0 ; x < k_size ; x++){
    
      kernel[y][x] = kernel[y][x] / sum;
    
    }
  }
  
  for(int y = 0 ; y < h ; y++){
    for(int x = 0 ; x < w ; x++){
    
      double process_pixels = 0.0;
      
      for(int ky = -center ; ky <= center ; ky++){
        for(int kx = -center ; kx <= center ; kx++){
    
          int newX = x + kx;
          int newY = y + ky;
          
          if(newX >= 0 && newX < w && newY >= 0 && newY < h){
          
            process_pixels += pixels[newY][newX] * kernel[ky + center][kx + center];
          
          }        
        }
      }
      
      GaussianPixels[y][x] = static_cast<int>(process_pixels);
    }
  }
  
  for(int n = 0 ; n < k_size ; n++){
  
    delete[] kernel[n];
  
  }

  delete[] kernel;
  
  GrayImage * gaussian_filter = new GrayImage(w,h,GaussianPixels);
  
  return gaussian_filter;
}
//===============================

//4.Laplacian_filter
GrayImage *GrayImage::Laplacian_filter()
{
  int height = this->h;
  int width = this->w;

  int **Lap = new int *[h];
  for(int y = 0 ; y < h ; y++){
  
    Lap[y] = new int[w];
  }
  
  const int kernel[3][3] = {
    {0, -1, 0},
    {-1, 5, -1},
    {0, -1, 0}
  };
  
  
  for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sum = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    sum += this->pixels[y + ky][x + kx] * kernel[ky + 1][kx + 1];
                  }
            }
                
            sum = std::min(255, std::max(0, sum));
            Lap[y][x] = sum;
        }
    }

    GrayImage *Laplacianpic = new GrayImage(width, height, Lap);
    return Laplacianpic;
}

//===============================

//5.negative_filter
GrayImage  *GrayImage::Negative_filter(){

  int **negativePixels = new int*[h];
  
  for(int y = 0 ; y < h ; y++){
  
    negativePixels[y] = new int[w];
  
  }

  for(int y = 0 ; y < h ; y++){
    for(int x = 0 ; x < w ; x++){
    
      negativePixels[y][x] = 255 - pixels[y][x];
    
    }
  }

  GrayImage *negative_filter = new GrayImage(w,h,negativePixels);
  
  return negative_filter;
}

//===============================

//6.adjustContrast
GrayImage * GrayImage::AdjustContrast(double alpha,int beta){

  int **contrastPixels = new int*[h];
  for(int y = 0 ; y < h ; y++){
  
    contrastPixels[y] = new int[w];
  
  }

  for(int y = 0 ; y < h ; y++){
    for(int x = 0 ; x < w ; x++){
  
      int originalPixel = pixels[y][x];
      
      double processPixel = alpha * originalPixel + beta;
      int processedPixel = static_cast<int>(processPixel);
      
      processedPixel = std::max(0,std::min(255,processedPixel));
      
      contrastPixels[y][x] = processedPixel;

    }
  }

  GrayImage *adjustContrast = new GrayImage(w,h,contrastPixels);
  
  return adjustContrast;
}
//====================================

//7.TiltShifter
GrayImage *GrayImage::TiltShifter(int focus_y,int focus_width,int max_blur_radius){

  int **tiltPixels = new int*[h];
  
  for(int y = 0 ; y < h ; y++){
  
    tiltPixels[y] = new int[w];
    
    for(int x = 0 ; x < w ; x++){
    
      tiltPixels[y][x] = pixels[y][x];
    
    }
  }
  
  GrayImage *tiltShifter = new GrayImage(w,h,tiltPixels);
  
  int focus_top = focus_y - focus_width/2;
  int focus_bottom = focus_y + focus_width/2;
  
  if(focus_top<0) focus_top = 0;
  if(focus_bottom >= h) focus_bottom = h -1;

  for(int y = 0 ; y < h ; y++){
  
    if(y >= focus_top && y <= focus_bottom){
    
      for(int x = 0 ; x < w ; x++){
      
        tiltShifter->pixels[y][x] = this->pixels[y][x];
      
      }
    } else {
    
      int dist_focus = 0;
      if(y < focus_top){
      
        dist_focus = focus_top - y;
      
      } else {
      
        dist_focus = y - focus_bottom;
      
      }
      
      double blur_ratio = static_cast<double>(dist_focus) / (h/2 - focus_width/2);
      if(blur_ratio > 1.0) blur_ratio = 1.0;
      
      int current_blur_radius = static_cast<int>(blur_ratio * max_blur_radius);
      if (current_blur_radius % 2 == 0) current_blur_radius++;
      if (current_blur_radius < 1) current_blur_radius = 1;
      
      double current_sigma = blur_ratio * max_blur_radius / 3.0;
      if(current_sigma < 0.5) current_sigma = 0.5;
      
      int kernel_size = static_cast<int>(current_sigma * 3.0) * 2 + 1;
      if(kernel_size < 3) kernel_size = 3;
      
      for(int x = 0 ; x < w ; x++){
      
        double blurred_pixel_value = 0.0;
        double total_weight = 0.0;
        
        int half_kernel = kernel_size / 2;

                for (int ky = -half_kernel; ky <= half_kernel; ++ky) {
                    for (int kx = -half_kernel; kx <= half_kernel; ++kx) {
                        int current_y = y + ky;
                        int current_x = x + kx;

                        if (current_y >= 0 && current_y < h && current_x >= 0 && current_x < w) {
                            double weight = exp(-(kx*kx + ky*ky) / (2 * current_sigma * current_sigma));
                            blurred_pixel_value += this->pixels[current_y][current_x] * weight;
                            total_weight += weight;
                        }
                    }
                }
                if (total_weight > 0) {
                    tiltShifter->pixels[y][x] = static_cast<int>(blurred_pixel_value / total_weight);
                } else {
                    tiltShifter->pixels[y][x] = this->pixels[y][x];
                }
      }
    } 
  }
  
  return tiltShifter;
  
}
//=========================================

//8.FisheyeEffect

GrayImage *GrayImage::FisheyeEffect(double distortion) {
    
    int** new_pixels = new int*[h];
    for (int y = 0; y < h; ++y)
        new_pixels[y] = new int[w];
        
    GrayImage* output = new GrayImage(w,h,new_pixels);

    double cx = w / 2.0;
    double cy = h / 2.0;
    double max_radius = min(cx, cy);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            
            double nx = (x - cx) / max_radius;
            double ny = (y - cy) / max_radius;
            double r = sqrt(nx * nx + ny * ny);

            if (r > 1.0) {
                new_pixels[y][x] = 0;
                continue;
            }

            double r_distorted = pow(r, distortion);
            double theta = atan2(ny, nx);

            double src_x = cx + r_distorted * max_radius * cos(theta);
            double src_y = cy + r_distorted * max_radius * sin(theta);

            int src_ix = static_cast<int>(round(src_x));
            int src_iy = static_cast<int>(round(src_y));

            if (src_ix >= 0 && src_ix < w && src_iy >= 0 && src_iy < h) {
                new_pixels[y][x] = getPixel(src_ix, src_iy);
            } else {
                new_pixels[y][x] = 0;
            }
        }
    }

    output->pixels = new_pixels;
    return output;
}
//===================================

//9.Threshold(only gray)

GrayImage *GrayImage::Threshold(int threshold_value){

  int** ThresholdPixels = new int*[h];
    for (int y = 0; y < h; ++y)
        ThresholdPixels[y] = new int[w];
        
  if(threshold_value < 0) threshold_value = 0;
  if(threshold_value > 255) threshold_value = 255;
  
  for(int y = 0 ; y < h ; y++){
    for(int x = 0 ; x < w ; x++){
    
      int original_pixel = pixels[y][x];
      
      if(original_pixel >= threshold_value){
      
        ThresholdPixels[y][x] = 255;
      
      }else{
      
        ThresholdPixels[y][x] = 0;
      
      }
    }
  }

  GrayImage *threshold = new GrayImage(w,h,ThresholdPixels);

  return threshold;

}
//=====================================

//10.OldPhotoEffect

void GrayImage::add_noise(double intensity){

  random_device rd;
  mt19937 gen(rd());
  
  normal_distribution<> dis(0.0,intensity);
  
  for(int y = 0 ;y < h ; y++){
    for(int x = 0 ; x < w ; x++){
    
      int current_pixel = pixels[y][x];
      
      double noise = dis(gen);
      
      int new_pixel = static_cast<int>(current_pixel + noise);
      
      if(new_pixel < 0) new_pixel = 0;
      if(new_pixel > 255) new_pixel = 255;
      
      pixels[y][x] = new_pixel;
    }
  }
}

GrayImage *GrayImage::OldPhotoEffect(){

  int** OldPhotoEffectPixels = new int*[h];
    for (int y = 0; y < h; ++y){
        OldPhotoEffectPixels[y] = new int[w];
        for(int x = 0 ; x < w ; x++){
        
          OldPhotoEffectPixels[y][x] = pixels[y][x];
 
        }
    }
        
  double alpha = 0.9;
  int beta = -10;
  
  GrayImage *temp = new GrayImage(w,h,OldPhotoEffectPixels);
  
  GrayImage *adjust = temp->AdjustContrast(alpha,beta);

  delete temp;
  
  temp = adjust;
  
  double noise_intensity = 15.0;
  
  temp->add_noise(noise_intensity);


  return temp;

}
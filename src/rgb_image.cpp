#include "rgb_image.h"

//constructor

RGBImage::RGBImage() : Image(0,0),pixels(nullptr)
{}

RGBImage::RGBImage(int wid,int hei,int ***pix) : Image(wid,hei)
{
  if (pix != nullptr) {
        pixels = new int**[hei];
        for (int y = 0; y < hei; ++y) {
            pixels[y] = new int*[wid];
            for (int x = 0; x < wid; ++x) {
                pixels[y][x] = new int[3];
                for (int c = 0; c < 3; ++c) {
                    pixels[y][x][c] = pix[y][x][c]; //copy
                }
            }
        }
    } else {
        pixels = new int**[hei];
        for (int y = 0; y < hei; ++y) {
            pixels[y] = new int*[wid];
            for (int x = 0; x < wid; ++x) {
                pixels[y][x] = new int[3]{0, 0, 0}; //0 at first 
            }
        }
    }
}

//copy ctor
RGBImage::RGBImage(const RGBImage &other) : Image(other.w, other.h)
{
    if (other.pixels != nullptr) {
        pixels = new int**[h];
        for (int y = 0; y < h; ++y) {
            pixels[y] = new int*[w];
            for (int x = 0; x < w; ++x) {
                pixels[y][x] = new int[3];
                for (int c = 0; c < 3; ++c) {
                    pixels[y][x][c] = other.pixels[y][x][c];
                }
            }
        }
    } else {
        pixels = nullptr;
    }
}

RGBImage::~RGBImage(){
  if (pixels != nullptr){
    for(int y = 0 ; y < h ; y++){
    
      for(int x = 0 ; x < w ; x++){
      
        delete[] pixels[y][x];
        
      }
      delete[] pixels[y];
    
    }
    delete[] pixels;
  }
}

//process

bool RGBImage::LoadImage(string filename){ 
  pixels = data_loader.Load_RGB(filename,&w,&h);
  return(pixels != nullptr);
}

void RGBImage::DumpImage(string filename){
  data_loader.Dump_RGB(w,h,pixels,filename);
  return;
}

void RGBImage::Display_X_Server(){
  data_loader.Display_RGB_X_Server(w,h,pixels);
  return;
}

void RGBImage::Display_ASCII(){
  data_loader.Display_RGB_ASCII(w,h,pixels);
  return;
}

int RGBImage::getrgbpix(int x, int y, int z){
  if(x >= 0 && x < w && y >= 0 && y < h && z >= 0 && z <= 2){
    return pixels[y][x][z];
  }
  return 0;
}

void RGBImage::setrgbpix(int x ,int y,int z, int value){
  if(x >= 0 && x < w && y >= 0 && y < h && z >= 0 && z <= 2){
    pixels[y][x][z] = value;
  }
}

//getwidthgetheight
int RGBImage::getWidth()
{
  return w;
}
int RGBImage::getHeight()
{
  return h;
}

//===================================================================
//image_process

//1.Horizon_flip
RGBImage *RGBImage::Horizon_flip()
{
  int width = this -> w;
  int height = this -> h;
  
  int ***flippedPixels = new int **[height];
  for(int i = 0 ; i < height ; i++){ 
    flippedPixels[i] = new int *[width];
    for(int j = 0 ; j < width ; j++){
      flippedPixels[i][j] = new int [3]{0, 0, 0};
    }
  }
  
  
  for(int i = 0 ; i < height ; i++){
    for(int j = 0 ; j < width ; j++){
      for(int k = 0 ; k < 3 ; k++){
        flippedPixels[i][width - 1 - j][k] = this->pixels[i][j][k];
      }
    }
  }
  
  RGBImage *flippedImage = new RGBImage(width,height,flippedPixels);

  return flippedImage;
}

//===================================================================
// 2.Mosaic_filter
RGBImage *RGBImage::Mosaic_filter(int blocksize)
{
  int height = this -> h;
  int width = this -> w;
  
  
  int ***mosaic = new int **[height];
  for(int i = 0 ; i < height ; i++){ 
    mosaic[i] = new int *[width];
    for(int j = 0 ; j < width ; j++){
      mosaic[i][j] = new int [3]{0, 0, 0};
    }
  }
  
  // run every mosaic block
  for(int block_y = 0 ; block_y < height ; block_y += blocksize)
  {
    for(int block_x = 0 ; block_x < width ; block_x += blocksize)
    {
      int sum[3] = {0, 0, 0};
      int count = 0;
      
      // calculate the sum
      for(int y = block_y ; y < block_y + blocksize && y < height ; y++)
      {
        for(int x = block_x ; x < block_x + blocksize  && x < width; x++)
        {
          for(int c = 0 ; c < 3 ;c ++)
          {
            sum[c] += this -> pixels[y][x][c];
          }
          
          count ++;
        }
      }
      
      //count avg
      int avg[3];
      for(int c = 0 ; c < 3 ; c++)
      {
        avg[c] = sum[c] / count;
      }
      
      // fill new pixels
      for(int y = block_y ; y < block_y + blocksize && y < height ; y++)
      {
        for(int x = block_x ; x < block_x + blocksize && x < width ; x++)
        {
          for(int c = 0 ; c < 3 ; c ++)
          {
            mosaic[y][x][c] = avg[c];
          }
        }
      }
    }
  }
  
  RGBImage *mosaicpic = new RGBImage(width, height, mosaic);
  return mosaicpic;
}

//===================================================================
// 3.Gaussian_filter
RGBImage *RGBImage::Gaussian_filter(int k_size, double sigma)
{
    int height = this->h;
    int width = this->w;

    int ***blurred = new int **[height];
    for (int i = 0; i < height; i++)
    {
        blurred[i] = new int *[width];
        for (int j = 0; j < width; j++)
        {
            blurred[i][j] = new int[3]{0, 0, 0};
        }
    }

    // construct gaussian kernel
    double **kernel = new double *[k_size];
    for (int i = 0; i < k_size; i++)
    {
        kernel[i] = new double[k_size];
    }

    int half = k_size / 2;
    double sum = 0.0;

    // calculate kernel
    for (int y = -half; y <= half; y++)
    {
        for (int x = -half; x <= half; x++)
        {
            double value = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel[y + half][x + half] = value;
            sum += value;
        }
    }

    // Normalize kernel
    for (int y = 0; y < k_size; y++)
    {
        for (int x = 0; x < k_size; x++)
        {
            kernel[y][x] /= sum;
        }
    }

    // Apply Gaussian filter 
    for (int c = 0; c < 3; c++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                double pixel_value = 0.0;

                for (int ky = -half; ky <= half; ky++)
                {
                    for (int kx = -half; kx <= half; kx++)
                    {
                        int ny = y + ky;
                        int nx = x + kx;

                        if (ny >= 0 && ny < height && nx >= 0 && nx < width)
                        {
                            pixel_value += pixels[ny][nx][c] * kernel[ky + half][kx + half];
                        }
                    }
                } 

                blurred[y][x][c] = static_cast<int>(pixel_value);
            }
        }
    }

    // delete kernel
    for (int i = 0; i < k_size; i++)
    {
        delete[] kernel[i];
    }
    delete[] kernel;

    RGBImage *result = new RGBImage(width, height, blurred);
    return result;
}

//==========================================================
// 4.Laplacian filter

RGBImage *RGBImage::Laplacian_filter()
{
  int height = this->h;
  int width = this->w;

  int ***laplacian = new int **[height];
  for (int i = 0; i < height; i++)
  {
    laplacian[i] = new int *[width];
    for (int j = 0; j < width; j++)
    {
      laplacian[i][j] = new int[3]{0, 0, 0};
    }
  }
  
  const int kernel[3][3] = {
    {0, -1, 0},
    {-1, 5, -1},
    {0, -1, 0}
  };
  
  
  for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < 3; c++) {
                int sum = 0;
                for (int ky = -1; ky <= 1; ky++) {
                    for (int kx = -1; kx <= 1; kx++) {
                        sum += this->pixels[y + ky][x + kx][c] * kernel[ky + 1][kx + 1];
                    }
                }
                
                sum = std::min(255, std::max(0, sum));
                laplacian[y][x][c] = sum;
            }
        }
    }

    RGBImage *Laplacianpic = new RGBImage(width, height, laplacian);
    return Laplacianpic;
}

//========================================================================================
// 5.negative_filter
RGBImage  *RGBImage::Negative_filter(){

  int height = this->h;
  int width = this->w;

  int ***neg = new int **[height];
  for (int i = 0; i < height; i++)
  {
    neg[i] = new int *[width];
    for (int j = 0; j < width; j++)
    {
      neg[i][j] = new int[3]{0, 0, 0};
    }
  }

  for(int y = 0 ; y < h ; y ++){
    for(int x = 0 ; x < w ; x ++){
      for(int c =0 ; c < 3 ; c ++){
        neg[y][x][c] = 255 - pixels[y][x][c];
      }
    }
  }

  RGBImage *nega = new RGBImage(w,h,neg);
  
  return nega;
}

//======================================================
// 6.adjustContrast

RGBImage * RGBImage::AdjustContrast(double factor){

  int height = this->h;
  int width = this->w;

  int ***contrast = new int **[height];
  for (int i = 0; i < height; i++)
  {
    contrast[i] = new int *[width];
    for (int j = 0; j < width; j++)
    {
      contrast[i][j] = new int[3]{0, 0, 0};
    }
  }
  
  for(int i = 0 ; i < h ; i ++){
    for(int j = 0 ; j < w ; j ++){
      for(int c = 0; c < 3 ; c ++){
      
        int newval = static_cast<int>((this->pixels[i][j][c] - 128) * factor + 128);
        newval = std::max(0, std::min(255, newval));
        contrast[i][j][c] = newval;
        
      }
    }
  }

  RGBImage *Contrast = new RGBImage(w,h,contrast);
  
  return Contrast;
}

//=======================================================================
// 7.TiltShifter
RGBImage *RGBImage::TiltShifter(int focus_y, int focus_width, int max_blur_radius) {
    int height = this->h;
    int width = this->w;

    int ***tiltPixels = new int**[height];
    for (int y = 0; y < height; y++) {
        tiltPixels[y] = new int*[width];
        for (int x = 0; x < width; x++) {
            tiltPixels[y][x] = new int[3];
            for (int c = 0; c < 3; c++) {
                tiltPixels[y][x][c] = pixels[y][x][c];
            }
        }
    }

    RGBImage *tiltShifter = new RGBImage(width, height, tiltPixels);

    int focus_top = focus_y - focus_width / 2;
    int focus_bottom = focus_y + focus_width / 2;

    if (focus_top < 0) focus_top = 0;
    if (focus_bottom >= height) focus_bottom = height - 1;

    for (int y = 0; y < height; y++) {
        if (y >= focus_top && y <= focus_bottom) {
            continue;
        } else {
            int dist_focus = (y < focus_top) ? (focus_top - y) : (y - focus_bottom);
            double blur_ratio = static_cast<double>(dist_focus) / (height / 2 - focus_width / 2);
            if (blur_ratio > 1.0) blur_ratio = 1.0;

            int current_blur_radius = static_cast<int>(blur_ratio * max_blur_radius);
            if (current_blur_radius % 2 == 0) current_blur_radius++;
            if (current_blur_radius < 1) current_blur_radius = 1;

            double current_sigma = blur_ratio * max_blur_radius / 3.0;
            if (current_sigma < 0.5) current_sigma = 0.5;

            int kernel_size = static_cast<int>(current_sigma * 3.0) * 2 + 1;
            if (kernel_size < 3) kernel_size = 3;

            int half_kernel = kernel_size / 2;

            for (int x = 0; x < width; x++) {
                double blurred_pixel[3] = {0.0, 0.0, 0.0};
                double total_weight = 0.0;

                for (int ky = -half_kernel; ky <= half_kernel; ++ky) {
                    for (int kx = -half_kernel; kx <= half_kernel; ++kx) {
                        int current_y = y + ky;
                        int current_x = x + kx;

                        if (current_y >= 0 && current_y < height && current_x >= 0 && current_x < width) {
                            double weight = exp(-(kx * kx + ky * ky) / (2 * current_sigma * current_sigma));
                            for (int c = 0; c < 3; c++) {
                                blurred_pixel[c] += this->pixels[current_y][current_x][c] * weight;
                            }
                            total_weight += weight;
                        }
                    }
                }

                if (total_weight > 0) {
                    for (int c = 0; c < 3; c++) {
                        tiltShifter->pixels[y][x][c] = static_cast<int>(blurred_pixel[c] / total_weight);
                    }
                } else {
                    for (int c = 0; c < 3; c++) {
                        tiltShifter->pixels[y][x][c] = this->pixels[y][x][c];
                    }
                }
            }
        }
    }

    return tiltShifter;
}


//=========================================
// 8.FisheyeEffect

RGBImage *RGBImage::FisheyeEffect(double distortion) {
    int ***new_pixels = new int**[h];
    for (int y = 0; y < h; ++y) {
        new_pixels[y] = new int*[w];
        for (int x = 0; x < w; ++x) {
            new_pixels[y][x] = new int[3]{0, 0, 0};
        }
    }
    
    RGBImage *output = new RGBImage(w, h, new_pixels);

    double cx = w / 2.0;
    double cy = h / 2.0;
    double max_radius = min(cx, cy);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double nx = (x - cx) / max_radius;
            double ny = (y - cy) / max_radius;
            double r = sqrt(nx * nx + ny * ny);

            if (r > 1.0) {
              for(int c = 0 ; c < 3 ; c++)
              {
                new_pixels[y][x][c] = 0;
              }
              continue;
            }

            double r_distorted = pow(r, distortion);
            double theta = atan2(ny, nx);

            double src_x = cx + r_distorted * max_radius * cos(theta);
            double src_y = cy + r_distorted * max_radius * sin(theta);

            int src_ix = static_cast<int>(round(src_x));
            int src_iy = static_cast<int>(round(src_y));

            if (src_ix >= 0 && src_ix < w && src_iy >= 0 && src_iy < h) {
                for (int c = 0; c < 3; ++c) {
                    new_pixels[y][x][c] = this->pixels[src_iy][src_ix][c];
                }
            }
        }
    }
    
    output->pixels = new_pixels;
    
    return output;
}

//=====================================
// 10.OldPhotoEffect











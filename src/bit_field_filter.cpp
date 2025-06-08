#include "bit_field_filter.h"
#include "gray_image.h"
#include "rgb_image.h"
#include <unistd.h>

void loadCase(int32_t option,int form){

  if(option & CASE_Horizon_flip)
    cout << "CASE Horizon flip detected!" << endl;
    
  if(option & CASE_Mosaic_filter)
    cout << "CASE Mosaic filter detected!" << endl;
    
  if(option & CASE_Gaussian_filter)
    cout << "CASE Gaussian filter detected!" << endl;
    
  if(option & CASE_Laplacian_filter)
    cout << "CASE Laplacian filter detected!" << endl;
    
  if(option & CASE_negative_filter)
    cout << "CASE negative filter!" << endl;
    
  if(option & CASE_adjustContrast)
    cout << "CASE adjustContrast!" << endl;
    
  if(option & CASE_TiltShifter)
    cout << "CASE TiltShifter!" << endl;
     
  if(option & CASE_FisheyeEffect)
    cout << "CASE FisheyeEffect!" << endl;
    
  if(option & CASE_Threshold)
    cout << "CASE Threshold!" << endl;
     
  if(option & CASE_OldPhotoEffect)
    cout << "CASE OldPhotoEffect!" << endl;
  
    
  cout << endl;
  
  printCase(option,form);
  
  return;
}

void printCase(int32_t option,int form){

  GrayImage *img = new GrayImage();
  img->LoadImage("Image-Folder/1-1.jpg");
  
  RGBImage *img_2 = new RGBImage();
  img_2->LoadImage("Image-Folder/1-2.jpg");
  cout << "Here are the original pictures!" << endl;
  img -> Display_X_Server();
  img_2 -> Display_X_Server();
  
  if((option & CASE_OldPhotoEffect || option & CASE_TiltShifter))
  
//1.Trigger Horizon flip

  if(option & CASE_Horizon_flip){
      
      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->Horizon_flip();
      img_process->Display_X_Server();
      delete img;
      img = img_process;
    
      RGBImage *img_2_process = img_2->Horizon_flip();
      img_2_process->Display_X_Server();
      delete img_2;
      img_2 = img_2_process;
   
  }
//2.Trigger Mosaic filter

  if(option & CASE_Mosaic_filter){
  
    cout << "Please enter the filter size" << endl;
    
    int size = 0;
    
    cin >> size;
  
    cout << "Procession......." << endl;
    
    GrayImage *img_process = img->Mosaic_filter(size);
    img_process->Display_X_Server();
    delete img;
    img = img_process;
    
    RGBImage *img_2_process = img_2->Mosaic_filter(size);
    img_2_process->Display_X_Server();
    delete img_2;
    img_2 = img_2_process;
    
  }
//3.Trigger Gaussian filter

  if(option & CASE_Gaussian_filter){
    
    cout << "Procession......." << endl;
    
    GrayImage *img_process = img->Gaussian_filter(7,1.5);
    img_process->Display_X_Server();
    delete img;
    img = img_process;
  
    RGBImage *img_2_process = img_2->Gaussian_filter(7,1.5);
    img_2_process->Display_X_Server();
    delete img_2;
    img_2 = img_2_process;
  }
  
//4.Trigger Laplacian filter

  if(option & CASE_Laplacian_filter){
    
    cout << "Procession......." << endl;
    
    GrayImage *img_process = img->Laplacian_filter();
    img_process->Display_X_Server();
    delete img;
    img = img_process;
    
    RGBImage *img_2_process = img_2->Laplacian_filter();
    img_2_process->Display_X_Server();
    delete img_2;
    img_2 = img_2_process;
  }

//5.Trigger negative filter

  if(option & CASE_negative_filter){
  
      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->Negative_filter();
      img_process->Display_X_Server();
      delete img;
      img = img_process;
    
      RGBImage *img_2_process = img_2->Negative_filter();
      img_2_process->Display_X_Server();
      delete img_2;
      img_2 = img_2_process;
  }
//6.Trigger adjustContrast

  if(option & CASE_adjustContrast){
  
      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->AdjustContrast(1.5,30);
      img_process->Display_X_Server();
      delete img;
      img = img_process;
    
      RGBImage *img_2_process = img_2->AdjustContrast(4);
      img_2_process->Display_X_Server();
      delete img_2;
      img_2 = img_2_process;
  }
//7.Trigger TiltShifter

  if(option & CASE_TiltShifter){
  
    GrayImage *img_3 = new GrayImage();
    img_3->LoadImage("Image-Folder/city.jpg");

    RGBImage *img_4 = new RGBImage();
    img_4->LoadImage("Image-Folder/city.jpg");
  
    cout << "Procession......." << endl;
    
    cout << "In order to show the TiltShifter,we use city image." << endl;
    img_3 -> Display_X_Server();
    img_4 -> Display_X_Server();
  
    if(form == 0){
    
      GrayImage *img_3_process = img_3->TiltShifter(img_3->getH()/2,img_3->getH()*0.15,10);
      img_3_process->Display_X_Server();
      delete img_3;
      img_3 = img_3_process;
    
      RGBImage *img_4_process = img_4->TiltShifter(img_3->getH()/2,img_3->getH()*0.15,10);
      img_4_process->Display_X_Server();
      delete img_4;
      img_4 = img_4_process;
    }
    
  } 
//8.FisheyeEffect  

  if(option & CASE_FisheyeEffect){
  
      double distortion = 0.0;
    
      cout << "Please enter the distortion rate (0.5~1.5)" << endl;
    
      cin >> distortion;

      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->FisheyeEffect(distortion);
      img_process->Display_X_Server();
      delete img;
      img = img_process;
    
      RGBImage *img_2_process = img_2->FisheyeEffect(distortion);
      img_2_process->Display_X_Server();
      delete img_2;
      img_2 = img_2_process;
  }
//9.Trigger Threshold

  if(option & CASE_Threshold){
  
      cout << "Please enter the threshold value(0~255)" <<endl;
    
      int value = 0;
    
      cin >> value;    
      
      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->Threshold(value);
      img_process->Display_X_Server();
      delete img;
      img = img_process;
  }
//10.Trigger OldPhotoEffect

  if(option & CASE_OldPhotoEffect){
    
      cout << "We use special photo." << endl;
      GrayImage *img_5 = new GrayImage();
      img_5->LoadImage("Image-Folder/Howard.jpg");
      
      cout << "Here are the original pictures!" << endl;
      
      img_5 -> Display_X_Server();
      
      cout << "Procession......." << endl;
    
      GrayImage *img_5_process = img_5->OldPhotoEffect();
      img_5_process->Display_X_Server();
      delete img_5;
      img_5 = img_5_process;
  }


}

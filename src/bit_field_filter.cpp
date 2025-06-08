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
  img_2->LoadImage("Image-Folder/lena.jpg");
  cout << "Here are the original pictures!" << endl;
  img -> Display_X_Server();
  img_2 -> Display_X_Server();
  
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
    cin.ignore();
  
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
  
    GrayImage *img = new GrayImage();
    RGBImage *img_2 = new RGBImage();
  
    img->LoadImage("Image-Folder/city.jpg");

    img_2->LoadImage("Image-Folder/city.jpg");
  
    cout << "Procession......." << endl;
    
    cout << "In order to show the TiltShifter,we use city image." << endl;
    img -> Display_X_Server();
    img_2 -> Display_X_Server();
  
    if(form == 0){
    
      GrayImage *img_process = img->TiltShifter(img->getH()/2,img->getH()*0.15,10);
      img_process->Display_X_Server();
      delete img;
      img = img_process;
    
      RGBImage *img_2_process = img_2->TiltShifter(img_2->getH()/2,img_2->getH()*0.15,10);
      img_2_process->Display_X_Server();
      delete img_2;
      img_2 = img_2_process;
    }

  } 
//8.FisheyeEffect  

  if(option & CASE_FisheyeEffect){
  
      double distortion = 0.0;
    
      cout << "Please enter the distortion rate (0.5~1.5)" << endl;
    
      cin >> distortion;
      cin.ignore();

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
      cin.ignore();    
      
      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->Threshold(value);
      img_process->Display_X_Server();
      delete img;
      img = img_process;

  }  
//10.Trigger OldPhotoEffect

  if(option & CASE_OldPhotoEffect){
  
      GrayImage *img = new GrayImage();
    
      cout << "We use special photo." << endl;
      img->LoadImage("Image-Folder/Howard.jpg");
      
      cout << "Here are the original pictures!" << endl;
      
      img -> Display_X_Server();
      
      cout << "Procession......." << endl;
    
      GrayImage *img_process = img->OldPhotoEffect();
      img_process->Display_X_Server();
      delete img;
      img = img_process;
  }
  
  string filename_gray = "Processing_gary.jpg";
  string filename_rgb = "Processing_rgb.jpg";
  cout<<"Do you want to dump the image?(y/n) : ";
    string ans;
    getline(cin,ans);
    if(ans=="y")
    {  
      string sub1 = filename_gray.substr(filename_gray.length()-4,4);
      filename_gray = filename_gray.substr(0,filename_gray.length()-4);
      filename_gray += "_final"+sub1;
      img->DumpImage("AfterProcessing/"+filename_gray);
      string sub2 = filename_rgb.substr(filename_rgb.length()-4,4);
      filename_rgb = filename_rgb.substr(0,filename_rgb.length()-4);
      filename_rgb += "_final"+sub2;
      img_2->DumpImage("AfterProcessing/"+filename_rgb);
    }

}

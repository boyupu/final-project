#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "image_encryption.h"
#include "bit_field_filter.h"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <sstream>
using namespace std;

void typeWriterEffect(const string& text, int delay_ms) {
    for (char c : text) {
        cout << c <<flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
}



int main(int argc, char *argv[]){

    int flag = 1;
    
    string message[4] = {"This is a code about photo procession!","You have to enter a number to execuate the procession.",
                         "The number is about what procession you want.",
                         "Here is the guide:"};
    
    for(int i = 0 ; i < 4 ; i++){
    
      typeWriterEffect(message[i],20);
      cout << endl;
    }
    
    
    while(flag == 1){
    
    sleep(1);
    
    cout << "enter the procession you want to do." << endl;
    cout << "1.Horizon flip" << endl;
    cout << "2.Mosaic filter" << endl;
    cout << "3.Gaussian filter" << endl;
    cout << "4.Laplacian filter" << endl;
    cout << "5.negative_filter" << endl;
    cout << "6.adjustContrast" << endl;
    cout << "7.TiltShifter" << endl;
    cout << "8.FisheyeEffect" << endl;
    cout << "9.Threshold(just for gray)" << endl;
    cout << "10.OldPhotoEffect(just for gray)" << endl;
    
    int32_t option = 0;
    string op;
    getline(cin,op);
    stringstream read(op);
    int times = (op.begin(),op.end(),'&');
    for(int i = 0 ; i < times ; i++)
    {
      int temp;
      char a;
      read >> temp >> a;
      switch (temp) {                 
        case 1: option = option | CASE_Horizon_flip;   break;
        case 2: option = option | CASE_Mosaic_filter;   break;
        case 3: option = option | CASE_Gaussian_filter; break;
        case 4: option = option | CASE_Laplacian_filter;  break;
        case 5: option = option | CASE_negative_filter;  break;
        case 6: option = option | CASE_adjustContrast;   break;
        case 7: option = option | CASE_TiltShifter; break;
        case 8: option = option | CASE_FisheyeEffect; break;
        case 9: option = option | CASE_Threshold; break;
        case 10: option = option | CASE_OldPhotoEffect; break;
      }
    }
    
    loadCase(option,0);
    
    cout << "If you still want to try"<< endl <<"please enter 1 to continue, else enter 0 to go encryption" << endl;
    
    cin >> flag;
    cin.ignore();
    
  }
  
//encrypt  
    
    GrayImage *img = new GrayImage();
    img->LoadImage("Image-Folder/lena.jpg");
  
    RGBImage *img_2 = new RGBImage();
    img_2->LoadImage("Image-Folder/4-2.jpg");
    
    cout << "Next shows the encrypt function! Here are the original pictures before encryption!" << endl;
    img -> Display_X_Server();
    img_2 -> Display_X_Server();
    
    
    cout << "Please enter the sentence you want to encrypt in the picture." << endl;
    cin.ignore();
    string passwd;
    getline(cin,passwd);
    
    ImageEncryption enc(passwd);
    
    GrayImage *img_process = enc.encrypt_GrayImage(img);
    img_process->Display_X_Server();
    delete img;
    img = img_process;
    
    RGBImage *img_2_process = enc.encrypt_RGBImage(img_2);
    img_2_process->Display_X_Server();
    delete img_2;
    img_2 = img_2_process;
    
    string GaryPassword = enc.decrypt_GrayImage(img);
    cout << "The decoded password in GrayImage: " << GaryPassword << endl;
    
    string RGBPassword = enc.decrypt_RGBImage(img_2);
    cout << "The decoded password in RGBImage: " << RGBPassword << endl;
    
//i dont know how to jump to bitfieldfilter shit
    
    cout << "Thanks for your testing!!!" << endl;
  
    return 0;
}

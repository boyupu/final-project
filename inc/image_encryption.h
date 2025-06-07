#ifndef IMAGE_ENCRYPTION_H
#define IMAGE_ENCRYPTION_H

#include <string>
#include <bitset>
#include <iostream>
#include "image.h"

using namespace std;

class RGBImage;
class GrayImage;

class ImageEncryption {

private:
    string password;

public:
    string getPassword();
    ImageEncryption();
    ImageEncryption(string Pass);

    string char_to_binary(char c);
    string string_to_binary_stream(const string& message);
    RGBImage* encrypt_RGBImage(RGBImage* img);
    GrayImage* encrypt_GrayImage(GrayImage* img);
    string decrypt_RGBImage(RGBImage* img);
    string decrypt_GrayImage(GrayImage* img);
};


#endif
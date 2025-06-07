#include "image.h"

//constructor
Image::Image(int wid,int hei) : w(wid),h(hei)
{}

int Image::getW(){

  return w;

}

int Image::getH(){

  return h;

}

Image::~Image() {}
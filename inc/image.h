#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"

using namespace std;

class Image{
protected:

int w;
int h;
static Data_Loader data_loader;

public:

Image(int wid ,int hie);
virtual ~Image();
virtual bool LoadImage(string filename){};
virtual void DumpImage(string filename){};
virtual void Display_X_Server(){};
virtual void Display_ASCII(){};// use virtual to redefine if necessary

int getW();
int getH();

};

#endif
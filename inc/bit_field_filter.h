#ifndef _BIT_FIELD_FILTER_H_
#define _BIT_FIELD_FILTER_H_

#include<stdio.h>
#include<stdint.h>


#define CASE_Horizon_flip 0b000000000001
#define CASE_Mosaic_filter 0b000000000010
#define CASE_Gaussian_filter 0b000000000100
#define CASE_Laplacian_filter 0b000000001000
#define CASE_negative_filter 0b000000010000
#define CASE_adjustContrast 0b000000100000
#define CASE_TiltShifter 0b000001000000
#define CASE_FisheyeEffect 0b000010000000
#define CASE_Threshold 0b000100000000
#define CASE_OldPhotoEffect 0b001000000000

void loadCase(int32_t option,int form);
void printCase(int32_t option,int form);


#endif
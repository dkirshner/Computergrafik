#pragma once
#include "HSV.h"
#include "CMY.h"
#include "RGB.h"

HSV RGBToHSV(RGB rgb);
RGB HSVToRGB(HSV hsv);
CMY RGBToCMY(RGB rgb);
RGB CMYToRGB(CMY cmy);

double MinHSV(double a, double b);
double MaxHSV(double a, double b);

bool customer_input(float& a_dValue, const char* a_pDesc, const char* a_pModel);
bool customer_input_grad(float& a_dValue, const char* a_pDesc, const char* a_pModel);

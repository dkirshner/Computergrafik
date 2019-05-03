#include "TransformColor.h"
#include <math.h>       /* round, floor, ceil, trunc*/ 
#include <iostream>

double MaxHSV(double a, double b) {
	return a >= b ? a : b;
}

double MinHSV(double a, double b)
{
	return a <= b ? a : b;
}

RGB HSVToRGB(HSV hsv) {
	double r = 0, g = 0, b = 0;

	if (hsv.getSaturation() == 0)
	{
		r = hsv.getValueHSV();
		g = hsv.getValueHSV();
		b = hsv.getValueHSV();
	}
	else
	{
		int i;
		double f, p, q, t;

		if (hsv.getHue() == 360)
			hsv.setHue(0.);

		else
			hsv.setHue(hsv.getHue() / 60);
			

		i = (int)trunc(hsv.getHue());
		f = hsv.getHue() - i;

		p = hsv.getValueHSV() * (1.0 - hsv.getSaturation());
		q = hsv.getValueHSV() * (1.0 - (hsv.getSaturation() * f));
		t = hsv.getValueHSV() * (1.0 - (hsv.getSaturation() * (1.0 - f)));

		switch (i)
		{
		case 0:
			r = hsv.getValueHSV();
			g = t;
			b = p;
			break;

		case 1:
			r = q;
			g = hsv.getValueHSV();
			b = p;
			break;

		case 2:
			r = p;
			g = hsv.getValueHSV();
			b = t;
			break;

		case 3:
			r = p;
			g = q;
			b = hsv.getValueHSV();
			break;

		case 4:
			r = t;
			g = p;
			b = hsv.getValueHSV();
			break;

		default:
			r = hsv.getValueHSV();
			g = p;
			b = q;
			break;
		}
	}

	return RGB((unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255));
}

RGB CMYToRGB(CMY cmy) {
	unsigned char r = (unsigned char)(255 * (1 - cmy.getCyan()/ 255));
	unsigned char g = (unsigned char)(255 * (1 - cmy.getMagenta()/ 255));
	unsigned char b = (unsigned char)(255 * (1 - cmy.getYellow()/ 255));

	return RGB(r, g, b);
}

HSV RGBToHSV(RGB rgb) {
	double delta, min;
	double h = 0, s, v;

	min = MinHSV(MinHSV(rgb.getRed(), rgb.getGreen()), rgb.getBlue());
	v = MaxHSV(MaxHSV(rgb.getRed(), rgb.getGreen()), rgb.getBlue());
	delta = v - min;

	if (v == 0.0)
		s = 0;
	else
		s = delta / v;

	if (s == 0)
		h = 0.0;

	else
	{
		if (rgb.getRed() == v)
			h = (rgb.getGreen() - rgb.getBlue()) / delta;
		else if (rgb.getGreen() == v)
			h = 2 + (rgb.getBlue() - rgb.getRed()) / delta;
		else if (rgb.getBlue() == v)
			h = 4 + (rgb.getRed() - rgb.getGreen()) / delta;

		h *= 60;

		if (h < 0.0)
			h = h + 360;
	}
	s = s / 100;
	v = v/ 100;
	return HSV(h, s, (v / 255));
}

CMY RGBToCMY(RGB rgb) {
	// normalisierung der Farbwerte RGB in intervall [0,1]
	double dr = (double)rgb.getRed() / 255;
	double dg = (double)rgb.getGreen() / 255;
	double db = (double)rgb.getBlue() / 255;

	double c = (1 - dr);
	double m = (1 - dg);
	double y = (1 - db);

	return CMY(c, m, y);
}

bool customer_input(float& a_dValue, const char* a_pDesc, const char* a_pModel)
{
	int iCount = 0;
	char input_str[50];
	bool bInputValid = false;

	while ((a_dValue<0.0 || a_dValue>1.0) && iCount < 10)
	{
		printf("Eingabe von %s %s im Interwall [0,1]:\n", a_pDesc, a_pModel);
		gets_s(input_str);

		if ((input_str[0] == '0' && input_str[1] == '\0') ||
			(input_str[0] == '0' && input_str[1] == '.' && input_str[1] == '\0') ||
			(input_str[0] == '0' && input_str[1] == '.' && (input_str[2] == '0' && input_str[3] == '\0')) ||
			(input_str[0] == '0' && input_str[1] == '.' && (input_str[2] == '0' && (input_str[3] == '0' && input_str[4] == '\0'))))
		{
			bInputValid = true;
			a_dValue = 0.0;
		}
		else
			a_dValue = (float)atof(input_str);

		if (!bInputValid && a_dValue == 0.0)
		{
			a_dValue = -1.0;
			printf("Eingabe liegt ausserhalb von Interwall [0,1]:\n");
		}
		else if (a_dValue<0.0 || a_dValue >1.0)
			printf("Eingabe liegt ausserhalb von Interwall [0,1]:\n");
		// Tastatupuffer freigeben!
		fflush(stdin);
		iCount++;
	}

	a_dValue *= 255;

	return true;
}

bool customer_input_grad(float& a_dValue, const char* a_pDesc, const char* a_pModel)
{
	int iCount = 0;
	char input_str[50];
	bool bInputValid = false;

	while ((a_dValue<0.0 || a_dValue>360.0) && iCount < 10)
	{
		printf("Eingabe von %s %s im Interwall [0,360 Grad]:\n", a_pDesc, a_pModel);
		gets_s(input_str);

		if ((input_str[0] == '0' && input_str[1] == '\0') ||
			(input_str[0] == '0' && input_str[1] == '.' && input_str[1] == '\0') ||
			(input_str[0] == '0' && input_str[1] == '.' && (input_str[2] == '0' && input_str[3] == '\0')) ||
			(input_str[0] == '0' && input_str[1] == '.' && (input_str[2] == '0' && (input_str[3] == '0' && input_str[4] == '\0'))))
		{
			bInputValid = true;
			a_dValue = 0.0;
		}
		else
			a_dValue = (float)atof(input_str);

		if (!bInputValid && a_dValue == 0.0)
		{
			a_dValue = -1.0;
			printf("Eingabe liegt ausserhalb von Interwall [0,360 Grad]:\n");
		}
		else if (a_dValue<0.0 || a_dValue >360.0)
			printf("Eingabe liegt ausserhalb von Interwall [0,360 Grad]:\n");
		// Tastatupuffer freigeben!
		fflush(stdin);
		iCount++;
	}

	return true;
}



#include<stdio.h>
#include <stdlib.h>  // atof
#include <iostream>	 // cout
#include <ostream>	
#include "TransformColor.h"

using namespace std;

int main(int argc, char** argv)
{
	// #1 RGB -Wert eingeben
	float R = 10., G = 10., B = 10.;	// RGB-Modell
	float C = 10., M = 10., Y = 10.;	// CMY-Modell
	float H = 400., S = 10., V = 10.;	// HSV-Modell

	cout << "1. Wert(r, g, b) im RGB Modell vom Benutzer gegeben, Ausgabe des Wertes fuer CMY und HSV Modell" << endl;
	customer_input(R, "ROT", "(RGB-Modell)");
	customer_input(G, "GRUEN", "(RGB-Modell)");
	customer_input(B, "BLAU", "(RGB-Modell)");

	RGB dataRGB = RGB((unsigned char)R, (unsigned char)G, (unsigned char)B);	// 48, 64, 224

	CMY valueCMY = RGBToCMY(dataRGB);
	valueCMY.Output();
	HSV valueHSV = RGBToHSV(dataRGB);
	valueHSV.Output();

	cout << "2. Wert (c,m,y) im CMY Modell vom Benutzer gegeben, Ausgabe des Wertes fuer HSV und RGB Modell" << endl;
	customer_input(C, "CYAN", "(CMY-Modell)");
	customer_input(M, "MAGENTA", "(CMY-Modell)");
	customer_input(Y, "YELLOW", "(CMY-Modell)");
	const CMY dataCMY = CMY((unsigned char)C, (unsigned char)M, (unsigned char)Y);

	RGB valueRGB = CMYToRGB(dataCMY);
	valueRGB.Output();

	HSV valueHSV_1 = RGBToHSV(valueRGB);
	valueHSV_1.Output();

	cout << "3. Wert(h, s, v) im HSV Modell vom Benutzer gegeben, Ausgabe des Wertes fuer RGB und CMY Modell" << endl;
	customer_input_grad(H, "HUE", "(HSV-Modell)");	// Grad
	customer_input(S, "SATURATION", "(HSV-Modell)");
	customer_input(V, "VALUE", "(HSV-Modell)");
	const HSV dataHSV = HSV(H, (float)(S/255.0), (float)(V/255.0));

	RGB valueRGB_2 = HSVToRGB(dataHSV);
	valueRGB_2.Output();

	CMY valueCMY_2 = RGBToCMY(valueRGB_2);
	valueCMY_2.Output();

	system("PAUSE");
	return 0;
}
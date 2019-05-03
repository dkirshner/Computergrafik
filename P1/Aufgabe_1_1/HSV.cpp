#include "HSV.h"
#include <iostream>	 
using namespace std;

HSV::HSV(double a_Hue, double a_Saturation, double a_ValueHSV)
{
	m_H = a_Hue;
	m_S = a_Saturation;
	m_V = a_ValueHSV;
}

void HSV::Output(void)
{
	cout << "---  HSV Ausgabe ---" << endl;
	cout << "H:" << m_H << " (Grad)" << endl; // (double)
	cout << "S:" << (m_S*100.0) << " (Prozent)" << endl;
	cout << "V:" << (m_V*100.0) << " (Prozent)" << endl;
}

//Getter und Setter
double HSV::getHue(void)
{
	return m_H;
}
bool HSV::setHue(double a_val)
{
	if (a_val >= 0 && a_val <= 360)
	{
		m_H = a_val;
	}	
	else
	{
		cout << "Fehler nur Eingaben im Intervall [0,360]" << endl;
		return 1;
	}
	return 0;
}

double HSV::getSaturation(void)
{
	return m_S;
}


bool HSV::setSaturation(double a_val)
{
	if (a_val >= 0 && a_val <= 1)
	{
		m_S = a_val;
	}
	else
	{
		cout << "Fehler nur Eingaben im Intervall [1,0]" << endl;
		return 1;
	}

	return 0;
}

double HSV::getValueHSV(void)
{
	return m_V;
}

bool HSV::setValueHSV(double a_val)
{
	if (a_val >= 0 && a_val <= 1)
	{
		m_V = a_val;
	}
	else
	{
		cout << "Fehler nur Eingaben im Intervall [1,0]" << endl;
		return 1;
	}
	return 0;
}



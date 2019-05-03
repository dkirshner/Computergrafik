#include <iostream>	
#include "RGB.h"

using namespace std;

RGB::RGB(const unsigned char a_Red, const unsigned char a_Green, const unsigned char a_Blue)
{
	m_R = a_Red;
	m_G = a_Green;
	m_B = a_Blue;
}

void RGB::Output(void)
{
	const float fR = (float)m_R, fG = (float)m_G, fB = (float)m_B;
	// RGB Ausgabe
	cout << "---  RGB Ausgabe ---" << endl;
	cout << "R:" << (fR / 255.0) << " (1/255)" << endl;// (float)
	cout << "G:" << (fG / 255.0) << " (1/255)" << endl;
	cout << "B:" << (fB / 255.0) << " (1/255)" << endl;

	//(für Ausgabe in %)
	//cout << "R:" << (fR / 255.0) << " (1/255)" << endl;// (float)

}

//Getter und Setter
unsigned char RGB::getRed(void)
{
	return m_R;
}
bool RGB::setRed(unsigned char a_val)
{
	if(a_val >= 0 && a_val <= 1)
	{
		m_R = a_val;	
	}
	else
	{
		cout << "Fehler nur Eingaben im Intervall [1,0]" << endl;
		return 1;
	}
	return 0;
}

unsigned char RGB::getGreen(void)
{
	return m_G;
}
bool RGB::setGreen(unsigned char a_val)
{
	if (a_val >= 0 && a_val <= 1)
	{
		m_G = a_val;
	}
	else
	{
		cout << "Fehler nur Eingaben im Intervall [1,0]" << endl;
		return 1;
	}
	return 0;
}

unsigned char RGB::getBlue(void)
{
	return m_B;
}
bool RGB::setBlue(unsigned char a_val)
{
	if (a_val >= 0 && a_val <= 1)
	{
		m_B = a_val;
	}
	else
	{
		cout << "Fehler nur Eingaben im Intervall [1,0]" << endl;
		return 1;
	}
	return 0;
}



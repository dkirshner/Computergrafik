#pragma once


class HSV
{
private:// Eigenschaften
	double m_H;
	double m_S;
	double m_V;

public:	
	HSV(double a_Hue, double a_Saturation, double a_ValueHSV);

	void Output(void);

//Getter und Setter
	double getHue(void);
	bool HSV::setHue(double a_val);

	double getSaturation(void);
	bool HSV::setSaturation(double a_val);

	double getValueHSV(void);
	bool HSV::setValueHSV(double a_val);
};


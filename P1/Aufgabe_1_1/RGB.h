#pragma once


class RGB
{
private:
	unsigned char m_R;
	unsigned char m_G;
	unsigned char m_B;

public:
	RGB(const unsigned char a_Red, const unsigned char a_Green, const unsigned char a_Blue);
/*
	bool Equals(RGB rgb)
	{
		return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
	}

	static double Max(double a, double b) {
		return a >= b ? a : b;
	}*/

	void Output(void);

//Getter und Setter

	unsigned char getRed(void);
	bool RGB::setRed(unsigned char a_val);

	unsigned char getGreen(void);
	bool RGB::setGreen(unsigned char a_val);

	unsigned char getBlue(void);
	bool RGB::setBlue(unsigned char a_val);
};

#pragma once
class CMY
{
private:// Eigenschaften liegen im Intervall [0,1]
	double m_C;
	double m_M;
	double m_Y;

public:
	CMY(double a_Cyan, double a_Magenta, double a_Yellow); // Konstuktor

	double getCyan(void);
	bool CMY::setCyan(double a_val);

	double getMagenta(void);
	bool CMY::setMagenta(double a_val);

	double getYellow(void);
	bool CMY::setYellow(double a_val);

	//bool Equals(CMY cmy);

	void Output(void);
};
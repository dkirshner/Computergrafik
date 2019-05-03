#include "CMY.h"

#include <iostream>	
using namespace std;

CMY::CMY(double a_c, double a_m, double a_y)
{
	m_C = a_c;
	m_M = a_m;
	m_Y = a_y;
}
// Getter und Setter
double CMY::getCyan(void)
{
	return m_C;
}

double CMY::getMagenta(void)
{
	return m_M;
}

double CMY::getYellow(void)
{
	return m_Y;
}

bool CMY::setCyan(double a_val)
{
	if (a_val >= 0 && a_val <= 1)
		m_C = a_val;
	else 
	{
		cout << "Bereich nicht im Interval [0,1]" << endl;
		return 1; //Fehler
	}
	return 0;
}

bool CMY::setMagenta(double a_val)
{
	if (a_val >= 0 && a_val <= 1)
		m_M = a_val;
	else
	{
		cout << "Bereich nicht im Interval [0,1]" << endl;
		return 1; //Fehler
	}
	return 0;
}

bool CMY::setYellow(double a_val)
{
	if (a_val >= 0 && a_val <= 1)
		m_Y = a_val;
	else
	{
		cout << "Bereich nicht im Interval [0,1]" << endl;
		return 1; //Fehler
	}
	return 0;
}

void CMY::Output(void)
{
	// CMY Ausgabe
	cout << "---  CMY Ausgabe ---" << endl;
	cout << "C:" << (m_C) << " (Prozent)" << endl;
	cout << "M:" << (m_M) << " (Prozent)" << endl;
	cout << "Y:" << (m_Y) << " (Prozent)" << endl;

	// Für Ausgabe in Prozent)
	//cout << "C:" << (m_C * 100.) << " (Prozent)" << endl;
}









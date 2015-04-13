#include "TempCountry.h"


TempCountry::TempCountry(void)
{
}


TempCountry::~TempCountry(void)
{
}

void TempCountry::setAdjacent(list<string> cAdjacent)
{
	adjacent = cAdjacent;
}

void TempCountry::setX(int cx)
{
	x = cx;
}

void TempCountry::setY(int cy)
{
	y = cy;
}

void TempCountry::setParentCont(string sParent)
{
	parentCont = sParent;
}

void TempCountry::setName(string sName)
{
	name = sName;
}

list<string> TempCountry::getAdjacent()
{
	return adjacent;
}

int TempCountry::getX()
{
	return x;
}

int TempCountry::getY()
{
	return y;
}

string TempCountry::getParentCont()
{
	return parentCont;
}

string TempCountry::getName()
{
	return name;
}
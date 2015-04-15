#pragma once

#include <string>
#include <list>
using namespace std;

/*
Class TempCountry: A class used for temporary storage in the loading and saving process of country objects
*/
class TempCountry
{
public:
	TempCountry(void);
	~TempCountry(void);
	void setAdjacent(list<string> adjacent);
	void setX(int x);
	void setY(int y);
	void setParentCont(string parent);
	void setName(string name);

	list<string> getAdjacent();
	int getX();
	int getY();
	string getParentCont();
	string getName();

private:
	int x;
	int y;
	string parentCont;
	list<string> adjacent;
	string name;


};


#pragma once
#include <string>

/*
Class Card: 
	A collection of the number a single type of card held by a player
*/
class Card
{
public:
	inline Card(){}
	Card(int newQuantity, int newTypeNum);
	~Card();
	void setType(int mType);
	std::string getType(int num);
	void setQuantity(int mQuantity);
	int getQuantity();
	void incrementQuantity();
	void decrementQuantity(int qty);

private:
	std::string type;
	int quantity;
};
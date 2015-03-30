#pragma once
#include <string>

class Card
{
public:
	Card();
	~Card();
	void setType(int mType);
	int getType();
	void setQuantity(int mQuantity);
	int getQuantity();
	void incrementQuantity();
	void decrementQuantity(int qty);
	static int numOfArmiesExchange;

private:
	int type;
	int quantity;
};
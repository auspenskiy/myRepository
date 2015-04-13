#pragma once
#include <string>

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
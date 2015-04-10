#include "Card.h"

Card::Card()
{
	quantity = 0;
}


Card::~Card()
{
	  
}

//sets a type of a given card 0 for infantry, 1 for cavalry 2 for artillery
void Card::setType(int num)
{
	std::string cardType;
	switch (num)
	{
	case 0:
		cardType = "infantry";
		break;
	case 1:
		cardType = "cavalry";
		break;
	case 2:
		cardType = "artillery";
		break;
	}
	type = cardType;
}
std::string Card::getType(int num)
{
	std::string cardType;
	switch (num)
	{
	case 0:
		cardType = "infantry";
		break;
	case 1:
		cardType = "cavalry";
		break;
	case 2:
		cardType = "artillery";
		break;
	}
	return cardType;
}

void Card::setQuantity(int mQuantity)
{
	quantity = mQuantity;
}
int Card::getQuantity()
{
	return quantity;
}

void Card::incrementQuantity()
{
	quantity++;
}

void Card::decrementQuantity(int qty)
{
	quantity = quantity - qty;
}

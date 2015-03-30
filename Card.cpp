#include "Card.h"

Card::Card()
{
	
}


Card::~Card()
{

}

//sets a type of a given card 0 for infantry, 1 for cavalry 2 for artillery
void Card::setType(int mType)
{
	type = mType;
}
int Card::getType()
{
	return type;
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

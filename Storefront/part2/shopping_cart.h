#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include "item.h"

class ShoppingCart
{
	Item** items; //1D dynamic array of pointers to items in the shopping cart
	int itemCount; //How many items are in the shopping cart
	int itemsArrSize; //Size of the items array

	const int RESIZE_AMOUNT = 4;

	void resizeArray();

public:
	ShoppingCart();
	ShoppingCart(int);
	~ShoppingCart();

	void addItem(Item*);
	void printCart();
	float getTotalCost();
};

#endif

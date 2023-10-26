#ifndef STORE_H
#define STORE_H

#include "shopping_cart.h"
#include <iostream>
#include <fstream>

using namespace std;

//Store class for actually selling things and interfacing with the catalog of items
class Store
{
	Item** itemCatalog; //Array of items available for purchase. This is a 1D array of Item*s 
	int catalogSize; //Size of the itemCatalog array
	int itemSelection[SELECTION_SIZE]; //Which items from the itemCatalog are available to buy
	int base, lastItem; //Base for random permutations and the index in the catalog of the last item added
public:
	Store();
	~Store();
	void readItemsFromFile(istream& itemsFile);
	void randomlyPopulateStore();
	void displayStore();
	void printCatalog();
	bool promptToBuy(ShoppingCart& cart);
	void swapOutItem(int index);
};

#endif

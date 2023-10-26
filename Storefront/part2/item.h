#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

const int SELECTION_SIZE = 5; //How many items to randomly offer for purchase

//Class for Items that can be purchased from the store front
class Item
{
	string name;
	int quantity;
	float price;

	const char BOX_CHAR = '#';
	const int BOX_WIDTH = 42;

public:

	//Constructors
	Item() {}
	Item(string name, int quantity, float price)
	{
		this->name = name;
		this->quantity = quantity;
		this->price = price;
	}

	//Function to print the values of the Item in a nice format for displaying on the store page
	void printItemBox()
	{
		cout << setfill(BOX_CHAR) << setw(BOX_WIDTH) << "" << endl;
		cout << BOX_CHAR << setw(10) << setfill(' ') << right << "___  " << setw(BOX_WIDTH - 13) 
			<< name <<  ' ' << BOX_CHAR << endl;
		cout << BOX_CHAR << setw(10) << "/\\   \\ " << setw(BOX_WIDTH - 11) << BOX_CHAR << endl;
		cout << BOX_CHAR << setw(10) << "/  \\ _ \\" << setw(26) << "Q: " << setw(BOX_WIDTH - 39) << quantity << ' ' << BOX_CHAR << endl;
		cout << BOX_CHAR << setw(10) << "\\  /   /" << setw(BOX_WIDTH - 17) << "$" << setprecision(2) << fixed 
			<< price << ' ' << BOX_CHAR << endl;
		cout << BOX_CHAR << setw(10) << "\\/___/ " << setw(BOX_WIDTH - 11) << BOX_CHAR << endl;
		cout << setfill(BOX_CHAR) << setw(BOX_WIDTH) << "" << endl;

		//Reset formatting constants
		cout << setfill(' ') << left << defaultfloat;
	}

	//Function to print the values of the Item on one single line
	void printItemInfo()
	{
		cout << setw(32) << left << name << " x" << setw(6) << right << quantity << "  $" << setprecision(2) << fixed
			<< price << endl;

		cout << left << defaultfloat;
	}

	//Changes the quantity of this item by the given amount
	void changeQuantity(int change) { quantity += change; }

	//= overload for easier usage with ShoppingCart class
	void operator = (Item other) 
	{ 
		this->name = other.name; 
		this->quantity = other.quantity;
		this->price = other.price;
	}

	string getName() const { return name; }
	int getQuantity() const { return quantity; }
	float getPrice() const { return price; }
};

#define ItemRef Item*

#endif

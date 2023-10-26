/*
Name: Melissa Swinehart, 8001176124, 1006, ASSIGNMENT 4
Description: Adding item to array and resizing it
if out of space
Input: No user input
Output: Prints items and shopping cart
*/

#include "shopping_cart.h"

//Function to add the item parameter to the end of the items array.
void ShoppingCart::addItem(Item* item)
{

	//If items equal the size of array, resize
	if(itemCount == itemsArrSize){
		resizeArray();
	}
	//Add the item to end of array
	items[itemCount] = item;
	//Increment
	itemCount++;
}

/* */
void ShoppingCart::resizeArray()
{
	//This should make the items array bigger by the const RESIZE_AMOUNT.
	
	//Make a new, bigger array
	//Set reSize equal to resizeamount (4) + the itemCount in old array
	int reSize = itemsArrSize + RESIZE_AMOUNT;
	//Create new array of pointers equal to item objects with new size
	Item** newArray = new Item*[reSize];
	//Then, copy over the elements from the old array to new array 
	for(int i = 0; i < itemCount; i++){
		newArray[i] = items[i];
	}
	//Deallocate the old array (Remember how to specifically deallocate an array!)
	delete[] items;
	//And then finally update the size to reflect the size of the newly 
	itemsArrSize = reSize;
	//allocated items array. Make sure to update any pointers as needed.
	//1D array of pointers equals new array of pointers
	items = newArray;
	itemsArrSize = reSize;

}

//printCart function to print all of the Items in the ShoppingCart
void ShoppingCart::printCart()
{
	for(int i = 0; i < itemCount; i++){
	items[i] -> printItemInfo();

}
	
}
//getTotalCost function to find the total cost of all the Items in the ShoppingCart
float ShoppingCart::getTotalCost()
{   //Initialize total cost to 0
	float getTotalCost = 0.0;
	//for loop to iterate through each item in shopping cart
	for(int i = 0; i < itemCount; i++){
		//retrieve pointer
        Item* cartItem = items[i];
		//set quantity
        int Quantity = cartItem -> getQuantity();
		//set price
        float Price = cartItem -> getPrice();
		//Multiply all items to get totalcost
        float totalCost = Quantity * Price;
		//have a running total
        getTotalCost += totalCost;
    }
    return getTotalCost;
}
/* */
ShoppingCart::~ShoppingCart()
{
	//Clear out the shopping cart by first deleting all of the items contained within it
	for(int i = 0; i < itemCount; i++){
		delete items[i];
	}
	//Then, deallocate the array that held all of those items
	delete[] items;

}

// -------------------------- Constructors --------------------------

//Default constructor
ShoppingCart::ShoppingCart()
{
	//This should initialize the shopping cart to be empty by making the items array point to null
	//The count and size should be 0
	items = nullptr;
	itemCount = 0;
	itemsArrSize = 0;
}

//Constructor that initializes the array to a given size
ShoppingCart::ShoppingCart(int initial_size)
{
	//This constructor should construct an empty shopping cart, but allocate an array of the given size
	//Initialize the items array using the size, set the size variable, and initialize count to 0

	items = new Item*[initial_size];
	itemCount = 0;
	itemsArrSize = initial_size;
}
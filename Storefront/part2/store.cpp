/*
Name: Melissa Swinehart, 8001176124, 1006, ASSIGNMENT 4
Description: Reading from file and storing
information
Input: No user input
Output: Prints items and shopping cart
*/
#include "store.h"
#include "shopping_cart.h"

//This function should should initialize the itemCatalog array.
//The array is dynamically allocated - that is, it is created during the runtime of the program.
void Store::readItemsFromFile(istream& itemsFile)
{

	


//Initialize both the itemCatalog array and the catalogSize
	string tempName;
	int tempQuantity;
	float tempPrice;

	itemsFile >> catalogSize;

	itemCatalog = new Item*[catalogSize];
//Afterwards, each line contains 3 values representing one item: the quantity, price, and name of each item
	for(int i = 0; i < catalogSize; i++){
//Read in these 3 values with appropriate data types and use them to construct an Item and place it into the array
		itemsFile >> tempQuantity >> tempPrice;
		getline(itemsFile, tempName);

		itemCatalog[i] = new Item(tempName, tempQuantity, tempPrice);
	}
}

/* Destructor for the Store class that deallocates all of
 the items in the itemCatalog, followed
by the catalog itself.*/
Store::~Store()
{
	for(int i = 0; i < catalogSize; i++){
		delete itemCatalog[i];
	}
	delete[] itemCatalog;

}

//------------------------------------------- SKELETON CODE -------------------------------------------

//Used for making a random permutation of Items
int primitiveRoots[] = { 3, 6, 7, 13, 14, 15, 19, 23, 24, 26, 27, 28, 29, 30, 31, 33, 35, 38, 41,
43, 46, 48, 51, 54, 56, 58, 59, 60, 61, 62, 63, 65, 66, 70, 74, 75, 76, 82, 83, 86 };
const int ROOTS_COUNT = 40;
const int N = 89;

Store::Store()
{
	itemCatalog = nullptr; 
	catalogSize = 0; 
	base = primitiveRoots[rand() % ROOTS_COUNT]; 
	lastItem = base;
}

//Randomly initializes the store's item selection with a number of items from the itemCatalog
void Store::randomlyPopulateStore()
{
	//Find the first index in the permutation sequence that is in bounds of the catalog
	while (lastItem > catalogSize)
		lastItem = (lastItem * base) % N;
	itemSelection[0] = lastItem - 1; //Add the first item selected from the constructor

	//Populate the itemSelection until the array is full
	for (int itemsPicked = 1; itemsPicked < SELECTION_SIZE; itemsPicked++)
		swapOutItem(itemsPicked);
}

//Displays all of the items in the store using the printItemBox function
void Store::displayStore()
{
	cout << "--------------- Store Front ---------------" << endl << endl;
	for (int i = 0; i < SELECTION_SIZE; i++)
	{
		itemCatalog[itemSelection[i]]->printItemBox();
		cout << endl;
	}
	cout << "-------------------------------------------" << endl << endl;
}

//Prints the item catalog for debugging purposes
void Store::printCatalog()
{
	for (int i = 0; i < catalogSize; i++)
	{
		itemCatalog[i]->printItemInfo();
		cout << endl;
	}
}
	

//Prints a prompt to the screen offering items to buy
//Returns true if the user sucessfully bought something and false if they quit shopping
bool Store::promptToBuy(ShoppingCart& cart)
{
	cout << "What would you like to buy? Please enter a letter for your choice." << endl;
	for (int i = 0; i < SELECTION_SIZE; i++)
		cout << (char)('A' + i) << ": " << itemCatalog[itemSelection[i]]->getName() << endl;
	cout << "Q: Quit Shopping" << endl;

	//Read the input from the user
	char choice;
	cin >> choice;

	choice = toupper(choice); //Make all letters capital for easier checking
	if (choice == 'Q') //If user chose to quit, then return false to signal that
		return false;
	if ((choice < 'A' || choice >('A' + SELECTION_SIZE))) //If the choice was not valid, try again
		return promptToBuy(cart);

	//Else if the choice was valid, buy the item, add it to the shopping cart and return true
	ItemRef item = itemCatalog[itemSelection[choice - 'A']]; //Get a reference to the item
	if (item->getQuantity() == 0) //If out of stock, print a message
	{
		cout << "That item is out of stock. Please check back in later" << endl;
		return true;
	}

	int buyQuantity = -1;
	int itemQuantity = item->getQuantity(); //Used to avoid calling the getQuantity getter frequently
	cout << "How many would you like to purchase? (1-" << itemQuantity << ")" << endl;
	cin >> buyQuantity; //Read the number they would like to buy
	//Reprompt when either a bad read happened or the number is invalid
	while (cin.fail() || buyQuantity < 0 || buyQuantity > itemQuantity)
	{
		cout << "I'm sorry, I didn't understand that. Please enter a number between 1 and " << itemQuantity << endl;
		cin.ignore(1024); //Clear the buffer
		cin.clear(); //Clear the flag
		cin >> buyQuantity;
	}

	//Buy the number of items requested
	item->changeQuantity(-1 * buyQuantity);
	//Add the items to the shopping cart
	cart.addItem(new Item(item->getName(), buyQuantity, item->getPrice()));

	//If the item bought is now out of stock, replace it
	if (itemQuantity == buyQuantity)
		swapOutItem(choice - 'A');
		
	return true;
}

//Swaps out the item with the given index in the item selection array. 
//If there are no more items that are able to be sold left, this will not swap the item out
void Store::swapOutItem(int index)
{
	//If out of items, don't swap out
	if (lastItem == -1)
		return;

	//If this is the last item to add
	if (lastItem == 1)
	{
		itemSelection[index] = 0;
		lastItem = -1; //Mark lastItem as -1 so we don't continue through the permutation
		return;
	}

	lastItem = (lastItem * base) % N; //Go to the next item before determining if valid

	//Find the first value in the permutation within the bounds of the array to be safe
	while (lastItem > catalogSize)
		lastItem = (lastItem * base) % N; //Get the next number in the permutation

	//Move the item index further into the primitive roots sequence until a valid position is found
	while (itemCatalog[lastItem - 1]->getQuantity() <= 0 && lastItem != 1)
		while (lastItem > catalogSize)
			lastItem = (lastItem * base) % N; //Get the next number in the permutations

	//Check if the itemIndex has a quantity of 0, in which case we can return
	if (itemCatalog[lastItem - 1]->getQuantity() <= 0)
	{
		lastItem = -1; //Mark as stock out for later
		return;
	}

	//Otherwise, place the new item into the item selection
	itemSelection[index] = lastItem - 1;
}
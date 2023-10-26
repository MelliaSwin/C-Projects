#include "../shopping_cart.h"
#include "../store.h"
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	//Check the command line arguments

	if (argc > 3 || argc < 2) //If there are too few or too many args, print an error and continue
	{
		cout << "ERROR: Incorrect Usage" << endl;
		cout << "Usage: ./store <input_file> <optional_seed>" << endl;
		return 1;
	}

	//Try to open the input file
	ifstream infile(argv[1]);
	if (!infile.good())
	{
		cout << "Could not open file: " << argv[1] << endl;
		return 1;
	}

	//Try to set up the seed for RNG
	int seed;
	if (argc == 3) //If a command line arg was provided for the seed, try to parse it
	{
		//Handle the seed
		try { seed = stoi(argv[2]); }
		catch (...)
		{
			cout << "ERROR: Invalid Argument" << endl;
			cout << "Could not convert " << argv[2] << " to an integer." << endl;
			cout << "Usage: ./store <input_file> <optional_seed>" << endl;
			return 1;
		}
	}
	else //If no seed was provided, seed based on the time
		seed = (int)time(NULL);

	//Create the store from the file
	Store store;
	ShoppingCart cart;
	srand(seed); //Seed the RNG
	store.readItemsFromFile(infile); //Populate the item catalog from the file
	store.randomlyPopulateStore(); //Randomly populate the store front
	infile.close();

	//Do the main loop for shopping
	store.displayStore();
	while (store.promptToBuy(cart)) //Prompt the user to buy something or quit out
		store.displayStore(); //Display the Store's items

	//Now that shopping is done, print the results of shopping
	cout << endl << "--------------- Cart at Checkout ---------------" << endl;
	cart.printCart();
	cout << endl << "Total: $" << setprecision(2) << fixed << cart.getTotalCost() << endl;
}
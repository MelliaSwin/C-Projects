/*
* Name: Melissa Swinehart, NSHE: 8001176124, 1020, AS8
* Description: A simple banking application
utilizing structs to model bank accounts
and transactions
* Input: Account number, pin code, and options listed
* Output: Menu options and their actions
*/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

//Two Structs & it's Attributes
struct Transaction{
    string type; //Stores Withdrawal & Deposit
    double amount; // Holds a decimal representing deposit/withdrawal
};
struct Account{
    int accountNumber; //Bank account number
    int pin; //Pin Code
    double balance; //Current Balance
    vector <Transaction> transactions; //Vector of transactions
};

int main(){
    cout << endl;
//Header
cout << "-------- Welcome to the Banking Application --------" << endl;
cout << endl;
//Create bank account instances
Account account_list[5];
//First account
account_list[0].accountNumber = 111000;
account_list[0].balance = 65938.91;
account_list[0].pin = 123456;
//Second Account
account_list[1].accountNumber = 111001;
account_list[1].balance = 100.53;
account_list[1].pin = 123456;
//Third Account
account_list[2].accountNumber = 111002;
account_list[2].balance = 25.13;
account_list[2].pin = 123456;
//Fourth Account
account_list[3].accountNumber = 111003;
account_list[3].balance = 100983.11;
account_list[3].pin = 123456;
//Fifth Account
account_list[4].accountNumber = 111004;
account_list[4].balance = 83764.17;
account_list[4].pin = 123456;

//Outer While loop for another transaction
bool another_transaction = true;
while (another_transaction){

//Asking User to enter account number or -1 to exit
//While loop to validate account number
int account_num = 0;
while (true){
    cout << "Enter account number or -1 to exit: \n";
    cin >> account_num;
    //Check if user enters anything other than numeric input
if(cin.fail()){
    cout <<"Account number must consist of 6 digits\n";
    cin.clear();
    cin.ignore(256,'\n');
    continue;
}
    //If user enters -1, terminate application
    if (account_num == -1){
            cout << "Thank you!" << endl;
            return 0;
        }
    // If not, validate the account number
    //Check for number of digits using to_string 
    //function and check length
    string account_str = to_string(account_num);
    //If length is not 6 numbers exactly, reprompt the user
    if (account_str.length() != 6){
            cout << "Account number must consist of 6 digits\n";
            continue; //Continue from beginning of while loop
        }

//Once account number is 6 digits exactly, check if found
bool found = false;
//For loop iterating over indexs
for (int i = 0; i < 5; i++){
    //If account number is in the list, set bool to true
    if (account_list[i].accountNumber == account_num){
                found = true;
                break; //Break out of loop
            }
        }
        //If account number is not found, reprompt user
        if (!found){
            cout << "Incorrect account number!\n";
            cout << "Try again or enter -1 to exit\n";
        } else {
            //Break out of loop
            break;

        }
    }
//While loop to validate pin code
int attempts = 3;
int pin_code = 0;
bool found = false;
while (attempts > 0){
    cout << "Enter pin:\n";
    cin >> pin_code;
//Check if input contains only digits)
if(cin.fail()){
    cout << "Pin should contain numbers only\n";
    cin.clear();
    cin.ignore(256,'\n');
    continue;
}
//Check if pin code is found, if not, decrease attempts
for(int i = 0; i < 5; i++){
    if(account_list[i].pin == pin_code){
        found = true;
        break;
    }
}
//If pin code found,decrease attempt
    if(!found){
        cout << "Incorrect pin\n";
        attempts--;
//Once found, break
    }else{
        break;
    }
}
//If attempts reaches 0, terminate application
if(attempts == 0){
cout << "You have exceeded the number of allowed pin attempts\n";
    cout << "See a banker to complete your transaction\n";
    cout << "Thank you!";
    return 0;
}
//If account number is found, 
//prompt user to select option from menu
int option = 0;
while (true){
cout << "Select from menu: \n";
cout << "1. Withdraw.\n";
cout << "2. Deposit.\n";
cout << "3. Show balance.\n";
cout << "4. Show transactions.\n";
cout << "5. Cancel.\n";
cin >> option;
//Switch statement for options
switch(option){
case 1:{ //Withdraw option
double withdraw_amount = 0;

cout << "Enter amount to withdraw: \n$ ";
cin >> withdraw_amount;
//Use For loop to iterate over index
//and check if account has sufficient balance
int i = 0;
for(i = 0; i < 5; i++){
    if (account_list[i].accountNumber == account_num){
        break;
        }
    }
//If the withdraw amount is greater than account balance, 
//it's insufficient
if(withdraw_amount > account_list[i].balance){
    cout << "Insufficient balance!\n";
    cout << "Transaction cancelled.\n";
    break;
//If not, withdrawal the amount requested
    }else{
        //Subtract the withdrawal amount from the balance
        account_list[i].balance -= withdraw_amount; //Update the balance
        //Create withdrawal transaction instance
        Transaction withdrawal;
        //Withdrawal string stored in withdrawal.type
        withdrawal.type = "withdrawal";
        //Amount stored in withdraw_amount
        withdrawal.amount = withdraw_amount;
        //Vector used to pushback this new information
        account_list[i].transactions.push_back(withdrawal);
        //Display the new balance
        cout << "New balance: $" << account_list[i].balance << endl;
    }
    break;
}
case 2:{//Deposit Option
double deposit_amount = 0;

cout << "Enter amount to deposit: \n$ ";
cin >> deposit_amount;
//Use For loop to iterate over index
int i = 0;
for(i = 0; i < 5; i++){
    if (account_list[i].accountNumber == account_num){
        break;
        }
    }
//Add the deposit amount to the balance
account_list[i].balance += deposit_amount;
//Create deposit transaction instance
Transaction deposit;
//Deposit string stored in deposit.type
deposit.type = "deposit";
//Amount stored in deposit_amount
deposit.amount = deposit_amount;
//Vector used to pushback this new information
account_list[i].transactions.push_back(deposit);
//Display the new balance
cout << "New balance: $" << account_list[i].balance << endl;
break;
}
case 3:{//Check balance
//For loop to iterate over index and output the balance
int i = 0;
for (i = 0; i < 5; i++){
if (account_list[i].accountNumber == account_num){
break;
}
}
//Output currenct balance
cout << "Current balance: $" <<  fixed << setprecision(2) 
<< account_list[i].balance << endl;
break;
}
case 4:{ //Show transactions option
//For loop to iterate over index and show transactions
int i = 0;
for(i = 0; i < 5; i++){
    if(account_list[i].accountNumber == account_num){
        break;
    }
}
//Check if any recent transactions were made
if(account_list[i].transactions.size() == 0){
    cout << "No recent transactions found\n";
    break;
}
//Output the transactions made
for (unsigned int j = 0; j < account_list[i].transactions.size(); j++){
 cout << j+1 << "- " << "Type: " << account_list[i].transactions[j].type 
 << ", " << "Amount:"
 <<" $" << fixed << setprecision(2) 
 << account_list[i].transactions[j].amount 
 << endl;
        }
        break;

break;
}
case 5://Cancel Option
break;
default:
break;
}
//Ask user if they would like to make another transaction
char response = ' ';
cout << "Would you like another transaction? (y/n)" << endl;
cin >> response;

if(response == 'N' || response == 'n'){
    another_transaction = false;
    cout << "Thank you!" << endl;
}else if (response == 'Y' || response == 'y'){
    another_transaction = true;
}else{
    cout << "Thank you!" << endl;
    another_transaction = false;
}
break;
}


}
    return 0;
}
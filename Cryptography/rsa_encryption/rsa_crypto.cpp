/*
* Name: Melissa Swinehart, 8001176124, As1 P2
* Description: Encrypting and decrypting
 message using RSA
* Input: User inputs prime numbers, RP numbers, and
files
* Output: Encryption and Decryption of the 
message
*/

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cmath>
using std::pow;
using std::sqrt;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::stol;
using std::string;

const int base = 27;

ifstream _open_input_file(string file_name) {
//Checks if file opened
  ifstream input;
  input.open(file_name);

  if(!input){
    cout << endl;
    cout << "ERROR: Could not open file : " << file_name << endl;
    exit(-1);
  }
  return input;
}

ifstream open_input_file() {
//Prompts user to input file

  string input_file;
  cout << "Please enter the name of your input file: ";
  cin >> input_file;
 cout << "\n";
  return _open_input_file(input_file);
  
  
}


ofstream _open_output_file(string file_name) {
 
//Checks if file opened
  ofstream output;
  output.open(file_name);

  if(!output){
    exit(-1);
  }
  return output;
}


ofstream open_output_file() {
//Prompts user to enter a file
    string output_file;
  cout << "Please enter the name of your output file: ";
  cin >> output_file;
 cout << "\n";
  return _open_output_file(output_file);
}

/**
 * @brief Tests if number is prime or not
 *
 * @param long p
 * @return true
 * @return false
 *
 */
bool prime_test(long p) {
  // Cover simple base cases
  if (p == 2 || p == 3) return true;
  if (p <= 1 || p % 2 == 0 || p % 3 == 0) return false;

 
  //Iterate from 3 to sqrt of our number
  for(int i = 2; i <= sqrt(p); i++){
  //if p % i gives remainder of 0, then
  //p isn't prime
  if(p % i == 0){
    return false;
  }
}

return true;
}

/**
 * @brief Euclid's GCD Algorithm
 *
 * @param num Numerator
 * @param den Denominator
 * @return int, Greatest Common Divisor
 *
 */
int gcd(int num, int den) {
  int quot, rem;
  while (den > 0) {
    rem = num % den;
    num = den;
    den = rem;
  }
  return num;
}

/**
 * @brief Prompts user for block
 * if block doesn't satisfy condition
 * then display error
 *
 * @param int& block
 *
 */
void prompt_user_block(int& block) {
//Bool is set to false
  bool isBlock = false;
  while(!isBlock){
    cout << "Enter plaintext block size: ";
    cin >> block;
//Error if block is less than or equal to 1
    if(block <= 1){
       cout << "\nERROR: block size must be greater than 1!";
        cout << "\n";
        //Set bool to false and keep iterating until correct
        //number
        isBlock = false;
    }else{
      //Set bool to true and exit loop
      isBlock = true;
    }
  }
  cout << "\n";
}

/**
 * @brief Checking if number is prime
 *
 * @param int& p
 *
 */
void _prompt_user_prime(int& p) {

  //Bool is set to false
  bool prime = false;

  while(!prime){

  cout << "Enter sufficiently large prime number: ";
  cin >> p;
  //If bool is returned false, keep iterating until
  //correct answer
  if(!prime_test(p)){
    cout << "\nERROR: " << p << " is not prime!\n";
  }
  else{
    //Set bool to true to exit loop
    prime = true;
  }

  }
  cout << "\n";
}

/**
 * @brief Both prime numbers must satisfy
 * conditions displayed below
 *
 * @param int& p
 * @param int& q
 * @param int block
 *
 * Hint: Use the pow function from the math library here
 */
void prompt_user_prime(int& p, int& q, int block) {
  for (;;) {

    _prompt_user_prime(p);
    _prompt_user_prime(q);
//If p equals q, display error message
    if (p == q) {
      cout << "\nERROR: p cannot equal q!" << endl;
      continue;
//if p * q is less than the power of 27 ^ block
//display error message
    } else if ((p * q) <= pow(base, block)){
      cout << "ERROR: p * q must be larger than " << base << "^"
        << block <<  "!" << endl;
      continue;
    } else {
      break;
    }
  }
}

/**
 * @brief Prompts user to enter value that
 * is relative prime to phi_n
 *
 * @param long& e
 * @param long phi_n
 */
void prompt_user_relative_prime(long& e, long phi_n) {
 
bool isValid;
//Do while loop to iterate until user enters a
//valid number
do{
    isValid = true;
cout << "Enter value that is relative prime to " << phi_n << ": ";
cin >> e;
//If number is greater than phi_n, display error message
if(e > phi_n){
    
    cout << "\nERROR: value must be less than " << phi_n;
    cout << "\n";
    isValid = false;

} else if(e < phi_n){
  //If the gcd is not equal to 1, display error message
  // and set the bool to false
    if (gcd(e, phi_n) != 1){

  cout << "\nERROR: " << e << " is not relatively prime to " 
  << phi_n << "!";
  isValid = false;
  cout << "\n";
}

}

}while(!isValid);

}

/**
 * @brief Function to generate all values that are 
 * relatively prime to the Euler
 * totient phi(n)
 *
 * @param phi_n Euler totient phi(n) calculated from 
 * the prime values p and q
 *
 */
void generate_relative_primes(long phi_n) {
  cout << "\nGenerating all values relatively prime to " 
  << phi_n << endl;

  int SI = 1;
  int versa = phi_n;

  do {
    versa /= 10;
    SI++;
  } while (versa != 0);

  for (int i = 2; i < phi_n; i++) {
    if (gcd(i, phi_n) == 1) {
      cout << setw(SI) << i << ",";
      if (++versa % 10 == 0) cout << endl;
    }
  }
  cout << endl;
}

/**
 * @brief Function to generate the private key given the public key
 * and prime product (p * q) or n
 *
 * @param a Public Key (e)
 * @param n Prime product (p * q)
 * @return long, private key
 *
 * @bug
 *  There are instances where negative private keys are generated
 */
long generate_private_key(long a, long n) {
  long d = 1, d_temp = 0;
  long quotient, versa;
  while (n) {
    quotient = a / n;
    versa = a;
    a = n;
    n = versa - quotient * n;
    versa = d;
    d = d_temp;
    d_temp = versa - quotient * d_temp;
  }
  return d < 0 ? d + n : d;
}

// Place the file handler functions here

/**
 * @brief Function to apply a key to either a piece of cipher 
 * text or plain text
 * Thus is the beauty of encryption that the methods of encryption and
 * decryption are identical but with differnt parameters
 *
 * @param key Public or Private Key
 * @param n Prime product (p * q)
 * @param text Message to be encrypted or decrypted
 * @return long, Encoded or Decoded message
 */
long apply_key(long key, long n, long text) {
  long msg = 1;
  while (key--) {
    msg *= text;
    msg %= n;
  }
  return msg;
}

/**
 * @brief This function serves to both encode a plaintext ascii
 * and send that encoding off to the apply_key function for
 * encryption
 *
 * The message to be encrypted exists within a file and must be read
 *
 * For each block the function encrypts it will write that data
 * to an output file separated by newlines
 *
 * @param key Public Key (e)
 * @param n Prime Product (p * q)
 * @param block Amount of characters encoded in each block
 *
 * @details
 * Hint: The given for loop will parse each block of the message
 * Embbed a for loop to implement the series composition
 */
void encrypt_message(long key, long n, int block) {
  int power; // Used to raise a base power
  int power_i;
  long cipher; // Used to store the series compound
  string message;
  char letter;
  int num;

  ifstream input = open_input_file();
  ofstream output = open_output_file();
  getline(input, message);
  input.close();

int i = 0;
int mes_length = message.length();

while(i < mes_length){
  //create a substring from the index
  //only take block amount in message
    string substring = message.substr(i, block);
    //reset total_cypher to 0
    //in order to add values of each block
    //of characters
    cipher = 0;
    
//For loop to start at highest index in
//set of block and decrement down
for (int j = block - 1; j >= 0; j--){
     if (j < substring.length()){
//Stores character at index j into letter
letter = substring[j];
//Use ASCIIvalue to subtract letter and
//get a number equivalent to letter
     if (letter != ' '){
      num = letter - 65;
      }else{
        num = 0;
        }
//Equation to set power to 0
//and increment up
power = block - 1 - j;
power_i = num * pow(base, power);
cipher += power_i;

        }
    }
    
    output << apply_key(key, n, cipher) << endl;
//Start at the next block of message
//i will multiply from block in order to begin next set of
//3 characters
   i+= block;  
}
output.close();
}
/**
 * @brief This function serves to both decrypt, decode, 
 * and then display
 * the original encrypted data
 *
 * The encrypted data was generated by the encrypt_message
 *  function and was
 * stored in a file. Each row of the file represents an
 *  encrypted block of data
 *
 * @param key Private Key (d)
 * @param n Prime Product (p * q)
 * @param block Amount of characters encoded in each block
 */
void decrypt_message(long key, long n, int block) {
  long cipher;
  int power;
  char letter;

  string message, original;
  ifstream input = open_input_file();

  while (getline(input, message)) {
    cipher = apply_key(key, n, stol(message));
    for (int i = block - 1; i >= 0; i--) {
      power = (int)pow(base, i);

      letter = cipher / power;
      letter = letter != 26 ? letter + 65 : ' ';

      original += letter;
      cipher %= power;
    }
  }
  cout << original << endl;

  input.close();
}

/**
 * @brief Serves to demonstrate the efficacy of 
 * all the functions implemented
 * above
 *
 * @param argc Count of command line parameters
 * @param argv Array of command line paramters
 * @return int, Status
 */
int main(int argc, char const* argv[]) {
  int block, p, q;
  long n, phi_n, e, d;

  prompt_user_block(block);

  prompt_user_prime(p, q, block);

  n = p * q;
  phi_n = (p - 1) * (q - 1);

  // generate_relative_primes(phi_n);

  prompt_user_relative_prime(e, phi_n);

  d = generate_private_key(e, phi_n);

  cout << "\nPrivate key = " << d << endl;
  
  cout << "Encrypting Message" << endl;
  encrypt_message(e, n, block);

  cout << "Decrypting Cipher" << endl;
  decrypt_message(d, n, block);


  return 0;
}

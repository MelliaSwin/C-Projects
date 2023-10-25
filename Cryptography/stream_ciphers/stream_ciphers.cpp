/*
* Name: Melissa Swinehart, 8001176124, As1
* Description: Encrypting and decrypting files
* Input: User inputs files, offset_value, and
encryption/decryption character
* Output: Encryption or Decryption of the 
message/files
*/

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <string>
using std::getline;
using std::string;

struct scheme_parameters {
  static const int stages = 3;
  int rotate[stages] = {22, 4, 40};
  int offset[stages] = {2, 4, 8};

};
/**
 * @brief Offsets message using ASCII values
 *
 * @param string message
 * @param int offset
 * @return string newString
 * 
 */
string offset(string message, int offset) {
 
string newString = "";
//For loop iterating over each character in
//message
for (int i = 0; i < message.length(); i++){
char letter = message[i];
//Convert character to asciivalue
int asciiValue = static_cast<int>(letter);
//Offset the ascii value
int result = (asciiValue + offset) % 128;
//Turn value back to character
char result_ = static_cast<char>(result);
//Append character to string
newString += result_;
}

return newString;
}

/**
 * @brief Demonstrates the efficacy of the offset function
 */
void offset_encryption() {
  int s = 5;
  string message = "The orange cat, sleeping quietly, awoke.";
//Ciphers and deciphers message
cout << "Text : " << message << "\n" << endl;
cout << "Cipher: " << offset(message,s) << "\n" << endl;
message = offset(message,s);
cout << "DeCipher: " << offset(message,-s) << endl;
cout << endl;

}

/**
 * @brief Checks if file can be opened
 *
 * @param  string file_name
 * @return ifstream
 */
ifstream _open_input_file(string file_name) {
  ifstream input;
  input.open(file_name);

  if(!input){
    cout << endl;
    cout << "ERROR: Could not open file : " << file_name << endl;
    exit(-1);
  }
  return input;
}

/**
 * @brief 
 *
 * @param argc main function formal parameter
 * @param argv main function formal parameter
 * @return ifstream
 */
ifstream open_argv_file(int argc, const char** argv) {
  //If there aren't 2 argunments, show error and exit
if(argc != 2){
    cout << endl;
    cout << "ERROR: Incorrect usage!" << endl;
    cout << "./a.out <filename>" << endl;
    exit(-1);
}
    string file_name = argv[1];
   return _open_input_file(file_name);

}

/**
 * @brief Opens input file
 * 
 * @return ifstream
 */
ifstream open_input_file() {
  string input_file;
  cout << "\nPlease enter the name of your input file: ";
  cin >> input_file;

  return _open_input_file(input_file);
  
  
}

/**
 * @brief Checks if output file opened
 *
 * @param string file_name
 * @return ifstream
 */
ofstream _open_output_file(string file_name) {
  ofstream output;
  output.open(file_name);

  if(!output){
    exit(-1);
  }
  return output;
}

/**
 * @brief  Opens output file
 * 
 * @return ofstream
 */
ofstream open_output_file() {
    string output_file;
  cout << "Please enter the name of your output file: ";
  cin >> output_file;

  return _open_output_file(output_file);
}

/**
 * @brief Demonstrate the efficacy of the following functions
 *  open_input_file
 *  open_output_file
 *  offset
 *
 * @param output ofstream output file id
 * @param input ifstream input file id
 */
void sequential_file_encryption(ofstream output, ifstream input) {
  int offset_value;
  string input_stream; //Stores line from file

  cout << "\nWhat is your shift key? ";
  cin >> offset_value;
  //Parse each line
while (getline(input, input_stream)){
//Offset the line
input_stream = offset(input_stream, offset_value);
//Output the result
output << input_stream << endl;

  }
  input.close();
  output.close();

 

  
}

/**
 * @brief Rotate message left or right
 *
 * @param string str
 * @param string r
 * @return string
 *
 */
string rotate(string str, int r){
//Convert str.length to avoid incorrect rotation
  int len = str.length();
//Keeps rotations from going greater than length
  r = r % len;
  //Copy String
  string str2 = "";

//Rotating right
if(r > 0){
  //Rotate from index and populate string
  for(int i = r + 1; i < len; i++){
      str2 += str[i];
    }
  //Append string from beginning to rotated
  for(int j = 0; j <= r; j++){
      str2 += str[j];
    }
//Rotating left
  }else if(r < 0){
    //Turn -r to positive
    r = -r;
    //Rotate from index of the string and populate string
    for(int i = r; i < len; i++){
      str2 += str[i];
    }
    //Append from the beginning of the string
    //up to the rotated part
    for(int j = 0; j < r; j++){
      str2 += str[j];
    }
  }

  return str2;
}

/**
 * @brief Uses struct's data to offset and rotate
 * pt2key.txt
 * 
 * @return string
 */
string rotation_encryption(string message) {
  scheme_parameters es;
  char scheme;

  cout << "\nAre you encrypting(E) or decrypting(D)?";
  cin >> scheme;
  cout << "\n";
  if (scheme == 'E' || scheme == 'e'){

    //Iterate over members of the struct
    //Encrypt or decrypt message using the
    //struct's array filled with pre-numbers

//For loop used to iterate of struct's array and 
// rotate or offset
    for(int i = 0; i < es.stages; i++){

      message = rotate(message, es.rotate[i]);

      message = offset(message, es.offset[i]);
    }
  }else if (scheme == 'D' || scheme == 'd'){
//For loop used to iterate of struct's array and 
// rotate or offset opposite way
    for(int i = 0; i < es.stages; i++){

      message = offset(message, -es.offset[i]);

      message = rotate(message, -es.rotate[i]);
    }
  }else{
    cerr << "ERROR: Encryption scheme unrecognized!" << endl;
  }

  return message;
}


/**
 * @brief Function to retrieve the password for pt2Key
 */
void rotation_file_encryption() {
  string message;
  ifstream input = open_input_file();
  ofstream output("message.txt");
  getline(input, message);
  output << rotation_encryption(message);

}
int main(int argc, char const** argv) {

  offset_encryption();

  sequential_file_encryption(open_output_file(), 
  open_argv_file(argc, argv));

  rotation_file_encryption();

  return 0;
}
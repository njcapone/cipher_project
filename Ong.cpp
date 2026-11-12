//Title: Ong.cpp
//Author: Niccolo Capones
//Date: 4/9/2025
//Description: This file implements the methods in Ong.h

#include "Cipher.h"
#include "Ong.h"
#include <string>
#include <vector>

// default constructor
Ong::Ong():Cipher(){}

// populated constructor, using the inherited cipher constructor
Ong::Ong(string message, bool isEncrypted):
  Cipher(message, isEncrypted){}

Ong::~Ong(){
  SetMessage("");
}

// helper functions to find vowels and punctuations
bool Ong::IsVowel(char letter){
  // i would do an if structure... but I'm feeling petty >:)
  return letter == 'A' or letter == 'E' or letter == 'I' or letter == 'O' or letter == 'U' or letter == 'a' or letter == 'e' or letter == 'i' or letter == 'o' or letter == 'u';
}

// recall that the ascii table has values for this one!
bool Ong::IsPunct(char c){
  // utilize an if structure

  // set variables for the start of the symbols and numbers
  int space = 32;
  int atMark = 64;

  // second set of symbols
  int lBracket = 91;
  int apostrophe = 96;

  // third set of symbols
  int lCurly = 123;
  int tilde = 126;

  // use the if structure!
  if (c >= space and c <= atMark){
    return true;
  } else if (c >= lBracket and c <= apostrophe){
    return true;
  } else if (c >= lCurly and c <= tilde){
    return true;
  } else {
    return false;
  }
}

// encryption for Ong
void Ong::Encrypt(){
  /*
    Idea:
    create a vector using each individual character of the Cipher
    use the helper functions to determine whether to keep spaces
    include the ong and dash for the consonants
    
   */
  // get the messages and set up the vector
  string message = GetMessage();
  string encrypt = "";

  // make a new string, and encrypt it in this process
  // note: vector methods apply to the string

  
  for(int i = 0; i < int(message.length()); i++){
    if (IsVowel(message[i]) == true){
      if(i == int(message.length())-1 or IsPunct(message[i+1]) == true){
	encrypt.push_back(message[i]);
      }else{
	encrypt.push_back(message[i]);
	encrypt.push_back('-');
      }
    } else if (IsPunct(message[i]) == false and IsVowel(message[i]) == false){
      if(IsPunct(message[i+1]) == true or i == int(message.length())-1){
	encrypt.push_back(message[i]);
	encrypt.push_back('o');
	encrypt.push_back('n');
	encrypt.push_back('g');
      }else{
	encrypt.push_back(message[i]);
	encrypt.push_back('o');
	encrypt.push_back('n');
	encrypt.push_back('g');
	encrypt.push_back('-');
      }
    } else {
      encrypt.push_back(message[i]);
    }
  }
  // display the encrypted string

  // set the message to the encrypted string
  SetMessage(encrypt);
  ToggleEncrypted();

  return;
}

void Ong::Decrypt(){
  /*
    Idea: Take everything that comes before a '-' and push_back to a decrypt string
    No matter what, push_back the first character
  */

  string message = GetMessage();
  string decrypt = "";

  for (int i = 0; i < int(message.length()); i++){
    if(i == 0){
      decrypt.push_back(message[i]);
    } else {
      if(IsPunct(message[i-1])){ // if the character beforehand is a space or otherwise, append the next char
	decrypt.push_back(message[i]);
      } else if (IsPunct(message[i]) and message[i] != '-'){ // we don't append dashes
	decrypt.push_back(message[i]);
      }
    }
  }
  ToggleEncrypted();
  SetMessage(decrypt);
  return;
  
}

// return the cipher type
string Ong::ToString(){return "Ong";}

string Ong::FormatOutput(){
  stringstream ss;
  ss << 'o' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage() << DELIMITER << '\n';
  return ss.str();
}

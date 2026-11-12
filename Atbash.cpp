// Title: Atbash.cpp
// Author: Niccolo James Capones
// Date: 4/7/2025
// Description: This file implements the methods in the child class Atbash
#include "Atbash.h"
#include "Cipher.h"
#include <string>

using namespace std;
// implement inherited default constructor remember, Atbash is a cipher
Atbash::Atbash():Cipher(){}

// implement inherited populated constructor
Atbash::Atbash(string message, bool isEncrypted)
  :Cipher(message, isEncrypted){}

// implement inherited destructor
Atbash::~Atbash(){
  SetMessage("");
}

// implement virtual function to Decrypt from Cipher
// for Atbash you swap the letters
// try to think about it as calculating the distance from the last letter z
void Atbash::Encrypt(){
  // plan: use the distance away from Z as a way to implement atbash
  // e.g) a = 97, 122 - 97 = 25, thus in an array of all chars a will now be z
  // use GetMessage  to mutate the string

  string message = GetMessage();
  string newMessage;
  int zAscii = 122; // lowercase max 
  int ZAscii = 90;

  char alphabetLower[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  
  char alphabetUpper[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  // iterate through the string

  for(int i = 0; i < int(message.length()); i++){
    // don't change spaces or special characters!
    if ((ZAscii - message[i]) >= 0 and (ZAscii - message[i]) <= 25){
      char newChar = alphabetUpper[ZAscii - message[i]]; // upper
      newMessage.push_back(newChar);
    } else if ((zAscii - message[i]) >= 0 and  (zAscii - message[i] <= 25)){
      char newChar = alphabetLower[zAscii - message[i]]; // lower
      newMessage.push_back(newChar);
    } else {
      newMessage.push_back(message[i]); // don't change characters that are not in the alphabet!
    }
  }
  SetMessage(newMessage);
  ToggleEncrypted();
  return;
}

// for decryption, the process is basically the same for 

void Atbash::Decrypt(){
  int zAscii = 122; // lowercase max 
  int ZAscii = 90; // uppercase max

  char alphabetLower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  
  char alphabetUpper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  // iterate through the string
  string message = GetMessage();
  string newMessage = "";
  for(int i = 0; i < int(message.length()); i++){
    // don't change spaces or special characters!
    if (ZAscii - message[i] >= 0 and ZAscii - message[i] <= 25){
      char newChar = alphabetUpper[ZAscii - message[i]]; // upper
      if(newChar == 'Z'){ // handling the only exception due to symmetry
	newChar = 'A';
      }
      newMessage.push_back(newChar);
    }else if (zAscii - message[i] >= 0 and  zAscii - message[i] <= 25){
      char newChar = alphabetLower[zAscii - message[i]]; // lower
      newMessage.push_back(newChar);
    }else {
      newMessage.push_back(message[i]); // don't change characters that are not in the alphabet!
    }
  }
  SetMessage(newMessage);
  ToggleEncrypted();
  return;
}

string Atbash::ToString(){return "Atbash";}

string Atbash::FormatOutput(){
  stringstream ss;
  ss << 'a' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage() << DELIMITER << '\n';
  return ss.str();
}

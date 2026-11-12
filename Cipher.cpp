// Title: Cipher.cpp
// Author: Niccolo James Capones
// Date 4/7/2028
// Description: This file implements the methods in Cipher.h

#include <iostream>
#include <string>
#include <sstream>
#include "Cipher.h"
using namespace std;

// default constructor
Cipher::Cipher(){
  m_message = "";
  m_isEncrypted = true;
}

// the overloaded constructor
Cipher::Cipher(string message, bool isEncrypted){
  m_message = message;
  m_isEncrypted = isEncrypted;
}

// deconstructor to kill Cipher
Cipher::~Cipher(){
  m_message = "";
  m_isEncrypted = true;
}

// Cipher decryption that applies to the child classes
void Cipher::Decrypt() {
  if (m_isEncrypted == false) {
    cout << "This message has already been deciphered" << endl;
    return;
  } else {
    return;
  }
}

void Cipher::Encrypt() {
  if (m_isEncrypted == true){
    cout << "Message already encrypted" << endl;
    return;
  } else {
    return; 
  }
}

// getter for Cipher's message
string Cipher::GetMessage(){ return m_message; }

// Getter for whether or not the cipher is encripted
bool Cipher::GetIsEncrypted(){ return m_isEncrypted; }

// setter for Cipher's Message
void Cipher::SetMessage(string newMessage){ m_message = newMessage; }

// switches the values for isEncrypted
void Cipher::ToggleEncrypted(){
  if (m_isEncrypted) {
    m_isEncrypted = false;
  }else{
    m_isEncrypted = true;
  }
}

// virtual function that returns the string of the object type
// define the virtual function based on class!
string Cipher::ToString(){
  stringstream ss;
  ss << 't' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage() << DELIMITER << '\n';
  return ss.str();
}
// overloading the << operator so we can cout cipher objects easily
ostream& operator<<( ostream &output, Cipher &C){
  return output << C.GetMessage() << endl;
}

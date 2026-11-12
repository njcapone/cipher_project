// Title: Scytale.cpp
// Author: Niccolo James Capones
// Date: 4/13/2025
// Description: This implements the methods in Cipher.h

#include "Cipher.h"
#include "Scytale.h"
#include <vector>
#include <string>
#include <istream>
using namespace std;

// default constructor
Scytale::Scytale():Cipher(){
  m_key = 0;
}

// populated constructor
Scytale::Scytale(string message, bool isEncrypted, int key)
  :Cipher(message, isEncrypted){
  m_key = key;
}

// destructor
Scytale::~Scytale(){
  m_key = 0;
}

void Scytale::Encrypt(){
  string message = GetMessage();
  cout << message << endl;

  /*
    Recall the process
    Divide the string by the keys
    The columns represent how the string will be divided
    the message length/key
   */
  int key = m_key;
  int index = 0;
  // this takes into factor that the length my not be fully divisible by the key
  int length = int(message.length());
  int rows = (length + (length % key) + 1) / key;
  cout << rows << endl;
  string encrypted = "";
  // make an empty array filled with spaces
  vector<vector<char>> matrix(key, vector<char>(rows, '@'));
  
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < key; j++){
      if(index < length){
	matrix[j][i] = message[index++];
      }
    }
  }

  for(int i = 0; i < key; i++){
    for(int j = 0; j < rows; j++){
      encrypted+=matrix[i][j];
    }
  }
  SetMessage(encrypted);
  ToggleEncrypted();
  return;
}

// do the encryption process but backwards!
void Scytale::Decrypt(){
  string message = GetMessage();
  int key = m_key;
  int length = int(message.length());
  int rows = (length + (length % key) + 1) / key;
  string decrypted = "";
  vector<vector<char>> matrix(rows, vector<char>(key, '@'));

  int index = 0;
  for(int i = 0; i < key; i++){
    for(int j = 0; j < rows; j++){
      if(index < length){
      matrix[j][i] = message[index++];
      }
    }
  }
  // instead of going row by row, go column by column!
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < key; j++){
      if(matrix[i][j] != '@'){
      decrypted+=matrix[i][j];
      }
    }
  }
  SetMessage(decrypted);
  ToggleEncrypted();
  return;
}

string Scytale::ToString(){return "Scytale";}

string Scytale::FormatOutput(){
  stringstream ss;
  ss << 's' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage() << DELIMITER << m_key << '\n';
  return ss.str();
}


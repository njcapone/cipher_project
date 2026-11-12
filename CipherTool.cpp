// Title: CipherTool.cpp
// Author: Niccolo James Capones
// Date: 4/13/2025
// Description: This file implements the methods in CipherTool.h
#include "Cipher.h"
#include "Atbash.h"
#include "Scytale.h"
#include "Ong.h"
#include "CipherTool.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// constructor
CipherTool::CipherTool(string fileName){m_filename = fileName;}

// destructor
CipherTool::~CipherTool(){
  if(m_ciphers.size() > 0){
    for(int i = 0; i < int(m_ciphers.size()); i++){
      delete m_ciphers[i];
      m_ciphers[i] = nullptr;
    }
  }
}
// file load process, 3 types of ciphers
void CipherTool::LoadFile(){
  ifstream cipherFile;
  cipherFile.open(m_filename);

  // if structure process
  string line;
  if(cipherFile.is_open()){
     while(getline(cipherFile, line)){
       if(line[0] == 'a'){
       // guaranteed index = 2 is the encryption signifier
         string boolChar(1, line[2]);
         bool isEncrypted = StringToBoolean(boolChar);
         string message = "";
         int index = 4;

         //guaranteed, index = 4 marks the start of the message
       
         while(index < int(line.length()) and line[index] != DELIMITER){
	   message.push_back(line[index]);
	   index++;
         }
         m_ciphers.push_back(new Atbash(message, isEncrypted));
      // for Ong cipher
       }else if(line[0] == 'o') {
	 string boolChar(1, line[2]);
	 bool isEncrypted = StringToBoolean(boolChar);
	 string message = "";
	 int index = 4;
	 //guaranteed, index = 4 marks the start of the message
	 while(index < int(line.length()) and line[index] != DELIMITER){
	   message.push_back(line[index]);
	   index++;
         }
	 m_ciphers.push_back(new Ong(message, isEncrypted));
       }else if(line[0] == 's') {
	 string boolChar(1, line[2]);
         bool isEncrypted = StringToBoolean(boolChar);
	 // In the event you have scytale function
	 char preKey = line[int(line.length()) - 1];
	 int key = preKey - '0';
	 cout << key << '\n';
         string message = "";
         int index = 4; //guaranteed, index = 4 marks the start of the message
         while(index < int(line.length()) and line[index] != DELIMITER){
	   message += (line[index]);
	   index++;
         }
         m_ciphers.push_back(new Scytale(message, isEncrypted, int(key)));
       }
     }
  }
     cipherFile.close();
     return;
}

// turn the 0 or 1 into an actual boolean
bool CipherTool::StringToBoolean(string input){
  if(input == "0"){
    return false;
  }else{
    return true;
  }
}

// display all the ciphers
void CipherTool::DisplayCiphers(){
  for(int i = 0; i < int(m_ciphers.size()); i++){
    cout << *m_ciphers[i] << '(' << m_ciphers[i] -> ToString() << ')' << endl;
    }
  return;
}

// Encrypt all or Decrypt all!
void CipherTool::EncryptDecrypt(bool isEncrypted){
  int affected = 0; // how many ciphers did you do?
  if(isEncrypted == true) { // if the target is encrypted ciphers
    for(int i = 0; i < int(m_ciphers.size()); i++){
      if(m_ciphers[i] -> GetIsEncrypted() == true){
	m_ciphers[i] -> Decrypt();
	affected++;
      }
    }
    cout << affected << " Ciphers Decrypted\n";
  } else if(isEncrypted == false){
    for(int i = 0; i < int(m_ciphers.size()); i++){
      if(m_ciphers[i] -> GetIsEncrypted() == false){
	m_ciphers[i] -> Encrypt();
	affected++;
      }
    }
    cout << affected << " Ciphers Encrypted\n";
  }
    return;
  }
  

/*
  Creates a new file that holds the ciphers, remember to use the string stream formatter and set those up in each file!!!
 */
void CipherTool::Export(){
  string fileName;
  cout << "What would you like to call this new file?: " << endl;
  getline(cin, fileName); // this is a decoy line
  getline(cin, fileName); // this is our actual line 

  ofstream exportFile (fileName);

  if(exportFile.is_open()){
    for(int i = 0; i < int(m_ciphers.size()); i++){
      exportFile << m_ciphers[i] -> FormatOutput() << endl;
    }
  }
  exportFile.close();
}

// display the menu and return the choice
int CipherTool::Menu(){

  cout << "What would you like to do?\n1. Display All Ciphers\n2. Encrypt All Ciphers\n3. Decrypt All Ciphers\n4. Export All Ciphers\n5. Quit\n";

  int choice;

  cin >> choice;

  return choice;
}
// the switch statement cycle!!!
void CipherTool::Start(){
  LoadFile();
    int choice = Menu();
    while(choice != 5){
      switch(choice){
      case 1:
        DisplayCiphers();
        break;
      case 2:
        EncryptDecrypt(false);
        cout << "All ciphers encrypted" << endl;
        break;
      case 3:
        EncryptDecrypt(true);
        cout << "All ciphers decrypted" << endl;
        break;
      case 4:
        Export();
      case 5:
        break;
      }
      choice = Menu();
    }
    return;
}

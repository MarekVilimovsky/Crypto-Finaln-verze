#pragma once
#include <Windows.h>
#include <stdio.h>
#include "clsProtoEncryption.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class clsEncryptionEx : public clsProtoEncryption
{
public:
	clsEncryptionEx();//prazdny konstruktor; //konstruktor
	//virutal, bude se funkce dedit a prepisovat
	virtual bool OpenFile(LPCWSTR p_chNameIN);//je abstraktni 
	virtual bool CloseFile(); //zavre vsechny otevrene slozky
	virtual bool Crypt(); //kryptovani slozek
	virtual bool Decrypt(); //kryptovani slozek

private:
	HANDLE hFile, hFileMapping;
	//handle je manipulacni cislo
	//predame jadru cislo handlu ten si najde misto v pameti 
	//kazdy proces ma sve vlsatni handles

	PBYTE p_mSourceFirstByte;//pointer na byte
	LARGE_INTEGER lpFileSize; // k ukladani velkych cisel
	int Caesarovasifra = 3;
};


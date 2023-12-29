#include "clsEncryption.h"
#include "clsEncryptionEx.h"
#include "clsProtoEncryption.h"
//include nasi heder file

//funkce pro kopirovani slozek, proc neni v tride?
void CopyCryptFile() 
{

}

int main()
{
	//pointer na objekt ze tridy
	clsEncryptionEx* p_lobjEncryptionEx;

	//alokuje pamet pro objekt tridy
	p_lobjEncryptionEx = new clsEncryptionEx();

	//dve aplikace si sdileji data pomoci sdilene pameti, ktera se po zavreni smaze
	//je to velmi rychle

	//otevreni slozky
	p_lobjEncryptionEx->OpenFile(L"C:\\temp\\test.txt");		

	//zasifrovat
	p_lobjEncryptionEx->Crypt();

	//odsifrovani
	p_lobjEncryptionEx->Decrypt();
	
	//zavreni slozky
	p_lobjEncryptionEx->CloseFile();

	//uvolneni pameti
	delete(p_lobjEncryptionEx);

}


#include "clsEncryption.h"
#include <cctype>

//Constructor 
clsEncryption::clsEncryption()
{
	//kdyz spoustime konstruktor tak fileIN and OUT musi byt null
	p_mFileIN = NULL;
	p_mFileOUT = NULL;
}

// Opens file and checks if it really oppened by True/False statement
// name="p_chName" Path and name of a specified file 

bool clsEncryption::OpenFile(const char* p_chNameIN, const char* p_chNameOUT)
{
	int lintLen;

	//File name copy

	lintLen = strnlen_s(p_chNameIN, MAX_LENGTH_FILENAME);
	p_mchFileNameIN = new char[lintLen + 1];	//ending char
	strcpy_s(p_mchFileNameIN, lintLen + 1, p_chNameIN);

	//File openning
	fopen_s(&p_mFileIN, p_mchFileNameIN, "r");

	//File name copy

	lintLen = strnlen_s(p_chNameOUT, MAX_LENGTH_FILENAME);
	p_mchFileNameOUT = new char[lintLen + 1];	//ending char
	strcpy_s(p_mchFileNameOUT, lintLen + 1, p_chNameOUT);

	//File openning
	fopen_s(&p_mFileOUT, p_mchFileNameOUT, "w");

	//test jestli jsou soubory otevrene
	if ((p_mFileIN == NULL) || (p_mFileOUT == NULL))
	{
		//zavirani souboru
		CloseFile();
		return false;
	}

	return true;
}

// Closes  file and checks if it really closed by True/False statement
bool clsEncryption::CloseFile()
{
	if (p_mFileIN != NULL)
	{
		fclose(p_mFileIN);
		p_mFileIN = NULL;
	}

	if (p_mFileOUT != NULL)
	{
		fclose(p_mFileOUT);
		p_mFileOUT = NULL;
	}

	if (p_mFileIN == NULL && p_mFileOUT == NULL)
	{

		return true;
	}


	return false;
}

bool clsEncryption::Crypt()
{
	unsigned char lchBuffer;
	int lintCount;
	int number_In_Alphabet;

	//if p_mFile is not opened (is NULL) then cant do anything
	if (p_mFileIN == NULL || p_mFileOUT == NULL)
	{
		return false;
	}

	do
	{
		//cteni jednoho bytu
		lintCount = fread_s(&lchBuffer, 1, 1, 1, p_mFileIN);

		//jsem na konci souboru to znamena ze nemuzu nikam psat musim prerusit
		if (lintCount == 0) break;

		//sifrovani
		if (lchBuffer + KEY > 255)
		{
			lchBuffer += KEY - 255;
		}
		else
		{
			lchBuffer += KEY;
		}

		//zapis jednoho byte do souboru
		fwrite(&lchBuffer, 1, 1, p_mFileOUT);

	} while (lintCount != 0); //end of file

	return false;
}

bool clsEncryption::Decrypt()
{
	unsigned char lchBuffer;
	int lintCount;

	//if p_mFile is not opened (is NULL) then cant do anything
	if (p_mFileIN == NULL || p_mFileOUT == NULL)
	{

		return false;
	}

	do
	{
		//cteni jednoho bytu
		lintCount = fread_s(&lchBuffer, 1, 1, 1, p_mFileIN);

		//jsem na konci souboru to znamena ze nemuzu nikam psat musim prerusit
		if (lintCount == 0) break;

		//desifrovani
		if (lchBuffer - KEY < 0)
		{
			lchBuffer = 255 + (lchBuffer - KEY);
		}
		else
		{
			lchBuffer -= KEY;
		}


		//zapis jednoho byte do souboru
		fwrite(&lchBuffer, 1, 1, p_mFileOUT);

	} while (lintCount != 0); //end of file

	return false;
}
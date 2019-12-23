
#include "provided.h"
#include <string>
#include <map>
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
	~TranslatorImpl();
	bool pushMapping(string ciphertext, string plaintext);
	bool popMapping();
	string getTranslation(const string& ciphertext) const;
private:
	bool hasMapping(char c) {
		for (int i = 0; i < 26; i++) {
			if (currentMap[i] == c) {
				return true;
			}
		}
		return false;
	}
	vector<map<char, char>> Mappings;
	map<char, char> currentMap;

};

TranslatorImpl::TranslatorImpl() {
	for (int i = 0; i < 26; i++) { //26 is the number of alphabet letters
		char alphabetletter = 97 + i;
		currentMap[alphabetletter] = '?';
	}
}

TranslatorImpl::~TranslatorImpl() {

}


bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.size() != plaintext.size()) { //both texts must be the same size
		return false;
	}

	//&& newCurrentMap[cipherletter] != plainletter
	map<char, char> newCurrentMap = currentMap;
	for (int i = 0; i < ciphertext.size(); i++) {
		char cipherletter = tolower(ciphertext[i]);
		char plainletter = tolower(plaintext[i]);
		if (hasMapping(plainletter)) {
			return false;
		}
		if (newCurrentMap[cipherletter] != '?' && newCurrentMap[cipherletter] != plainletter) {
			return false;
		}
		newCurrentMap[cipherletter] = plainletter;

	}
	Mappings.push_back(currentMap); //push the old "currentMap" onto the stack after we have all possible chances to return false, because if we return false we shouldnt change our stack or current map
	currentMap = newCurrentMap; //make the current Map =newCurrentMap for the same reason as above
	return true;
	/*
	for (int i = 0; i < 26; i++) { //26 is the number of alphabet letters
	char alphabetletter = 141 + i;
	StorageMap[alphabetletter] = '?';
	}
	map<char,char>tempCurrentMap = currentMap; //create a temp copy of the current map so thats if the for loop every returns false, the real currentMap will not change
	for (int i = 0; i < ciphertext.size(); i++) {
	char cipherletter = tolower(ciphertext[i]);
	char plainletter = tolower(plaintext[i]);
	if (currentMap.at(cipherletter) != '?') {
	return false;
	}
	StorageMap[cipherletter] = plainletter;
	tempCurrentMap[cipherletter] = plainletter;
	}
	Mappings.push_back(StorageMap); //push a map of the chars we changed in the current map into the vector
	currentMap = tempCurrentMap; //after we have gone through the loop and never returned false, we can safely change the current map
	return true;
	*/
}

bool TranslatorImpl::popMapping()
{
	if (Mappings.size() <= 0) {
		return false;
	}
	currentMap = Mappings.back();
	Mappings.pop_back();
	return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string modCipherText = ciphertext;
	string translation = "";
	for (int i = 0; i < modCipherText.size(); i++) {
		modCipherText[i] = tolower(modCipherText[i]); //make sure the cipher text is lower cased
		if (isalpha(modCipherText[i])) {

			char translatedLetter = currentMap.at(modCipherText[i]);
			if (isupper(ciphertext[i])) {
				translation += toupper(translatedLetter);
			}
			else {
				translation += translatedLetter;
			}
		}
		else {
			translation += modCipherText[i];
		}
	}
	return translation; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
	m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
	delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
	return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
	return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
	return m_impl->getTranslation(ciphertext);
}


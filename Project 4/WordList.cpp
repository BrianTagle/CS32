
#include "provided.h"
#include "MyHash.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;



class WordListImpl
{
public:
	bool loadWordList(string filename);
	bool contains(string word) const;
	vector<string> findCandidates(string cipherWord, string currTranslation) const;

private:
	string getPattern(string word) const;
	MyHash<string, string> m_table;
	MyHash<string, vector<string>> m_patternTable;

};

bool WordListImpl::loadWordList(string filename)
{
	if (m_table.getNumItems() > 0) {
		m_table.reset();
	}
	if (m_patternTable.getNumItems() > 0) {
		m_table.reset();
	}
	ifstream wordfile(filename);
	if (!wordfile)
	{
		cerr << "Cannot open " << filename << "!" << endl;
		return false; //failed to open the file so return false;
	}

	string s;
	while (getline(wordfile, s))
	{
		bool add = true;

		for (int i = 0; i < s.size(); i++) {
			if (!isalpha(s[i]) && s[i] != 39) { //int 39 = char ' 
				bool add = false; //there is a 
				break;
			}
			s[i] = tolower(s[i]);
		}
		if (add) {
			string p = getPattern(s);
			m_table.associate(s, s);
			//cerr << s << endl;

			if (m_patternTable.find(p) == nullptr) {
				vector<string> temp;
				temp.push_back(s);
				m_patternTable.associate(p, temp);
			}
			else {
				vector<string>* temp = m_patternTable.find(p);
				temp->push_back(s);
			}
		}

	}
	return true;
}

bool WordListImpl::contains(string word) const
{

	for (int i = 0; i < word.length(); i++) { //makes the entire word lower case
		word[i] = tolower(word[i]);
	}
	//string pattern = getPattern(word);
	if (m_table.find(word) == nullptr) {
		return false; //TODO currently case sensitive, not sure how to fix
	}
	else {
		return true;
	}

}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	if (cipherWord.size() != currTranslation.size()) { //cipher word and curr Translation must be strings of equal size;
		return vector<string>(); //return empty vector
	}
	MyHash<char, char> knownTranslationLetters;
	string pattern = getPattern(cipherWord);
	vector<string> allWords = *(m_patternTable.find(pattern));
	vector<string> currTranslationWords;
	bool add = true;
	for (int i = 0; i < currTranslation.size(); i++) {
		currTranslation[i] = tolower(currTranslation[i]);
		cipherWord[i] = tolower(cipherWord[i]);
		if (cipherWord[i] == 39 && currTranslation[i] != 39) { //when the cipherword is a apostrophe but the currtranslation is not an apostrophe
			return vector<string>();
		}
		if (isalpha(cipherWord[i]) && (!isalpha(currTranslation[i]) && currTranslation[i] != '?')) {//when the cipheword is a letter but the currTranslation is not a question mark or a letter
			return vector<string>();
		}
		if (knownTranslationLetters.find(cipherWord[i]) == nullptr) { //creates a map of the letter we know as we go along
			knownTranslationLetters.associate(cipherWord[i], currTranslation[i]);
		}
		if (*knownTranslationLetters.find(cipherWord[i]) != currTranslation[i]) {//if the map of letter we know doesn't add up in the cipherword,we return an empty vector 
			return vector<string>();
		}
	}
	for (int i = 0; i < allWords.size(); i++) {
		add = true;
		string currentWord = allWords[i];
		for (int i = 0; i < currTranslation.size(); i++) {


			if (isalpha(currTranslation[i]) && currTranslation[i] != currentWord[i]) {//if the current translation[i] is not a question mark and the letter it is != the letter the currentWord is
				add = false; //make sure not to add this word to the currTranslationWords and break the current loop because this is not a correct word base off of the current translation
				break;
			}

		}
		if (add) {
			currTranslationWords.push_back(currentWord);
		}
	}
	return currTranslationWords;
}

string WordListImpl::getPattern(string word) const {

	MyHash<char, char> patternTable;
	char numletter = 97;
	string pattern = "";
	for (int i = 0; i < word.size(); i++) {
		word[i] = tolower(word[i]); //TODO, maybe delete this line, since only I call it I can gurantee that the word will already be lower case?
		if (!isalpha(word[i])) {
			continue;
		}
		if (patternTable.find(word[i]) == nullptr) {
			patternTable.associate(word[i], numletter);
			pattern += char(numletter);
			numletter++;
		}
		else {
			pattern += *(patternTable.find(word[i]));
		}
	}
	return pattern;
}

//***** hash functions for string, int, and char *****

unsigned int hasher(const std::string& s)
{
	return std::hash<std::string>()(s);
}

unsigned int hasher(const int& i)
{
	return std::hash<int>()(i);
}

unsigned int hasher(const char& c)
{
	return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
	m_impl = new WordListImpl;
}

WordList::~WordList()
{
	delete m_impl;
}

bool WordList::loadWordList(string filename)
{
	return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
	return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
	return m_impl->findCandidates(cipherWord, currTranslation);
}

#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
	~TokenizerImpl();
    vector<string> tokenize(const std::string& s) const;
private:
	char* separator;
	int numSeparators;
	bool isSeparator(char C) const;
};

TokenizerImpl::TokenizerImpl(string separators)
{
	numSeparators = separators.size();
	separator = new char[numSeparators];
	for (int i = 0; i < numSeparators; i++) {
		separator[i] = separators[i];
		
	}


}
TokenizerImpl::~TokenizerImpl() {
	delete[]separator;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	vector<string> tokens;
	for (int i = 0; i < s.size();i++) {//go through the entire string
		string word = "";
		while(i< s.size() && !isSeparator(s[i])){
			word += s[i];
			i++; //increment i up because we move past a letter
		}
		if (word != "") {
			tokens.push_back(word);
		}
			
	}
    return tokens;  // This compiles, but may not be correct
}

bool TokenizerImpl::isSeparator(char C) const{
	for (int i = 0; i < numSeparators; i++) {
		if (C == separator[i]) {
			return true;
		}
	}
	return false;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}

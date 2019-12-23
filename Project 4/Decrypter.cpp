
#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
	DecrypterImpl();
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	WordList m_WL;
	Translator m_translator;
	Tokenizer m_tokens;

	int numQuestionMarks(string token)
	{
		int num = 0;
		string trans = m_translator.getTranslation(token);
		for (int i = 0; i < trans.size(); i++)
		{
			if (trans[i] == '?') {
				num++;

			}
		}
		return num;

	}

	int mostQuestionMarks(const vector<string>& tokens)
	{
		int indexOfMax = -1; //invalid index to start
		int max = 0;
		 
		for (int i = 0; i < tokens.size(); i++)
		{
			if (numQuestionMarks(tokens[i]) >= max) {
				indexOfMax = i;
				max = numQuestionMarks(tokens[i]);
			}
		}
		return indexOfMax;
	}

	bool isCompleteTranslation(string s)
	{
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '?') {
				return false;
			}
		}
		return true;
	}

	string removeApostrophe(string s) //if we try to push a map when there is an apostrophe in the word, there will be problemsn
	{
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '\''){
				s.erase(i, 1);
			}
		}
		return s; //string with Apostrophe removed
	}

};

DecrypterImpl::DecrypterImpl()
	:m_tokens(",;:.!()[]{}-\"#$%^& 0123456789") {
}

bool DecrypterImpl::load(string filename)
{
	return m_WL.loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> translatedAnswers;

	vector<string> cipherTokens;
	cipherTokens = m_tokens.tokenize(ciphertext);
	int index = mostQuestionMarks(cipherTokens);
	string translatedToken = m_translator.getTranslation(cipherTokens[index]);

	vector<string> solutions = m_WL.findCandidates(cipherTokens[index], translatedToken);


	if (solutions.empty()) {//no possible words that can match current pattern
		m_translator.popMapping();
		return vector<string>();
	}

	else {
		for (int i = 0; i < solutions.size(); i++)
		{

			bool realWordCheck = true;
			bool viableAnswerCheck = true;

			if (!m_translator.pushMapping(removeApostrophe(cipherTokens[index]), removeApostrophe(solutions[i]))) {
				continue;
			}

			string nextTranslation = m_translator.getTranslation(ciphertext);
			vector<string> nextCipher = m_tokens.tokenize(nextTranslation);

			for (int j = 0; j < nextCipher.size(); j++)
				if (isCompleteTranslation(nextCipher[j]) && (!m_WL.contains(nextCipher[j]))) {
					realWordCheck = false;
					break;
				}

			if (realWordCheck == false) {
				m_translator.popMapping();
				continue;
			}

			for (int j = 0; j < nextCipher.size(); j++)
				if (!isCompleteTranslation(nextCipher[j])) {
					viableAnswerCheck = false;
					break;
				}


			if (viableAnswerCheck == false) {

				vector<string> tmp = crack(ciphertext);
				translatedAnswers.insert(translatedAnswers.end(), tmp.begin(), tmp.end());
			}
			else {
				translatedAnswers.push_back(nextTranslation);
 
				m_translator.popMapping();
			}
		}
	}

	m_translator.popMapping();
	sort(translatedAnswers.begin(), translatedAnswers.end()); //answers must be sorted
	// sort
	return translatedAnswers;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
	m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
	delete m_impl;
}

bool Decrypter::load(string filename)
{
	return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
	return m_impl->crack(ciphertext);
}

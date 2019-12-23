#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;
bool hasValidSyntax(string infix);
bool isBinaryOperator(char character);
bool parseParentheses(stack<char> paren);
bool lettersInMap(string infix, const Map& values);
void infixToPostfix(string infix, string& postfix);
int findPrecedence(char sign);
bool evaluatePostfix(string postfix, const Map& values, int& finalResult);
int evaluate(string infix, const Map& values, string& postfix, int& result) {
	if (infix == "") { //empty infix catch
		return 1;
	}
	if (!hasValidSyntax(infix)) {
		return 1;
	}
	else { //has valid syntax
		infixToPostfix(infix, postfix);
	}
	if (!lettersInMap(infix, values)) { //syntacically valid but letters in infix are not present in the map
		return 2;
	}
	if (!evaluatePostfix(postfix, values, result)) { //attempted division by zero when evaluating 
		return 3;
	}
	else { //everything checks out, change result
		evaluatePostfix(postfix, values, result); 
		return 0;
	}

}
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.


bool hasValidSyntax(string infix) {
	if (infix == "") {
		return true;
	}
	stack<char> parenthesesStack;
	stack<char> operatorsAndOperands;
	for (int i = 0; i < int(infix.length()); i++) {
		if (infix[i] == ' ') {
			continue;
		}
		if (infix[i] == ')' || infix[i] == '(') {
			parenthesesStack.push(infix[i]);
			continue;
		}

		if ((isalpha(infix[i]) && islower(infix[i])) || isBinaryOperator(infix[i])) { //if infix[i] is a lowercase letter or its a binary operator
			if (isalpha(infix[i])) {
				if (!operatorsAndOperands.empty() && isalpha(operatorsAndOperands.top())) { //when the stack isnt empty and the top of the stack is already a letter
					return false;
				}
				else {
					operatorsAndOperands.push(infix[i]);
				}
			}
			else if (isBinaryOperator(infix[i])) {
				if (operatorsAndOperands.empty()) { //a binary operator can never be the first char of the infix
					return false;
				}
				if (!operatorsAndOperands.empty() && isBinaryOperator(operatorsAndOperands.top())) { //when the stack isnt empty and the top of the stack is already a binary operator
					return false;
				}
				else {
					operatorsAndOperands.push(infix[i]);
				}
			}
		}
		else {
			return false; //false if infix[i] isnt a parenthese, a space, a letter, or a binary operator
		}
	}
	if (!operatorsAndOperands.empty() && isBinaryOperator(operatorsAndOperands.top())) { //the last char of the infix can never be a binary operator
		return false;
	}
	if (operatorsAndOperands.empty()){ //there must be operands in the stack
		return false;
	}
	return parseParentheses(parenthesesStack);
}
bool isBinaryOperator(char character) {
	if (character == '+' || character == '-' || character == '*' || character == '/') {
		return true;
	}
	else {
		return false;
	}
}

bool parseParentheses(stack<char> paren) {
	stack<char> temp;

	while (!paren.empty()) {
		if (paren.top() == ')') {


			// put all preceding closed parens in stack
			while (!paren.empty() && paren.top() == ')') {
				temp.push(paren.top());
				paren.pop();
			}

			// pop one off of temp for each subsequent open you get
			while (!paren.empty() && !temp.empty() && paren.top() == '(') { //ADDED: !temp.empty()
				temp.pop();
				paren.pop();
			}
		}

		// if you're ever looking at an open paren
		// without having seen an closed one, it's no good
		else {
			return false;
		}
	}

	return temp.empty();
}
	/*if (paren.empty()) {
		return true;
	}
	stack<char> temp;
	while (!paren.empty()) {
		if (paren.top() == ')') {
			temp.push(paren.top());
			paren.pop();
		}
		else if (paren.top() == '(') {
			if (temp.empty()) {
				return false;
			}
			else {
				paren.pop();
				temp.pop();
			}
		}
	}
	return true;
	*/
	

bool lettersInMap(string infix, const Map& values) {// return true if all letters in infix are in map, return false otherwise
	for (int i = 0; i < int(infix.length()); i++) {
		if (isalpha(infix[i]) && islower(infix[i]) && !values.contains(infix[i])) {
			return false;
		}
	}
	return true;
}
void infixToPostfix(string infix, string& postfix) {
	postfix = "";
	stack<char> Stack;
	char ch;
	for (int i = 0; i < int(infix.length()); i++) {
		ch = infix[i];
		switch (ch) {
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': 
		case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
				postfix += ch;
				break;
			case'(':
				Stack.push(ch);
				break;
			case')':
				while (Stack.top() != '(') { //ADDED !Stack.empty()
					postfix += Stack.top();
					Stack.pop();
				}
				Stack.pop();//ADDED While loop
				break;
			case '+': case '-':
			case '*':case '/':
				while (!Stack.empty() && Stack.top() != '(' && findPrecedence(ch) <= findPrecedence(Stack.top())) {
					postfix += Stack.top();
					Stack.pop();
				}
				Stack.push(ch);
				break;
		}
	}
	while (!Stack.empty()){
		postfix += Stack.top();
		Stack.pop();
	}
}
int findPrecedence(char sign) {
	switch (sign) {
		case'+':
		case'-':
			return 1;
			break;
		case'*':
		case'/':
			return 2;
			break;
	}
	return -1;
}
bool evaluatePostfix(string postfix, const Map& values, int& finalResult) {
	stack<int> operandStack;
	int value;
	int result;
	for (int i = 0; i < int(postfix.length()); i++) {
		char ch = postfix[i];
		if (isalpha(ch)) { //ch is an operand
			values.get(ch, value);
			operandStack.push(value);
		}
		else { //ch is a binary operator
			int operand2 = operandStack.top();
			operandStack.pop();
			int operand1 = operandStack.top();
			operandStack.pop();
			switch (ch) {
				case '+':
					result = operand1 + operand2;
					break;
				case '-':
					result = operand1 - operand2;
					break;
				case '*':
					result = operand1 * operand2;
					break;
				case '/':
					if (operand2 == 0) { //attempted division by zero
						return false;
					}
					result = operand1 / operand2;
					break;
			}
			operandStack.push(result);
		}
	}
	finalResult = operandStack.top();
	return true;
}

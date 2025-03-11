//Infix to Postfix Converter Class

#include <iostream>
#include <stack>
#include <cctype>
#include <stdexcept>

using namespace std;

class InfixToPostfixConverter {
private:
	string infix; //For storing infix input
	string postfix; //For storing converted postfix

	//Function to determine the precedence of operators
	int precedence(char oper) {
		if (oper == '+' || oper == '-') {
			return 1;
		}
		else if (oper == '*' || oper == '/') {
			return 2;
		}
		else {
			return 0;
		}
	}

	//Function for checking if a character is an operator or not
	bool isOperator(char c) {
		return (c == '+' || c == '-' || c == '*' || c == '/');
	}

public:

	//Default constructor:
	InfixToPostfixConverter() : infix(""), postfix("") {}

	//Parameterized constructor: initializing with an infix
	InfixToPostfixConverter(const string& exp) {
		setInfix(exp);
	}

	//Setter for infix
	void setInfix(const string& exp) {
		infix = exp;
		postfix = "";
	}

	//Getter for postfix
	string getPostfix() const {
		return postfix;
	}

	//Converting an infix to postfix expression
	void converter() {
		stack<char> oprStack; //Stack to hold operators
		postfix = ""; //clearing the previous one

		for (size_t i = 0; i < infix.length(); i++) {
			char c = infix[i];

			//Skip if whitespace
			if (isspace(c)) {
				continue;
			}

			//If the character is an operand adding it to postfix
			if (isalnum(c)) {
				postfix += c;
			}
			else if (c == '(') { //If it is an openning parenthesis
				oprStack.push(c);
			}
			else if (c == ')') { //If it is a closing parenthesis
				while (!oprStack.empty() && oprStack.top() != '(') {
					postfix += oprStack.top();
					oprStack.pop();
				}
				if (!oprStack.empty()) {
					oprStack.pop(); //Remove the '(' from stack
				}
				else {
					throw invalid_argument("Mismatched parenthesis in the expression!");
				}
			}
			else if (isOperator(c)) { //If character is an operator
				while (!oprStack.empty() && precedence(oprStack.top()) >= precedence(c)) {
					postfix += oprStack.top();
					oprStack.pop();
				}
				oprStack.push(c); //Pushing the current operator into the stack
			}
			else {
				throw invalid_argument("Invalid character! " + string(1, c));
			}
		}

		//Popping the remaining operators and adding it to postfix
		while (!oprStack.empty()) {
			if (oprStack.top() == '(') {
				throw invalid_argument("Mismatched parenthesis!");
			}
			postfix += oprStack.top();
			oprStack.pop();
		}
	}
};

//Main program

int main() {
	try {
		//Test case 1
		InfixToPostfixConverter input1("1+2*4");
		input1.converter();
		cout << "Infix: 1+2*4\nPostfix: " << input1.getPostfix() << endl;

		//Test case 2, with parenthesis
		InfixToPostfixConverter input2("(1+2)*4");
		input2.converter();
		cout << "\nInfix: (1+2)*4\nPostfix: " << input2.getPostfix() << endl;

		//Test case 3
		InfixToPostfixConverter input3("2+2*(4-2)/4");
		input3.converter();
		cout << "\nInfix: 2+2*(4-2)/4\nPostfix: " << input3.getPostfix() << endl;

		//Test case 4, with mismatched parenthesis
		InfixToPostfixConverter input4("2+2)*3");
		input4.converter();
		cout << "\nInfix: 2+2)*3\nPostfix: " << input4.getPostfix() << endl;

	}
	catch (const exception& e) {
		cout << "\nError: " << e.what() << endl;
	}

	return 0;
}

//Postfix Evaluator Class

#include <iostream>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <fstream>

using namespace std;

class PostfixEvaluator {
private:
	string postfix;
	double res; //For results

	//Function to check if a string represents a number or not
	bool isNumber(const string& str) {
		return !str.empty() && (isdigit(str[0]) || (str[0] == '-' && str.size() > 1));
	}

public:
	//Default constructor
	PostfixEvaluator() : postfix(""), res(0.0) {}

	//Parameterized constructor
	PostfixEvaluator(const string& exp) {
		setPostfix(exp);
	}

	//Setter for postfix
	void setPostfix(const string& exp) {
		postfix = exp;
		res = 0; //Before evaluation
	}

	//Getter for result
	double getResult() const {
		return res;
	}

	//Function for evaluating postfix using a stack
	void evaluatePostfix() {
		stack<double> evaStack;
		stringstream ss(postfix);
		string token;

		while (ss >> token) {
			//If is a number push onto the stack
			if (isNumber(token)) {
				evaStack.push(stod(token));
			}
			else if (token == "+" || token == "-" || token == "*" || token == "/") { //if the token is an operator then perform computation
				if (evaStack.size() < 2) {
					throw invalid_argument("Not enough operands before operator  '" + token + "'");
				}

				double b = evaStack.top(); evaStack.pop();
				double a = evaStack.top(); evaStack.pop();

				if (token == "+") {
					evaStack.push(b + a);
				}
				else if (token == "-") {
					evaStack.push(b - a);
				}
				else if (token == "*") {
					evaStack.push(b * a);
				}
				else if (token == "/") {
					if (b == 0) {
						throw invalid_argument("Error: Division by zero!");
					}
					evaStack.push(b / b);
				}
			}
			else {
				throw invalid_argument("Invalid token: " + token);
			}
		}
		//One result should be exaclty left in stack
		if (evaStack.size() != 1) {
			throw invalid_argument("Too many operands!");
		}
		res = evaStack.top();
	}
};

//Main program

int main() {
	ifstream openFile("RpnData.txt"); //To open the file
	if (!openFile) {
		cerr << "Error: Unable to open the RpnData.txt file!" << endl;
		return 1;
	}

	string line;
	while (getline(openFile, line)) {
		try {
			PostfixEvaluator evaluator(line);
			evaluator.evaluatePostfix();
			cout << "Postfix: " << line << " => Result: " << evaluator.getResult() << endl;
		}
		catch (const exception& e) {
			cout << "Postfix: " << line << " => Error: " << e.what() << endl;
		}
	}

	openFile.close();

	return 0;
}

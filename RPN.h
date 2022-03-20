
#include <vector>
#include <string>
#include <iostream>
#include "BinaryNumber.h"
#include "Stack.h"
using namespace std;

template <typename T>
class RPN {
    vector<string> expression;
public:

    RPN(vector<string> expr) {
        expression = expr;
    }

    bool isOperator(string& exp) {
        return (exp == "+" || exp == "-" || exp == "*");
    }


    BinaryNumber<T> evaluate() {
        auto* stack = new Stack<BinaryNumber<T>>();
        for (string e : expression) {
            if (!isOperator(e)) {
                try {
                    BinaryNumber<T> num = BinaryNumber<T>(stoi(e));
                    cout << "Binary representation of operand: ";
                    num.printBinArray(num.mainArray);
                    cout << endl;
                    stack->push(num);
                }
                catch (std::invalid_argument& exc) {
                    throw "Invalid symbol in expression";
                }
            }
            else {
                BinaryNumber<T> a = stack->pop();
                BinaryNumber<T> b = stack->pop();
                BinaryNumber<T> r;
                if (e == "+") r = a + b;
                else if (e == "-") r = b - a;
                else if (e == "*") r = a * b;
                stack->push(r);
            }

        }
        BinaryNumber<T> result = stack->pop();
        if (!stack->empty()) {
            throw "Invalid expression";
        }
        return result;
    }
};



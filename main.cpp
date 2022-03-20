#include <iostream>
#include "RPN.h"
#include "BinaryNumber.h"
using T = char;

int main(int argc, char* argv[]) {
    string expression;
    vector<string> vector;
    cout << "Enter expression: ";
    while ((cin.peek() != '\n') && (cin.peek() != EOF)) {
        cin >> expression;
        vector.push_back(expression);
    }
    try {
        auto* machine = new RPN<T>(vector);
        BinaryNumber<T> result = machine->evaluate();

        cout << "Result: "; result.printBinArray(result.mainArray);
        cout << endl;
        cout << "Decimal result: " << +result.binToDec(result.mainArray);
       
        cout << endl;
    }
    catch (const char* exception) {
        cout << "Error" << endl;
    }
}
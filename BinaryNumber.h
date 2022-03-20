#pragma once
#include <iostream>
#include <cmath>
#include <string>

//template<typename T>
class BinaryNumber {
private:
    int num;
    int size = 8;
public:
    int* mainArray = new int[size];
    bool isNegative = false;
    BinaryNumber(): num(0) {};
    BinaryNumber(int user_num) {
        setBinNum(user_num); 
    }

    void setBinNum(int user_num) {
        num = user_num;
        isNegative = module();
        mainArray = decToBin(isNegative);
    }

    bool module() {
        using namespace std;

        bool isNegative = false;

        if (num < 0) {
            isNegative = true;
        }
        return isNegative;
    }

   
    int* decToBin(bool isNegative) {
        using namespace std;

        int* binArray = new int[size];

        if (isNegative) {
            num = -1 * num;
            num = num - 1;
        }

        for (int i = size - 1; i >= 0; i--) {
            binArray[i] = num % 2;
            num = num / 2;
        }

        if (isNegative) {
            binArray = reverseCoding(binArray);
        }
        return binArray;
    }
 
    void printBinArray(int array[]) {
        using namespace std;

        for (int i = 0; i < size; i++) {
            cout << array[i];
        }
        cout << endl;
    }

   
    int* addition(int array1[], int array2[]) const {
        using namespace std;

        int* result = new int[size];
        int reminder = 0;
        int i = size - 1;

        while (i != -1)
        {
            result[i] = array1[i] + array2[i];
            if (result[i] == 0) {
                result[i] = 0 + reminder;
                reminder = 0;
                i--;
            }
            else if (result[i] == 1) {
                result[i] = 1 + reminder;
                if (result[i] == 2) {
                    result[i] = 0;
                    reminder = 1;
                }
                else {
                    reminder = 0;
                }
                i--;
            }
            else if (result[i] == 2) {
                result[i] = 0 + reminder;
                reminder = 1;
                i--;
            }
        }

        if (array1[0] == 0 && array2[0] == 0 && result[0] == 1) {
            throw "Overflow2";
        }
        else if (array1[0] == 1 && array2[0] == 1 && result[0] == 0) {
            throw "Overflow2";
        }
        return result;
    }

    BinaryNumber operator+(const BinaryNumber& other) const {
        using namespace std;

        BinaryNumber A = *this;
        BinaryNumber B = other;
        BinaryNumber C(0);

        C.mainArray = addition(A.mainArray, B.mainArray);

        return C;
    }

    BinaryNumber operator-(const BinaryNumber& other) const {
        using namespace std;

        BinaryNumber A = *this;
        BinaryNumber B = other;
        BinaryNumber C(0);

        
        C.mainArray = extraCoding(reverseCoding(B.mainArray));
        C = A + C;

        return C;
    }

    bool equalLeftLim(int array[]) const {
        int* leftBin = new int[size];
        bool isEqual = true;
        for (int i = 0; i < size; i++) {
            leftBin[i] = 0;
        }
        leftBin[0] = 1;

        for (int i = 0; i < size; i++) {
            if (array[i] != leftBin[i]) {
                isEqual = false;
            }

        }
        return isEqual;
    }


    BinaryNumber operator*(const BinaryNumber& other) const {
        using namespace std;

        BinaryNumber A = *this;
        BinaryNumber B = other;
        BinaryNumber C(0);

        int doubleSize = size * 2;
        int* result = new int[doubleSize];
        for (int i = 0; i < doubleSize; i++)
            result[i] = 0;
        int value = 1;
        bool firstCheck = equalLeftLim(A.mainArray);
        bool secondCheck = equalLeftLim(B.mainArray);

        if (A.mainArray[0] == 1 && firstCheck == 0) {
        
            A.mainArray = extraCoding(reverseCoding(A.mainArray));
            value *= -1;
        }
        if (B.mainArray[0] == 1 && secondCheck == 0) {
            B.mainArray = extraCoding(reverseCoding(B.mainArray));
            value *= -1;
        }
        if (A.mainArray[0] == 1 && firstCheck == 1) {
            value *= -1;
        }
        if (B.mainArray[0] == 1 && secondCheck == 1) {
            value *= -1;
        }

        for (int i = size - 1; i >= 0; i--)
        {
            for (int j = size - 1; j >= 0; j--)
            {
                if (result[j + i + 1] > 1) {
                    result[j + i + 1] = A.mainArray[j] * B.mainArray[i];
                    result[i + j]++;
                }
                else
                {
                    result[j + i + 1] += A.mainArray[j] * B.mainArray[i];
                    if (result[j + i + 1] > 1) {
                        result[j + i + 1] = 0;
                        result[i + j] ++;
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            if (result[i] == 1)
                throw "Overflow";
        }
        if (value == 1 && result[size] == 1) {
            for (int i = size; i < doubleSize; i++) {
                if (result[i] == 1)
                    throw "Overflow";
            }
        }
        else if (value == -1 && result[size] == 1) {
            for (int i = size + 1; i < doubleSize; i++) {
                if (result[i] == 1)
                    throw "Overflow";
            }
        }

        int j = 0;
        for (int i = size; i < doubleSize; i++) {
            C.mainArray[j] = result[i];
            j = j + 1;
        }
        return C;
    }


    int* reverseCoding(int binArray[]) const {
        using namespace std;

        for (int i = 0; i < size; i++) {
            if (binArray[i] == 0) {
                binArray[i] = 1;
            }
            else {
                binArray[i] = 0;
            }
        }
        return binArray;
    }

    
    int* binaryOne() const {
        int* binOne = new int[size];
        for (int i = 0; i < size - 1; i++) {
            binOne[i] = 0;
        }
        binOne[size - 1] = 1; // 00000001
        return binOne;
    }

    //extra code
    int* extraCoding(int binArray[]) const {
        using namespace std;

       
        binArray = addition(binArray, binaryOne());

        return binArray;
    }

    int binToDec(int result[]) {
        using namespace std;
        int* array = new int[size];
        int sum = 0;

        for (int i = size - 1; i >= 0; i--) {
            array[i] = i;
        }
        int j = size - 1;
        for (int i = 0; i < size; i++) {
            sum += result[i] * pow(2, array[j]);
            j = j - 1;
        }
        return sum;
    }
};



#include <iostream>
using namespace std;

// Return the number of digits in d
int getSize(long long d) {
    int size = 0;
    while (d != 0) {
        d = d / 10;
        size++;
    }
    return size;
}

// Return the first k number of digits from number.
// If the number of digits in number is less than k, return number.
long long getPrefix(long long number, int k) {
    int size = getSize(number);
    if (size < k) {
        return number;
    }
    for (int i = 0; i < size - k; i++) {
        number = number / 10;
    }
    return number;
}

// Return true if the digit d is a prefix for number
bool prefixMatched(long long number, int d) {
    int size = getSize(d);
    return getPrefix(number, size) == d;
}

// Return this number if it is a single digit,
// otherwise, return the sum of the two digits
int getDigit(int number) {
    if (number < 10) {
        return number;
    }
    return number / 10 + number % 10;
}

// Return sum of odd place digits in number
int sumOfOddPlace(long long number) {
    int sum = 0;
    while (number != 0) {
        sum += number % 10;
        number = number / 100;
    }
    return sum;
}

// Return the result from Step 2 (sum of doubled even-place digits)
int sumOfDoubleEvenPlace(long long number) {
    int sum = 0;
    number = number / 10; // move to the first even-place digit (from right)
    while (number != 0) {
        int digit = number % 10;
        sum += getDigit(digit * 2);
        number = number / 100;
    }
    return sum;
}

// Return true if the card number is valid
bool isValid(long long number) {
    int size = getSize(number);
    return (size >= 13 && size <= 16) &&
           (prefixMatched(number, 4) || prefixMatched(number, 5) ||
            prefixMatched(number, 37) || prefixMatched(number, 6)) &&
           ((sumOfDoubleEvenPlace(number) + sumOfOddPlace(number)) % 10 == 0);
}

int main() {
    long long number;
    cout << "Enter a credit card number as a long integer: ";
    cin >> number;

    if (isValid(number)) {
        cout << number << " is valid" << endl;
    } else {
        cout << number << " is invalid" << endl;
    }

    return 0;
}
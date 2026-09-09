// (Population projection) UBoS projects population based on the
// following assumptions:
// One birth every 7 seconds
// One death every 13 seconds
// One new immigrant every 45 seconds
// Write a program to display the population for each of the next five years. Assume the current population is 312032486 and one year has 365 days.

#include <iostream>
using namespace std;

int main() {
    const double SECONDS_PER_YEAR = 365 * 24 * 60 * 60;
    long long population = 312032486;

    for (int year = 1; year <= 5; year++) {
        long long births = SECONDS_PER_YEAR / 7;
        long long deaths = SECONDS_PER_YEAR / 13;
        long long immigrants = SECONDS_PER_YEAR / 45;

        population += births - deaths + immigrants;

        cout << "Year " << year << ": " << population << endl;
    }

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    const int NUM_STUDENTS = 8;
    const int NUM_QUESTIONS = 10;

    char answers[NUM_STUDENTS][NUM_QUESTIONS] = {
        {'A', 'B', 'A', 'C', 'C', 'D', 'E', 'E', 'A', 'D'},
        {'D', 'B', 'A', 'B', 'C', 'A', 'E', 'E', 'A', 'D'},
        {'E', 'D', 'D', 'A', 'C', 'B', 'E', 'E', 'A', 'D'},
        {'C', 'B', 'A', 'E', 'D', 'C', 'E', 'E', 'A', 'D'},
        {'A', 'B', 'D', 'C', 'C', 'D', 'E', 'E', 'A', 'D'},
        {'B', 'B', 'E', 'C', 'C', 'D', 'E', 'E', 'A', 'D'},
        {'B', 'B', 'A', 'C', 'C', 'D', 'E', 'E', 'A', 'D'},
        {'E', 'B', 'E', 'C', 'C', 'D', 'E', 'E', 'A', 'D'}
    };

    char keys[NUM_QUESTIONS] = {'D', 'B', 'D', 'C', 'C', 'D', 'A', 'E', 'A', 'D'};

    for (int student = 0; student < NUM_STUDENTS; student++) {
        int correctCount = 0;
        for (int question = 0; question < NUM_QUESTIONS; question++) {
            if (answers[student][question] == keys[question]) {
                correctCount++;
            }
        }
        cout << "Student " << student << "'s correct count is " << correctCount << endl;
    }

    return 0;
}
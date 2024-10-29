#include <iostream>
#include<cmath>
#include<ctime>

using namespace std;

class guessMyNum {
    private:
        int secret_num;
        int upper_bound;
        int lower_bound;
        int* num_arr;
    
    public:
        guessMyNum(int high, int low) {
            upper_bound = high;
            lower_bound = low;
            num_arr = new int[upper_bound-lower_bound + 1];

            
            srand(time(nullptr));
            secret_num = rand() % (high - low + 1);
            secret_num = secret_num + low;

            // create array using pointer arithmetic
            for (int i=0; i<upper_bound - lower_bound + 1; i++) {
                *(num_arr + i) = i + low;
            }
        }

        void playGame() {
            int guess = -1;
            int attempts = 0;
            int lowest_poss = lower_bound;
            int highest_poss = upper_bound;
            
            while (guess != secret_num) {
                cout << "Guess a number between " << lowest_poss << " and " << 
            highest_poss << ": " << endl;
                cin >> guess;

                if (guess > secret_num) {
                    highest_poss = guess - 1;
                    cout << "Too high!" << endl;
                    }
                else if (guess < secret_num) {
                    lowest_poss = guess + 1;
                    cout << "Too low!" << endl;
                    }
                cout << "Possible numbers: [";
                for (int i=0; i<upper_bound - lower_bound + 1; i++) {
                        if (*(num_arr + i) <= highest_poss && *(num_arr + i) >= lowest_poss) {
                            cout << *(num_arr + i);
                            if (i < upper_bound - lower_bound) cout << ", ";
                        }
                    }
                cout << "]" << endl;
                attempts++;
            }
            cout << "Correct! You guessed the number " << secret_num << " correctly in "
            << attempts << " attempts!" << endl;
        }
};

int main() {
    int low1;
    int high1;
    int low2;
    int high2;
    cout << "Welcome to Guess My Number! You'll play two rounds." << endl;
    cout << "-------------------------------------------" << endl;
    cout << "ROUND ONE:" << endl;
    cout << "Choose a lower number: " << endl;
    cin >> low1;
    cout << "Choose a higher number: " << endl;
    cin >> high1;
    guessMyNum round_one(high1, low1);
    round_one.playGame();


    cout << "-------------------------------------------" << endl;
    cout << "ROUND TWO:" << endl;
    cout << "Choose a lower number: " << endl;
    cin >> low2;
    cout << "Choose a higher number: " << endl;
    cin >> high2;
    guessMyNum* round_two = new guessMyNum(high2, low2);
    round_two->playGame();
    return 0;
}
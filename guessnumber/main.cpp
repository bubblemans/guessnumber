// This program is to interact with the player playing number guessing. The user will be asked to input a password, and the computer will guess the password. Also, the user will be asked to guess a number which is computer's password. There will be tips for users and computer, such as 1A3B which means there is one correct digit in correct position, and three correct digits in wrong position. For example, computer's password is 1234, and a user input 1478. Then the computer will tell you 1A1B. Because 1 is correct and in right position. 4 is correct but in the wrong position.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
bool checknumber(int, int);
bool guessnumber(int, int [], int&);

int main() {
    // Create a list of all possibility.
    int size = 10 * 9 * 8 * 7;
    int list[size];
    int i = 0;
        for (int j = 9; j > 0; j--) {
            for (int k = 9; k >= 0; k--) {
                for (int l = 9; l >= 0; l--) {
                    for (int m = 9; m >= 0; m--) {
                        if (j!=k && j!=l && j!= m && k!=l && k!=m && l!=m) {
                            list[i] = j * 1000 + k * 100 + l * 10 + m;
                            i++;
                        }
                    }
                }
            }
        }
    // Set a different random series by time.
    srand((unsigned) time(0));
    int comnum = list[rand() % size];
    int num;
    int usernum;
    bool found = false, guess = false;
    // The computer and the user will take turns guessing each other's password.
    cout <<"Please enter your password:\n";
    cin >> usernum;
    cout << "Please guess computer's 4 digit number(all different):\n";
    cin >> num;
    while (!found) {
        found = checknumber(num, comnum);
        guess = guessnumber(usernum, list, size);
        if ((found)&&(!guess)){
            cout <<"You win.\n";
            break;
        }
        else if((guess)&&(!found)){
            cout <<"You lose. My number is " << comnum << endl;
            break;
        }
        else if((guess)&&(found)){
            cout << "Draw!\n";
            break;
        }
        if (!found) {
            cout << "Your turn: ";
            cin >> num;
        }
    }
}

// Check the password the user input is correct or not.
bool checknumber(int num, int comnum){
    string strnum = to_string(num);
    string strcomnum = to_string(comnum);
    int a = 0 , b = 0;
    // Check the password's number and position.
    for (int i = 0; i < 4; i++) {
        if (strnum[i] == strcomnum[i]) {
            a++;
        }
        for (int j = 0; j < 4; j++) {
            if ((i != j)&&(strnum[i] == strcomnum[j])){
                b++;
            }
        }
    }
    cout << a << "A" << b << "B" << endl;
    if ((a == 4)&&(b == 0)) {
        return true;
    }
    return false;
}

// Computer will random a number and check if it is right or not.
bool guessnumber(int usernum, int list[], int &size){
    // Random a number.
    int randomguess = list[rand() % size];
    cout << "My turn: " << randomguess << endl;
    
    string strusernum = to_string(usernum);
    string strrandomguess = to_string(randomguess);
    //Check the password's number and position.
    int a = 0 , b = 0;
    for (int i = 0; i < 4; i++) {
        if (strusernum[i] == strrandomguess[i]) {
            a++;
        }
        for (int j = 0; j < 4; j++) {
            if ((i != j)&&(strusernum[i] == strrandomguess[j])){
                b++;
            }
        }
    }
    cout << a << "A" << b << "B" << endl;
    cout << endl;
    if ((a == 4)&&(b == 0)) {
        return true;
    }
    // Remove all the possibilities which are not meet the tips.
    for (int k = 0; k < size; k++) {
        string temp = to_string(list[k]);
        int A = 0 , B = 0;
        for (int i = 0; i < 4; i++) {
            if (temp[i] == strrandomguess[i]) {
                A++;
            }
            for (int j = 0; j < 4; j++) {
                if ((i != j)&&(temp[i] == strrandomguess[j])){
                    B++;
                }
            }
        }
        if (!((A == a)&&(B == b))) {
            for (int m = k; m < size; m++) {
                list[m] = list[m+1];
            }
            size--;
            k--;
        }
    }
    return false;
}

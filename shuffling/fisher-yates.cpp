#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

string shuffle(const string &givenString) {
    string shuffledString = givenString;
    for (int i = 0; i < shuffledString.size() - 1; ++i) {
        int j = rand() % (shuffledString.size() - i) + i;
        swap(shuffledString[i], shuffledString[j]);
    }
    return shuffledString;
}

int main() {
    srand(time(NULL));
    string text = "Text to Shuffle";
    
    cout << shuffle("Text to Shuffle") << endl;

    return 0;
}
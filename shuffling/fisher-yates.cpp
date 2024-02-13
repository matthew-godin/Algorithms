#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
    srand(time(NULL));
    string text = "Text to Shuffle";
    
    for (int i = 0; i < text.size() - 1; ++i) {
        int j = rand() % (text.size() - i) + i;
        swap(text[i], text[j]);
    }
    
    cout << text << endl;

    return 0;
}
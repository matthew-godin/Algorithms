#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<string> split(const string &givenString, const char &separator) {
    vector<string> stringSplit;
    stringstream stringStream(givenString);
    string splitString;
    while (getline(stringStream, splitString, separator)) {
        stringSplit.push_back(splitString);
    }
    return stringSplit;
}

int main() {
    string text = "abcdef;12345;a;b;c";
    
    vector<string> textTokens = split(text, ';');
    for (int i = 0; i < textTokens.size(); ++i) {
        cout << textTokens[i] << endl;
    }

    return 0;
}
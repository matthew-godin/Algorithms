#include <iostream>
#include <vector>
using namespace std;

void populateLPS(vector<int> &lps, const string &pattern) {
    int j = 0;
    lps[0] = 0;
    for (int i = 1; i < pattern.length();) {
        if (pattern[i] == pattern[j]) {
            lps[i] = ++j;
            ++i;
        } else {
            if (j > 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                ++i;
            }
        }
    }
}

int searchKMP(const string &pattern, const string &text) {
    int numOccurrences = 0;
    int j = 0;
    vector<int> lps(pattern.length());
    populateLPS(lps, pattern);
    for (int i = 0; text.length() - i >= pattern.length() - j;) {
        if (pattern[j] == text[i]) {
            ++j;
            ++i;
        }
        if (j == pattern.length()) {
            // Found pattern
            ++numOccurrences;
            j = lps[j - 1];
        } else if (i < text.length() && pattern[j] != text[i]) {
            if (j > 0) {
                j = lps[j - 1];
            } else {
                ++i;
            }
        }
    }
    return numOccurrences;
}

int main() {
    string pattern = "AAACAAA";
    string text = "AAACAAAACAAACAAACAAAAAAAAACAACAAAACAAAAAAACAAAA";
    
    cout << searchKMP(pattern, text) << endl;

    return 0;
}
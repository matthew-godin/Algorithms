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

int main() {
    string pattern = "AAACAAAA";
    vector<int> lps(pattern.length());
    populateLPS(lps, pattern);

    return 0;
}
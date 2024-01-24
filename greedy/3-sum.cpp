#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> find3Sum(vector<int> arr, int sum) {
    vector<int> answer = { -1, -1, -1 };
    int l, r;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < arr.size() - 2; ++i) {
        l = i + 1;
        r = arr.size() - 1;
        while (l < r) {
            int currentSum = arr[i] + arr[l] + arr[r];
            if (currentSum == sum) {
                answer[0] = arr[i];
                answer[1] = arr[l];
                answer[2] = arr[r];
                return answer;
            } else if (currentSum < sum) {
                ++l;
            } else {
                --r;
            }
        }
    }
    return answer;
}

int main() {
    vector<int> arr = { 12, 3, 4, 1, 6, 9 };
    int sum = 24;
    vector<int> answer = find3Sum(arr, sum);
    cout << answer[0] << " " << answer[1] << " " << answer[2] << endl;
    return 0;
}
#include <chrono>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int MaxSubseqSum4(int A[], int n, int& start, int& end) //在线处理
{
    int max = -1, curr = 0;
    int currStart = 0;
    start = 0, end = n - 1;
    for (int i = 0; i < n; i++) {
        curr += A[i];
        if (curr > max) {
            max = curr;
            start = A[currStart];
            end = A[i];
        } else if (curr < 0) {
            curr = 0;
            currStart = i + 1;
        }
    }
    if (max == -1) {
        max = 0;
        start = A[0], end = A[n - 1];
    }
    return max;
}
int main()
{
    int A[100000]{ 0 };
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int i, j;
    cout << MaxSubseqSum4(A, n, i, j) << " " << i << " " << j;
    return 0;
}
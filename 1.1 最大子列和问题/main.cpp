#include <chrono>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono_literals;
int max(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
int ScanForRight(int A[], int n)
{
    int sum = 0, max = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}
int ScanForLeft(int A[], int n)
{
    int sum = 0, max = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += A[i];
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}
int MaxSubseqSum1(int A[], int n) //时间复杂度o(n^3)
{
    int max = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int curr = 0;
            for (int k = i; k < j; k++) {
                curr += A[k];
            }
            if (curr > max) {
                max = curr;
            }
        }
    }
    return max;
}
int MaxSubseqSum2(int A[], int n) //时间复杂度o(n^2)
{
    int max = 0;
    for (int i = 0; i < n; i++) {
        int curr = 0;
        for (int j = i; j < n; j++) {
            curr += A[j];
            if (curr > max) {
                max = curr;
            }
        }
    }
    return max;
}
int MaxSubseqSum3(int A[], int n) //分而治之
{
    if (n == 1) {
        return A[0];
    } else if (n == 2) {
        return max(A[0], A[1]);
    } else {
        int middle = ScanForLeft(A, n / 2) + ScanForRight(&A[n / 2], n / 2 + n % 2);
        return max(max(middle, MaxSubseqSum3(A, n / 2)), MaxSubseqSum3(&A[n / 2], n / 2 + n % 2));
    }
}
int MaxSubseqSum4(int A[], int n)//在线处理
{ 
    int max = 0, curr = 0;
    for (int i = 0; i < n; i++) {
        curr += A[i];
        if (curr > max) {
            max = curr;
        } else if (curr < 0) {
            curr = 0;
        }
    }
    return max;
}
int main()
{
    int A[100]{ 4, -3, 5, -2, -1, 2, 6, -2, -1, 22 };
    int n = 8;
    //auto start = std::chrono::high_resolution_clock::now(); //开始计时
    cout << MaxSubseqSum4(A, n) << endl;
    //auto end = std::chrono::high_resolution_clock::now(); //结束计时
    std::chrono::duration<double, std::milli> elapsed = end - start; //计算时间差
    //cout << "time cost: " << elapsed.count() << " ms\n";
    return 0;
}
#include <iostream>
#include <chrono>
using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono_literals;
int main(){
    auto start = std::chrono::high_resolution_clock::now(); //开始计时

    auto end = std::chrono::high_resolution_clock::now();   //结束计时
    std::chrono::duration<double, std::milli> elapsed = end-start; //计算时间差
    std::cout << "time cost: " << elapsed.count() << " ms\n";
    return 0;
}
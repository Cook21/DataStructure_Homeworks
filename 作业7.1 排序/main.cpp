#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::list;
using std::vector;

void popSort(vector<int>& container){
    bool isSwaped=true;
    for(int i=0;i<container.size()-1&&isSwaped;i++){
        isSwaped=false;
        for(int j=0;j<container.size()-i-1;j++){
            if(container[j]>container[j+1]){
                int temp=container[j];
                container[j]=container[j+1];
                container[j+1]=temp;
                isSwaped=true;
            }
        }
    }
}
void insertionSort(vector<int>& container){
    for(int sortedSize=1;sortedSize<container.size();sortedSize++){
        int curr=container[sortedSize];
        int i;
        for(i=sortedSize-1;i>=0&&container[i]>curr;i--){
            container[i+1]=container[i];
        }
        container[i+1]=curr;
    }
}
int main(){
    int numOfNums;
    cin >> numOfNums;
    vector<int> container{};
    for(int i=0;i<numOfNums;i++){
        int temp;
        cin >> temp;
        container.push_back(temp);
    }
    //popSort(container);
    insertionSort(container);
    for(auto i:container){
        cout << i << " ";
    }
}
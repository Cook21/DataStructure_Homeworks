#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <iomanip> //设置小数点输出需要
#include <vector>
#include<deque>
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::deque;
int depthFirstSearch(int curr, const vector<list<int>>& adjacencyTable, int depth=1)
{
    static vector<bool> visited;
    if(depth==1){
        visited=vector<bool>(adjacencyTable.size(),false);
        visited[curr] = true;
    }
    if (depth <= 6) {
        for (auto i : adjacencyTable[curr]) {
            if (!visited[i]) {
                visited[i] = true;
                depthFirstSearch(i, adjacencyTable, depth + 1);
            }
        }
    }
    if(depth==1){
        int count = 0;
        for (int j = 0; j < adjacencyTable.size(); j++) {
            if (visited[j]) {
                count++;
            }
        }
        return count;
    }else{
        return 0;
    }

}
int breadthFirstSearch(int startNode,vector<list<int>> adjacencyTable){
    vector<bool> visited(adjacencyTable.size(),false);
    deque<int> queue{};
    queue.push_back(startNode);
    visited[startNode]=true;
    int level=0;
    int thisLevelLast=startNode;
    int count=1;
    int nextLevelLast;
    while(!queue.empty()&&level<=5){
        int currNode=queue.front();
        queue.pop_front();
        for (auto neighbourNode : adjacencyTable[currNode]) {
            if (!visited[neighbourNode]) {
                visited[neighbourNode] = true;
                queue.push_back(neighbourNode);
                count++;
                nextLevelLast = neighbourNode;
            }
        }
        if(currNode==thisLevelLast){
            level++;
            thisLevelLast=nextLevelLast;
        }
    }
    return count;
}
int main()
{
    int numOfNode, numOfEdge;
    cin >> numOfNode >> numOfEdge;
    vector<list<int>> adjacencyTable(numOfNode, list<int> {});
    for (int i = 0; i < numOfEdge; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        node1--;
        node2--;
        adjacencyTable[node1].push_front(node2);
        adjacencyTable[node2].push_front(node1);
    }
    for (int i = 0; i < numOfNode; i++) {
        double count = breadthFirstSearch(i, adjacencyTable);
        cout << i + 1 << ": " << std::setprecision(2) << std::fixed << count / numOfNode * 100 << "%\n";
    }
}
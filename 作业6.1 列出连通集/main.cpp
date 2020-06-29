#include <deque>
#include <iostream>
#include <sstream>
#include <vector>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::vector;

class Graph {
public:
    int size;
    vector<bool> adjacencyMatrix; //邻接矩阵的下三角矩阵, 不含对角线
    Graph(int size_)
    {
        size = size_;
        adjacencyMatrix.resize((size * size - size) / 2, 0);
    }
    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    int adressTranslate(int node1, int node2)
    {
        if (node2 > node1) {
            swap(node1, node2);
        }
        return (node1) * (node1 - 1) / 2 + node2;
    }
    void connect(int node1, int node2)
    {
        if (node1 != node2) {
            adjacencyMatrix[adressTranslate(node1, node2)] = 1;
        }
    }
    bool check(int node1, int node2)
    {
        if (node1 != node2) {
            return adjacencyMatrix[adressTranslate(node1, node2)];
        } else {
            return false; //默认对角线元素为0
        }
    }
    void print()
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << check(i, j);
            }
            cout << endl;
        }
    }
    vector<int> breadthFirstSearch(int startNode)
    {
        deque<int> queue {};
        vector<bool> visited(10, 0);
        vector<int> result {};
        queue.push_back(startNode);
        visited[startNode] = 1;
        result.push_back(startNode);
        while (!queue.empty()) {
            int curr = queue.front();
            queue.pop_front();
            for (int i = 0; i < size; i++) {
                if (!visited[i] && check(curr, i)) {
                    queue.push_back(i);
                    visited[i] = 1;
                    result.push_back(i);
                }
            }
        }
        return result;
    }
    vector<int> depthFirstSearch(int startNode)
    {
        static vector<bool> visited(10, 0);
        vector<int> result {};
        visited[startNode] = 1;
        result.push_back(startNode);
        for (int i = 0; i < size; i++) {
            if (!visited[i] && check(i, startNode)) {
                auto temp=depthFirstSearch(i);
                result.insert(result.end(),temp.begin(),temp.end());
            }
        }
        return result;
    }
};
int main()
{
    int numOfVertex, numOfEdge;
    cin >> numOfVertex >> numOfEdge;
    Graph graph { numOfVertex };
    for (int i = 0; i < numOfEdge; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        graph.connect(node1, node2);
    }
    std::stringstream output{};
    vector<bool> visited(numOfVertex, 0);
    for (int i = 0; i < numOfVertex; i++) {
        if(!visited[i]){
            output << "{ ";
            vector<int> result = graph.depthFirstSearch(i);
            for(auto j:result){
                visited[j]=1;
                output <<j << " ";
            }
            output << "}" <<endl;
        }
    }
    visited=vector<bool>(numOfVertex, 0);
    for (int i = 0; i < numOfVertex; i++) {
        if(!visited[i]){
            output << "{ ";
            vector<int> result = graph.breadthFirstSearch(i);
            for(auto j:result){
                visited[j]=1;
                output <<j << " ";
            }
            output << "}" <<endl;
        }
    }
    cout << output.str();

}
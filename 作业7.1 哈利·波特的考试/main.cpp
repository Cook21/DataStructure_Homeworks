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
    vector<int> adjacencyMatrix; //邻接矩阵的下三角矩阵, 不含对角线
    vector<int> minDis;
    vector<int> path;
    static const int posInfinity;
    Graph(int size_)
    {
        size = size_;
        adjacencyMatrix.resize((size * size - size) / 2, posInfinity);
    }
    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    int addressTranslate(int node1, int node2)
    {
        if (node2 > node1) {
            swap(node1, node2);
        }
        return (node1) * (node1 - 1) / 2 + node2;
    }
    void connect(int node1, int node2, int distance)
    {
        if (node1 != node2) {
            adjacencyMatrix[addressTranslate(node1, node2)] = distance;
        }
    }
    int distance(int node1, int node2)
    {
        if (node1 != node2) {
            return adjacencyMatrix[addressTranslate(node1, node2)];
        } else {
            return 0; //默认对角线元素为0
        }
    }
    int minDistance(int node1, int node2)
    {
        if (node1 != node2) {
            return minDis[addressTranslate(node1, node2)];
        } else {
            return 0; //默认对角线元素为0
        }
    }
    void print()
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << minDistance(i, j) << " ";
            }
            cout << endl;
        }
    }
    void Floyd()
    {
        minDis = adjacencyMatrix;
        path.resize(adjacencyMatrix.size(), -1);
        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (i != j && minDistance(i, k) + minDistance(k, j) < minDis[addressTranslate(i, j)]) {
                        minDis[addressTranslate(i, j)] = minDistance(i, k) + minDistance(k, j);
                        path[addressTranslate(i, j)] = k;
                    }
                }
            }
        }
    }
    void pickAnimal()
    {
        int minLine;
        int min=posInfinity;
        for (int i = 0; i < size; i++) {
            int thisLineMax=0;
            for (int j = 0; j < size; j++) {
                if(minDistance(i, j)>thisLineMax){
                    thisLineMax=minDistance(i, j);
                }
            }
            if(thisLineMax==posInfinity){
                minLine=-1;
                break;
            }
            if(thisLineMax<min){
                minLine=i;
                min=thisLineMax;
            }
        }
        if(minLine!=-1){
            cout << minLine+1 << ' ' << min;
        }else{
            cout << 0;
        }
        
    }
};
const int Graph::posInfinity = 10000;
int main()
{
    int numOfNodes, numOfEdges;
    cin >> numOfNodes >> numOfEdges;
    Graph graph { numOfNodes };
    for (int i = 0; i < numOfEdges; i++) {
        int node1, node2, distance;
        cin >> node1 >> node2 >> distance;
        graph.connect(node1 - 1, node2 - 1, distance);
    }
    graph.Floyd();
    graph.pickAnimal();
}
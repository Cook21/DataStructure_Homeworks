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

using NodeID = int;
class Graph {
public:
    class AdjTableElem {
    public:
        NodeID nodeID;
        int cost;
    };
    vector<list<AdjTableElem>> adjacencyTable;
    vector<list<AdjTableElem>> reversedAdjacencyTable; //关键
    vector<int> inDegree;
    vector<int> outDegree;
    vector<int> earliestCompletionTime;
    vector<int> latestCompletionTime; //关键
    int result;
    static const int posInfinity;
    Graph(int size)
    {
        adjacencyTable = vector<list<AdjTableElem>>(size);
        reversedAdjacencyTable = vector<list<AdjTableElem>>(size); //关键
        inDegree = vector<int>(size, 0);
        outDegree = vector<int>(size, 0);
        
    }
    void connect(NodeID node1, NodeID node2, int price)
    {
        adjacencyTable[node1].push_front(AdjTableElem { node2, price }); //保证KeyPath输出顺序
        reversedAdjacencyTable[node2].push_front(AdjTableElem { node1, price }); //关键
        inDegree[node2]++;
        outDegree[node1]++;
    }
    int TopSort()
    {
        earliestCompletionTime = vector<int>(adjacencyTable.size(), posInfinity);
        deque<NodeID> inDegreeEqualsZero {};
        for (NodeID i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] == 0) {
                earliestCompletionTime[i] = 0;
                inDegreeEqualsZero.push_back(i);
            }
        }
        
        while (inDegreeEqualsZero.size() != 0) {
            NodeID currNode = inDegreeEqualsZero.front();
            inDegreeEqualsZero.pop_front();
            for (auto neighbour : adjacencyTable[currNode]) {
                if (--inDegree[neighbour.nodeID] == 0) {
                    inDegreeEqualsZero.push_back(neighbour.nodeID);
                }
                if (earliestCompletionTime[currNode] + neighbour.cost > earliestCompletionTime[neighbour.nodeID] || earliestCompletionTime[neighbour.nodeID] == posInfinity) {
                    earliestCompletionTime[neighbour.nodeID] = earliestCompletionTime[currNode] + neighbour.cost;
                }
            }
        }
        result = 0;
        for (auto compTime : earliestCompletionTime) {
            if (compTime > result) {
                result = compTime;
            }
        }
        if (result == posInfinity) {
            result = 0;
        }
        return result;
    }
    void calcLatestCompTime()
    {
        deque<NodeID> queue {};
        latestCompletionTime = vector<NodeID>(adjacencyTable.size(), posInfinity);
        for (NodeID i = 0; i < adjacencyTable.size(); i++) {
            if (outDegree[i] == 0) { //找末端节点
                queue.push_back(i);
                latestCompletionTime[i] = result;
            }
        }
        while (!queue.empty()) {
            NodeID currNode = queue.front();
            queue.pop_front();
            for (auto neighbour : reversedAdjacencyTable[currNode]) {
                if (latestCompletionTime[currNode] - neighbour.cost < latestCompletionTime[neighbour.nodeID]) {
                    latestCompletionTime[neighbour.nodeID] = latestCompletionTime[currNode] - neighbour.cost;
                }
                if (--outDegree[neighbour.nodeID] == 0) {
                    queue.push_back(neighbour.nodeID);
                }
            }
        }
        /*
        for (NodeID i = 0; i < inDegree.size(); i++) {
            cout << i+1 << ": " << earliestCompletionTime[i] << " " <<latestCompletionTime[i] << endl;
        }
        */
    }
    void findKeyPath()
    {
        for (NodeID currNode = 0; currNode < adjacencyTable.size(); currNode++) {
            for (auto i : adjacencyTable[currNode]) {
                if (latestCompletionTime[i.nodeID] - earliestCompletionTime[currNode] == i.cost) {
                    cout << currNode + 1 << "->" << i.nodeID + 1 << endl;
                }
            }
        }
    }
};

const int Graph::posInfinity = 1000000;
int main()
{
    int numOfNodes, numOfEdges;
    cin >> numOfNodes >> numOfEdges;
    Graph activityOnEdge { numOfNodes };
    for (int i = 0; i < numOfEdges; i++) {
        int node1, node2, cost;
        cin >> node1 >> node2 >> cost;
        activityOnEdge.connect(node1 - 1, node2 - 1, cost);
    }
    int earliestCompletionTime = activityOnEdge.TopSort();
    cout << earliestCompletionTime << endl;
    if (earliestCompletionTime != 0) {
        activityOnEdge.calcLatestCompTime();
        activityOnEdge.findKeyPath();
    }
}
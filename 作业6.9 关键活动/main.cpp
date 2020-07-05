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
    vector<int> earliestCompletionTime;
    vector<int> latestCompletionTime; //关键
    static const int posInfinity;
    Graph(int size)
    {
        adjacencyTable = vector<list<AdjTableElem>>(size);
        reversedAdjacencyTable = vector<list<AdjTableElem>>(size); //关键
        inDegree = vector<int>(size, 0);
        earliestCompletionTime = vector<int>(size, 0);
    }
    void connect(NodeID node1, NodeID node2, int price)
    {
        adjacencyTable[node1].push_front(AdjTableElem { node2, price });
        reversedAdjacencyTable[node2].push_front(AdjTableElem { node1, price }); //关键
        inDegree[node2]++;
    }
    int TopSort()
    {
        vector<NodeID> inDegreeEqualsZero {};
        for (NodeID i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] == 0) {
                inDegreeEqualsZero.push_back(i);
            }
        }
        while (inDegreeEqualsZero.size() != 0) {
            NodeID currNode = inDegreeEqualsZero.back();
            inDegreeEqualsZero.pop_back();
            for (auto neighbour : adjacencyTable[currNode]) {
                if (--inDegree[neighbour.nodeID] == 0) {
                    inDegreeEqualsZero.push_back(neighbour.nodeID);
                }
                if (earliestCompletionTime[currNode] + neighbour.cost > earliestCompletionTime[neighbour.nodeID]) {
                    earliestCompletionTime[neighbour.nodeID] = earliestCompletionTime[currNode] + neighbour.cost;
                }
            }
        }
        int result = 0;
        for (auto compTime : earliestCompletionTime) {
            if (compTime > result) {
                result = compTime;
            }
        }
        return result;
    }
    void calcLatestCompTime()
    {
        deque<NodeID> queue {};
        vector<NodeID> isEnqueued(adjacencyTable.size(), false);
        latestCompletionTime = vector<NodeID>(adjacencyTable.size(), posInfinity);
        for (NodeID i = 0; i < inDegree.size(); i++) {
            if (adjacencyTable[i].size() == 0) {
                queue.push_back(i);
                isEnqueued[i]=true;
                latestCompletionTime[i] = earliestCompletionTime[i];
            }
        }
        while (!queue.empty()) {
            NodeID currNode = queue.front();
            queue.pop_front();
            for (auto neighbour : reversedAdjacencyTable[currNode]) {
                if (latestCompletionTime[currNode] - neighbour.cost < latestCompletionTime[neighbour.nodeID]) {
                    latestCompletionTime[neighbour.nodeID] = latestCompletionTime[currNode] - neighbour.cost;
                }
                if (!isEnqueued[neighbour.nodeID]) {
                    queue.push_back(neighbour.nodeID);
                    isEnqueued[neighbour.nodeID] = true;
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
                    cout << currNode + 1 << "->" << i.nodeID+1 << endl;
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
    if (earliestCompletionTime == -1) {
        cout << "Impossible" << endl;
    } else {
        cout << earliestCompletionTime << endl;
    }
    activityOnEdge.calcLatestCompTime();
    activityOnEdge.findKeyPath();
}
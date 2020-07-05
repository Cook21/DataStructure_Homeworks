#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
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
    vector<int> inDegree;
    vector<int> earliestCompletionTime;
    static const int posInfinity;
    Graph(int size)
    {
        adjacencyTable = vector<list<AdjTableElem>>(size);
        inDegree = vector<int>(size, 0);
        earliestCompletionTime = vector<int>(size, 0);
    }
    void connect(NodeID node1, NodeID node2, int price)
    {
        adjacencyTable[node1].push_front(AdjTableElem { node2, price });
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
            //adjacencyTable[currNode].clear();
        }
        int result = 0;
        for (auto i : inDegree) {
            if (i != 0) {
                result = -1;
            }
        }
        if (result != -1) {
            for (auto compTime : earliestCompletionTime) {
                if (compTime > result) {
                    result = compTime;
                }
            }
        }
        return result;
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
        activityOnEdge.connect(node1, node2, cost);
    }
    int earliestCompletionTime=activityOnEdge.TopSort();
    if(earliestCompletionTime==-1){
        cout << "Impossible";
    }else{
        cout << earliestCompletionTime;
    }
}
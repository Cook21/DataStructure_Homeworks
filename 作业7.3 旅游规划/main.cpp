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
class Graph {
public:
    class adjTableElem {
    public:
        int nodeID;
        int distance;
        int price;
    };
    vector<list<adjTableElem>> adjacencyTable;
    vector<int> distanceFromSource;
    vector<int> priceFromSource;
    static const int posInfinity;
    Graph(int size)
    {
        adjacencyTable = vector<list<adjTableElem>>(size);
        distanceFromSource = vector<int>(size, posInfinity);
        priceFromSource = vector<int>(size, posInfinity);
    }
    void connect(int node1, int node2, int distance, int price)
    {
        adjacencyTable[node1].push_front(adjTableElem { node2, distance, price });
        adjacencyTable[node2].push_front(adjTableElem { node1, distance, price });
    }
    vector<int> dijkstra(int sourceID, int destID)
    {
        priceFromSource[sourceID] = 0;
        distanceFromSource[sourceID] = 0;
        vector<bool> isCollected(adjacencyTable.size(), false);
        while (!isCollected[destID]) { //普通的Dijstra算法不需要这个!isCollected[destID]
            int nodeIdToCollect = -1;
            for (int currVertexId = 0; currVertexId < isCollected.size(); currVertexId++) {
                if (!isCollected[currVertexId]) {
                    if (nodeIdToCollect == -1 || (distanceFromSource[currVertexId] < distanceFromSource[nodeIdToCollect])) {
                        nodeIdToCollect = currVertexId;
                        
                    } 
                    /*
                    else if (distanceFromSource[currVertexId] == distanceFromSource[nodeIdToCollect] && priceFromSource[currVertexId] < priceFromSource[nodeIdToCollect]) {
                        nodeIdToCollect = currVertexId;
                    }
                    */
                }
            }
            if (nodeIdToCollect == -1) {
                break;
            } else {
                isCollected[nodeIdToCollect] = true;
            }
            for (auto currEdge : adjacencyTable[nodeIdToCollect]) {
                if (!isCollected[currEdge.nodeID] && distanceFromSource[currEdge.nodeID] > distanceFromSource[nodeIdToCollect] + currEdge.distance) {
                    distanceFromSource[currEdge.nodeID] = distanceFromSource[nodeIdToCollect] + currEdge.distance;
                    priceFromSource[currEdge.nodeID] = priceFromSource[nodeIdToCollect] + currEdge.price;
                    //普通的Dijstra算法不需要下面这个else if
                } else if (!isCollected[currEdge.nodeID] && distanceFromSource[currEdge.nodeID] == distanceFromSource[nodeIdToCollect] + currEdge.distance && priceFromSource[currEdge.nodeID] > priceFromSource[nodeIdToCollect] + currEdge.price) {
                    priceFromSource[currEdge.nodeID] = priceFromSource[nodeIdToCollect] + currEdge.price;
                }
            }
        }
        return vector<int> { distanceFromSource[destID], priceFromSource[destID] };
    }
};
const int Graph::posInfinity = 2147483647;
int main()
{
    int numOfNode, numOfEdge, sourceId, destId;
    cin >> numOfNode >> numOfEdge >> sourceId >> destId;
    Graph graph { numOfNode };
    for (int i = 0; i < numOfEdge; i++) {
        int node1, node2, distance, price;
        cin >> node1 >> node2 >> distance >> price;
        graph.connect(node1, node2, distance, price);
    }
    vector<int> result = graph.dijkstra(sourceId, destId);
    cout << result[0] << " " << result[1];
}
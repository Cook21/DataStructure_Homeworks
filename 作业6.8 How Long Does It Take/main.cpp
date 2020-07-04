#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;

using NodeID=int;
class Graph {
public:
    class AdjTableElem {
    public:
        int nodeID;
        int cost;
    };
    
    vector<list<AdjTableElem>> adjacencyTable;
    static const int posInfinity;
    Graph(int size)
    {
        adjacencyTable = vector<list<AdjTableElem>>(size);
    }
    void connect(int node1, int node2, int price)
    {
        adjacencyTable[node1].push_front(AdjTableElem { node2, price });
    }
    int Prim(){
        vector<int> distanceFromTreeTo (adjacencyTable.size(),posInfinity);
        vector<NodeID> parentOf(adjacencyTable.size(),-1);
        distanceFromTreeTo[0]=0;
        while(1){
            for(int i=1;i<adjacencyTable.size())
        }
    }

};

const int Graph::posInfinity = 1000000;
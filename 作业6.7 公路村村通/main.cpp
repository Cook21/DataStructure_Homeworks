//This is a practise of Minimal Span Tree
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::vector;
class Graph {
public:
    class AdjTableElem {
    public:
        int nodeID;
        int price;
    };
    class Edge {
    public:
        int node1Id;
        int node2Id;
        int price;
        bool operator>(const Edge& edge) const
        {
            return price > edge.price;
        }
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
        adjacencyTable[node2].push_front(AdjTableElem { node1, price });
    }
    static bool greater(const Graph::Edge& edge1, const Graph::Edge& edge2)
    {
        return edge1 > edge2;
    }

    int Prim()
    {
        vector<int> priceFromTreeTo(adjacencyTable.size(), posInfinity);
        vector<int> parentOf(adjacencyTable.size(), -1);
        int startNode = 0; //初始点随便选
        priceFromTreeTo[startNode] = 0;
        for (auto i : adjacencyTable[startNode]) {
            priceFromTreeTo[i.nodeID] = i.price;
            parentOf[i.nodeID] = startNode;
        }
        while (1) {
            int minPrice = posInfinity;
            int currNode = -1;
            for (int i = 1; i < adjacencyTable.size(); i++) {
                if (priceFromTreeTo[i] != 0 && priceFromTreeTo[i] < minPrice) {
                    currNode = i;
                    minPrice = priceFromTreeTo[i];
                }
            }
            if (currNode == -1) {
                break;
            }
            priceFromTreeTo[currNode] = 0;
            for (auto i : adjacencyTable[currNode]) {
                if (i.price < priceFromTreeTo[i.nodeID]) {
                    priceFromTreeTo[i.nodeID] = i.price;
                    parentOf[i.nodeID] = currNode;
                }
            }
        }
        int totalPrice=0;
        for (int i = 0; i < adjacencyTable.size(); i++) {
            if (priceFromTreeTo[i] != 0) {
                totalPrice = -1;
                break;
            } else if (parentOf[i] != -1) {
                for(auto j: adjacencyTable[parentOf[i]]){
                    if(j.nodeID==i){
                        totalPrice+=j.price;
                    }
                }
            }
        }
        return totalPrice;;
    }
    int Kruskal()
    {
        class UnionFind {
        public:
            class Element {
            public:
                int data;
                int parent = -1;
            };
            vector<Element> table;
            int find(int a) //注意返回值是根节点数组下标
            {
                for (int i = 0; i < table.size(); i++) {
                    if (table[i].data == a) {
                        int root;
                        for (root = i; table[root].parent >= 0; root = table[root].parent)
                            ;
                        return root;
                    }
                }
                return -1;
            }
            void connect(int a, int b)
            {
                if (find(a) == -1) {
                    table.push_back(Element { a });
                }
                if (find(b) == -1) {
                    table.push_back(Element { b });
                }
                int rootOfa = find(a);
                int rootOfb = find(b);
                if (table[rootOfa].parent < table[rootOfb].parent) { //a所属集合的元素较多
                    table[rootOfa].parent += table[rootOfb].parent;
                    table[rootOfb].parent = rootOfa;
                } else {
                    table[rootOfb].parent += table[rootOfa].parent;
                    table[rootOfa].parent = rootOfb;
                }
            }
        };

        vector<Edge> uncollectedEdge {};
        vector<Edge> minSpanTree {};
        UnionFind unionfind {};
        for (int i = 1; i < adjacencyTable.size(); i++) {
            for (auto j : adjacencyTable[i]) {
                if (j.nodeID < i) {
                    uncollectedEdge.push_back(Edge { i, j.nodeID, j.price });
                }
            }
        }
        std::make_heap(uncollectedEdge.begin(), uncollectedEdge.end(), Graph::greater);
        while (minSpanTree.size() < adjacencyTable.size() - 1 && uncollectedEdge.size() > 0) {
            Edge currEdge = uncollectedEdge.front();
            std::pop_heap(uncollectedEdge.begin(), uncollectedEdge.end(), Graph::greater);
            uncollectedEdge.pop_back();
            if (unionfind.find(currEdge.node1Id) == -1 || unionfind.find(currEdge.node2Id) == -1 || unionfind.find(currEdge.node1Id) != unionfind.find(currEdge.node2Id)) {
                unionfind.connect(currEdge.node1Id, currEdge.node2Id);
                minSpanTree.push_back(currEdge);
            }
        }
        int totalPrice;
        if (minSpanTree.size() != adjacencyTable.size() - 1) {
            totalPrice = -1;
        } else {
            totalPrice = 0;
            for (auto i : minSpanTree) {
                totalPrice += i.price;
            }
        }
        return totalPrice;
    }
};

const int Graph::posInfinity = 1000000;
int main()
{
    int numOfNode, numOfCandidateEdge;
    cin >> numOfNode >> numOfCandidateEdge;
    Graph graph { numOfNode };
    for (int i = 0; i < numOfCandidateEdge; i++) {
        int node1, node2, price;
        cin >> node1 >> node2 >> price;
        graph.connect(node1 - 1, node2 - 1, price);
    }
    cout << graph.Kruskal();
    //cout << graph.Prim();
}
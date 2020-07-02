#include <cmath>
#include <deque>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::vector;
class Node {
public:
    int x;
    int y;

    bool isEscapeable(int jumpDistance, int lakeSize)
    {
        int maxCoordinate = lakeSize / 2 - jumpDistance;
        if (-maxCoordinate < x && x < maxCoordinate && -maxCoordinate < y && y < maxCoordinate) {
            return false;
        } else {
            return true;
        }
    }
    float firstJumpDistance(Node node, int radius = 0)
    {
        return sqrt(pow(node.x, 2) + pow(node.y, 2)) - radius;
    }
    bool isReachable(Node node, int jumpDistance, int raidus = 0)
    {
        int delta_x = abs(x - node.x);
        int delta_y = abs(y - node.y);
        return pow(jumpDistance + raidus, 2) >= pow(delta_x, 2) + pow(delta_y, 2);
    }
    bool operator<(const Node& node) const
    {
        return x < node.x || (x == node.x && y < node.y);
    }
    deque<int> shortestPath(int jumpDistance, int lakeSize, vector<Node>& allNode, float centerLakeRadius = 7.5) //核心代码
    {
        //-1代表湖心岛, allNode.size()+1代表岸
        vector<int> distanceTo = vector<int>(allNode.size() + 1, -1);
        vector<int> previousNodeOf = vector<int>(allNode.size() + 1, -2);
        vector<float> firstJumpDistance = vector<float>(allNode.size() + 1, -1);
        int shore = allNode.size() ;
        deque<int> nodeQueue {};
        for (int i = 0; i < allNode.size(); i++) {
            if (Node{0,0}.isReachable(allNode[i], jumpDistance, centerLakeRadius)) {
                distanceTo[i] = 1;
                previousNodeOf[i] = -1;
                firstJumpDistance[i] = Node::firstJumpDistance(allNode[i], centerLakeRadius);
                nodeQueue.push_back(i);
            }
        }
        while (!nodeQueue.empty()) {
            int currNode = nodeQueue.front();
            nodeQueue.pop_front();
            if (distanceTo[shore] == distanceTo[currNode]) {
                break;
            }
            if (allNode[currNode].isEscapeable(jumpDistance, lakeSize) && distanceTo[shore] == -1) {
                distanceTo[shore] = distanceTo[currNode] + 1;
                previousNodeOf[shore] = currNode;
            } else if (allNode[currNode].isEscapeable(jumpDistance, lakeSize) && firstJumpDistance[shore] > firstJumpDistance[currNode]) {
                previousNodeOf[shore] = currNode;
            }
            for (int i = 0; i < allNode.size(); i++) {
                if (distanceTo[i] == -1 && allNode[currNode].isReachable(allNode[i], jumpDistance)) {
                    distanceTo[i] = distanceTo[currNode] + 1;
                    previousNodeOf[i] = currNode;
                    nodeQueue.push_back(i);
                } else if (distanceTo[i] == distanceTo[currNode] + 1 && firstJumpDistance[i] > firstJumpDistance[currNode] && allNode[currNode].isReachable(allNode[i], jumpDistance)) {
                    previousNodeOf[i] = currNode;
                }
            }
        }
        deque<int> shortestPath {};
        int currNode = previousNodeOf[shore];
        while (currNode >= 0) {
            shortestPath.push_front(currNode);
            currNode = previousNodeOf[currNode];
        }
        return shortestPath;;
    }
};

int main()
{
    int numOfCrocodile;
    int jumpDistance;
    cin >> numOfCrocodile >> jumpDistance;
    vector<Node> allNodes {};
    for (int i = 0; i < numOfCrocodile; i++) {
        int x, y;
        cin >> x >> y;
        allNodes.push_back(Node { x, y });
    }
    int lakeSize = 100;
    deque<int> shortestPath = Node { 0, 0 }.shortestPath(jumpDistance, lakeSize, allNodes);
    if (shortestPath.size() == 0) {
        cout << 0;
    } else {
        cout << shortestPath.size() + 1 <<endl;
        for (int i : shortestPath) {
            cout << allNodes[i].x << " " << allNodes[i].y << endl;
        }
    }
}
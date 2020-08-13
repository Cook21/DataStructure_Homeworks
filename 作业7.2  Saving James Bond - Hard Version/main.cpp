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
    static int centerLake;
    static int nullNode;
    static int posInf;
    bool isEscapeable(int jumpDistance, int lakeSize)
    {
        int maxCoordinate = lakeSize / 2 - jumpDistance;
        if (-maxCoordinate < x && x < maxCoordinate && -maxCoordinate < y && y < maxCoordinate) {
            return false;
        } else {
            return true;
        }
    }
    float firstJumpDistance(int radius = 0)
    {
        return sqrt(pow(x, 2) + pow(y, 2)) - radius;
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
        //-1代表湖心岛,-2代表null, allNode.size()代表岸

        vector<int> distanceTo = vector<int>(allNode.size() + 1, posInf);
        vector<int> previousNodeOf = vector<int>(allNode.size() + 1, nullNode);
        vector<float> firstJumpDistance = vector<float>(allNode.size() + 1, posInf);
        int shore = allNode.size();
        deque<int> nodeQueue {};
        for (int i = 0; i < allNode.size(); i++) {
            if (Node { 0, 0 }.isReachable(allNode[i], jumpDistance, centerLakeRadius)) {
                distanceTo[i] = 1;
                previousNodeOf[i] = centerLake;
                firstJumpDistance[i] = allNode[i].firstJumpDistance(centerLakeRadius);
                nodeQueue.push_back(i);
            }
        }
        if (Node { 0, 0 }.isEscapeable(jumpDistance + centerLakeRadius, lakeSize)) {
            int i = shore;
            distanceTo[i] = 1;
            previousNodeOf[i] = centerLake;
            firstJumpDistance[i] = 0;
            nodeQueue.clear();
        }
        while (!nodeQueue.empty()) {
            int currNode = nodeQueue.front();
            nodeQueue.pop_front();
            if (distanceTo[shore] == distanceTo[currNode]) {
                break;
            }
            if (allNode[currNode].isEscapeable(jumpDistance, lakeSize) && distanceTo[shore] == posInf) {
                distanceTo[shore] = distanceTo[currNode] + 1;
                previousNodeOf[shore] = currNode;
                firstJumpDistance[shore] = firstJumpDistance[currNode];
            } else if (allNode[currNode].isEscapeable(jumpDistance, lakeSize) && firstJumpDistance[shore] > firstJumpDistance[currNode]) {
                previousNodeOf[shore] = currNode;
                firstJumpDistance[shore] = firstJumpDistance[currNode];
            }
            for (int i = 0; i < allNode.size(); i++) {
                if (distanceTo[i] == posInf && allNode[currNode].isReachable(allNode[i], jumpDistance)) {
                    distanceTo[i] = distanceTo[currNode] + 1;
                    previousNodeOf[i] = currNode;
                    firstJumpDistance[i] = firstJumpDistance[currNode];
                    nodeQueue.push_back(i);
                } else if (distanceTo[i] == distanceTo[currNode] + 1 && firstJumpDistance[i] > firstJumpDistance[currNode] && allNode[currNode].isReachable(allNode[i], jumpDistance)) {
                    previousNodeOf[i] = currNode;
                    firstJumpDistance[i] = firstJumpDistance[currNode];
                }
            }
        }
        deque<int> shortestPath {};
        int currNode = previousNodeOf[shore];
        while (currNode != nullNode) {
            shortestPath.push_front(currNode);
            if (currNode != centerLake) {
                currNode = previousNodeOf[currNode];
            } else {
                currNode = nullNode;
            }
        }
        return shortestPath;
    }
};
int Node::centerLake = -1;
int Node::nullNode = -2;
int Node::posInf = 100000;
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
        cout << shortestPath.size() << endl;
        for (int i : shortestPath) {
            if (i != Node::centerLake) {
                cout << allNodes[i].x << " " << allNodes[i].y << endl;
            }
        }
    }
}
#include <cmath>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
class Node {
public:
    int x;
    int y;
    int radius = 0;
    bool isAccessed = false;
    bool isEscapeable(int jumpDistance, int lakeSize)
    {
        int maxCoordinate = lakeSize / 2 - jumpDistance - radius;
        if (-maxCoordinate < x && x < maxCoordinate && -maxCoordinate < y && y < maxCoordinate) {
            return false;
        } else {
            return true;
        }
    }
    bool isReachable(Node node, int jumpDistance)
    {
        int delta_x = abs(x - node.x);
        int delta_y = abs(y - node.y);
        return pow(jumpDistance + radius + node.radius, 2) >= pow(delta_x, 2) + pow(delta_y, 2);
    }
    bool operator<(const Node& node) const
    {
        return x < node.x || (x == node.x && y < node.y);
    }
    bool depthFristSearch(int jumpDistance, int lakeSize, vector<Node>& allNode)
    {
        isAccessed=true;
        if (isEscapeable(jumpDistance, lakeSize)) {
            return true;
        }
        for (auto& i : allNode) {
            if (!i.isAccessed && isReachable(i, jumpDistance)) {
                if (i.depthFristSearch(jumpDistance, lakeSize, allNode)) {
                    return true;
                }
            }
        }
        return false;
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
    Node centerLake { 0, 0, 15 };
    int lakeSize = 100;
    if (centerLake.depthFristSearch(jumpDistance, lakeSize, allNodes)) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}
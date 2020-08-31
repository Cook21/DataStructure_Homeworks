#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::stable_sort;
using std::vector;
class User {
public:
    int id; //比实际id小1
    int totalScore;
    int numOfFullSocreProblem = 0;
    static bool greater(const User& u1, const User& u2);
};
bool User::greater(const User& u1, const User& u2)
{
    return u1.totalScore > u2.totalScore || (u1.totalScore == u2.totalScore && u1.numOfFullSocreProblem > u2.numOfFullSocreProblem);
}
const int maxScore = 2147483647;
int main()
{
    int numOfUser;
    int numOfProblem;
    int numOfSubmission;
    cin >> numOfUser >> numOfProblem >> numOfSubmission;
    vector<int> fullScore(numOfProblem, 0);
    vector<vector<int>> scoreTable(numOfUser, vector<int>(numOfProblem, -2));
    vector<bool> isQualified(numOfUser, false);
    for (int i = 0; i < numOfProblem; i++) {
        cin >> fullScore[i];
    }
    int user_id, problem_id, partial_score_obtained;
    for (int i = 0; i < numOfSubmission; i++) {
        cin >> user_id >> problem_id >> partial_score_obtained;
        if (partial_score_obtained > scoreTable[user_id - 1][problem_id - 1]) {
            scoreTable[user_id - 1][problem_id - 1] = partial_score_obtained;
            if (partial_score_obtained != -1) {
                isQualified[user_id - 1] = true;
            }
        }
    }
    vector<User> allQualifiedUser {};
    for (int i = 0; i < numOfUser; i++) {
        if (isQualified[i]) {
            int totalScore = 0;
            int numOfFullSocreProblem = 0;
            for (int j = 0; j < numOfProblem; j++) {
                if (scoreTable[i][j] > 0) {
                    totalScore += scoreTable[i][j];
                    if (scoreTable[i][j] == fullScore[j]) {
                        numOfFullSocreProblem++;
                    }
                }
            }
            allQualifiedUser.push_back(User { i, totalScore, numOfFullSocreProblem });
        }
    }
    stable_sort(allQualifiedUser.begin(), allQualifiedUser.end(), User::greater);
    int rank = 0;
    int count=0;
    int previousScore = maxScore;
    for (auto currUser : allQualifiedUser) {
        count++;
        if (currUser.totalScore < previousScore) {
            previousScore = currUser.totalScore;
            rank=count;
        }
        cout << rank;
        cout << " " << std::setw(5) << std::setfill('0') << currUser.id + 1;
        cout << " " << currUser.totalScore;
        for (auto currScore : scoreTable[currUser.id]) {
            if (currScore >= 0) {
                cout << " " << currScore;
            } else if (currScore == -1) {
                cout << " 0";
            } else {
                cout << " -";
            }
        }
        cout << endl;
    }
}
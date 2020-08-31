#include <iostream>
#include <string>
#include <unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

int main()
{
    int numOfInstructions;
    cin >> numOfInstructions;
    unordered_map<long long, string> passwordTable {};
    passwordTable.reserve(numOfInstructions);
    for (int i = 0; i < numOfInstructions; i++) {
        char operation;
        long long userID;
        string password;
        cin >> operation >> userID >> password;
        auto it = passwordTable.find(userID);
        if (operation == 'N') {
            if (it == passwordTable.end()) {
                passwordTable[userID] = password;
                cout << "New: OK\n";
            } else {
                cout << "ERROR: Exist\n";
            }
        } else if (operation == 'L') {
            if (it == passwordTable.end()) {
                cout << "ERROR: Not Exist\n";
            } else {
                if(it->second==password){
                    cout << "Login: OK\n";
                }else{
                    cout << "ERROR: Wrong PW\n";
                }
            }
        }
    }
}
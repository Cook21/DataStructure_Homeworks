#include <cstdlib>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
typedef short ElementType;
class Polynominal {
public:
    struct Node {
        ElementType coefficient;
        ElementType exponent;
        struct Node* next;
        struct Node* prev;
    };
    struct Node* head;
    struct Node* tail;

    Polynominal()
    {
        head = new struct Node;
        tail = new struct Node;
        head->next = tail;
        head->prev = nullptr;
        tail->next = nullptr;
        tail->prev = head;
    }
    ~Polynominal()
    {
        struct Node* curr = head;
        struct Node* next;
        while (curr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
    }
    void insert(ElementType coe, ElementType exp)
    {
        if (coe == 0) {
            return;
        }
        struct Node* curr = head;
        while (true) {
            if (exp == curr->exponent && curr != head && curr != tail) {
                curr->coefficient += coe;
                break;
            } else if ((curr->next == tail)
                || (curr == head && exp < curr->next->exponent)
                || (exp < curr->next->exponent && exp > curr->exponent)) {
                struct Node* insertedNode = new struct Node;
                insertedNode->exponent = exp;
                insertedNode->coefficient = coe;
                insertedNode->next = curr->next;
                curr->next->prev = insertedNode;
                insertedNode->prev = curr;
                curr->next = insertedNode;
                curr = insertedNode;
                break;
            } else {
                curr = curr->next;
            }
        }
        if (curr->coefficient == 0) {
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            delete curr;
        }
        return;
    }
    void print(int direction)
    {
        struct Node* curr;
        if (head->next == tail) {
            cout << "0 0" << endl;
            return;
        }
        if (direction > 0) { //按指数从小到大打印
            curr = head->next;
            while (curr != tail) {
                cout << curr->coefficient << " " << curr->exponent;
                curr = curr->next;
                if (curr != tail) {
                    cout << " ";
                } else {
                    cout << endl;
                }
            }
        } else if (direction < 0) { //按指数从大到小打印
            curr = tail->prev;
            while (curr != head) {
                cout << curr->coefficient << " " << curr->exponent;
                curr = curr->prev;
                if (curr != head) {
                    cout << " ";
                } else {
                    cout << endl;
                }
            }
        }
        return;
    }
    Polynominal operator+(Polynominal& p)
    {
        Polynominal newPoly {};
        struct Node* curr = p.head->next;
        while (curr != p.tail) {
            newPoly.insert(curr->coefficient, curr->exponent);
            curr = curr->next;
        }
        curr = this->head->next;
        while (curr != this->tail) {
            newPoly.insert(curr->coefficient, curr->exponent);
            curr = curr->next;
        }
        return newPoly;
    }
    Polynominal operator*(Polynominal& p)
    {
        Polynominal newPoly {};
        struct Node* curr1 = p.head->next;
        while (curr1 != p.tail) {
            struct Node* curr2 = this->head->next;
            while (curr2 != this->tail) {
                newPoly.insert(curr1->coefficient * curr2->coefficient, curr1->exponent + curr2->exponent);
                curr2 = curr2->next;
            }
            curr1 = curr1->next;
        }
        return newPoly;
    }
};
int main()
{
    int n, coe, exp;
    Polynominal p1 {};
    Polynominal p2 {};
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> coe >> exp;
        p1.insert(coe, exp);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> coe >> exp;
        p2.insert(coe, exp);
    }
    (p1 * p2).print(-1);
    (p1 + p2).print(-1);
    return 0;
}

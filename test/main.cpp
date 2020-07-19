#include <iostream>
using std::cout;
using std::endl;
class C {
    int x = 0;
public:
    void show(int x)
    {
        cout << x;
    }
    void test(C* c)
    {
        cout << c->x;
    }
};
int main()
{
    C c1;
    C c2 ;
	c1.test(&c2);
	cout << (&c2)->x;
    return (0);
}
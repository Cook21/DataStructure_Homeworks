#include <iostream>
using std::cout;using std::endl;
class C{
	int x{0};
public:
	C(int x_):x{x_}{
		std::cout << "C(" << x_ << ")" << std::endl;
	}
	C(double x_):C(static_cast<int>(x_)){
		std::cout << "C(" << x_ << ")" << std::endl;
	}
	C():C(3.8){
		std::cout << "C()" << std::endl;
	}
};
int main() {
	C c1, c2{2.2}, c3{1};
	return (0);
}
#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class popSequence {
private:
    struct stack {
        short maxSize;
        short top = -1; //-1表示栈空
        short s[1000] = { 0 };
        short output[1000] = { 0 };
    };
    int count = 0; //统计有多少种可能输出
    short maxSize; //the maximum capacity of the stack
    short endNumber; //the length of push sequence
    short K; //the number of pop sequences to be checked
    short** a;
    bool* b;

public:
    popSequence(short M_, short N_, short K_)
    {
        maxSize = M_;
        endNumber = N_;
        K = K_;
        this->a = new short*[K];
        this->b = new bool[K];
        for (short i = 0; i < K; i++) {
            a[i] = new short[endNumber];
            for (short j = 0; j < endNumber; j++) {
                cin >> a[i][j];
            }
        }
        for (short i = 0; i < K; i++) {
            b[i] = false;
        }
    }
    void show()
    {
        struct stack s;
        s.maxSize = maxSize;
        push(s, 1);
        for (short i = 0; i < K; i++) {
            if (b[i] == true) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
        //cout << count << endl;
    }
    void push(struct stack stack, short nextNumber)
    {
        stack.s[++stack.top] = nextNumber++;
        if (nextNumber <= endNumber && stack.top != stack.maxSize - 1) { //栈不满且元素没用完则可以push
            push(stack, nextNumber);
        }
        if (stack.top != -1) { //栈不空则可以pop
            pop(stack, nextNumber);
        }
    }
    void pop(struct stack stack, short nextNumber)
    {

        stack.output[nextNumber - stack.top - 2] = stack.s[stack.top];
        stack.top--;
        if (nextNumber <= endNumber && stack.top != stack.maxSize - 1) { //栈不满且元素没用完则可以push
            push(stack, nextNumber);
        }
        if (stack.top != -1) { //栈不空则可以pop
            pop(stack, nextNumber);
        } else {
            if (nextNumber > endNumber) { //栈空且元素用完, 则可以开始打印
                /*
                for (short j = 0; j < endNumber; j++) {
                    cout << stack.output[j] << " ";
                }
                cout << endl;
                */
                for (short i = 0; i < K; i++) {
                    bool isMatch = true;
                    for (short j = 0; j < endNumber; j++) {
                        if (a[i][j] != stack.output[j]) {
                            isMatch = false;
                            break;
                        }
                    }
                    if (isMatch) {
                        b[i] = true;
                    }
                }
                count++;
            }
        }
        return;
    }
};
int main()
{
    short M; //the maximum capacity of the stack
    short N; //the length of push sequence
    short K; //the number of pop sequences to be checked
    cin >> M >> N >> K;
    popSequence p { M, N, K };
    p.show();
}
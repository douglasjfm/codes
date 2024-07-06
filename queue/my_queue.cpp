#include <iostream>
#include <string>
#include <stack>

class MyQueue {
    private:
        void linkStacks(){
            while(!stack_newest_on_top.empty()){
                int i = stack_newest_on_top.top();
                stack_oldest_on_top.push(i);
                stack_newest_on_top.pop();
            }
        }
    public:
        std::stack<int> stack_newest_on_top, stack_oldest_on_top;   
        void push(int x) {
            stack_newest_on_top.push(x);
        }

        void pop() {
            if (!stack_oldest_on_top.empty()) {
                stack_oldest_on_top.pop();
                return;
            }
            else {
                linkStacks();
                if (!stack_oldest_on_top.empty()) stack_oldest_on_top.pop();
            }
        }

        int front() {
            if (!stack_oldest_on_top.empty()) {
                return stack_oldest_on_top.top();
            } else {
                linkStacks();
                if (!stack_oldest_on_top.empty()) return stack_oldest_on_top.top();
            }
            return 0;
        }

        void print() {
            std::cout << front() << std::endl;
        }
};

int main(){
    MyQueue q;
    q.push(15);
    q.push(17);
    q.print();// print 15
    q.push(25);
    q.pop(); //remove 15
    q.print(); // print 17
    q.pop();//remove 17
    q.print();//25
    return 0;

}
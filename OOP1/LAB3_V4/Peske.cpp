#include <iostream>
using namespace std;

class A {
    friend int f(int& v, const A& a) { return ++v / 2.0; }
};
//int main() {
//    int a = 0;
//    decltype(f(++a, A())) b = f(a, A());
//    cout << b;
//
//    return 0;
//}
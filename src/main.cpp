#include "vec.hpp"
#include <iostream>

// using namespace mathlib;

using std::cout;
using std::endl;

using vec2i = vec2<int>;

int main(){
    vec2i a{1,2};
    vec2i b{3,4};

    cout << a << endl;
    cout << b << endl;

    cout << a.x << endl;
    cout << a.y << endl;

    cout << a.yx[0] << ", " << a.yx[1] << endl;

    cout << a.yyx[0] << ", " << a.yyx[1] << ", " << a.yyx[2] << endl;

    cout << a.yyy[0] << ", " << a.yyy[1] << ", " << a.yyy[2] << endl;

    cout << a.xxx[0] << ", " << a.xxx[1] << ", " << a.xxx[2] << endl;

    cout << b.yx[0] << ", " << b.yx[1] << endl;

    a = b.yx; //okay a = 4,3

    a.yx = b.yx; //okay a = 3,4

    a.yx = b.xxx; //编译错误

    cout << a << endl;

    return 0;
}
#include <iostream>

template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T1, typename T2>
T1 max(T1 a, T2 b) {
    return (a > b) ? a : b;
}

int main() {
    int a = 5, b = 10;
    double x = 5.5, y = 10.2;

    std::cout << "Max of " << a << " and " << b << " is: " << max(a, b) << std::endl;
    std::cout << "Max of " << x << " and " << y << " is: " << max(x, y) << std::endl;

    return 0;   
}
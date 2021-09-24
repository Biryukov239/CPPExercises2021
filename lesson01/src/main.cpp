#include <iostream>
#include <vector>

#include "simple_sum.h"
#include "some_math.h"

int main() {
    std::cout << "Hello World!" << std::endl;

    int a = 10;
    std::cout << "Please enter b=";
    int b;
    std::cin >> b;
    std::cout << "b=" << b << std::endl;

    int res = sum(a, b);

    std::cout << "a+b=" << a << "+" << b << "=" << res << std::endl;

    std::cout << "fib(b)=" << fibbonachiFast(b);

    std::vector<double> values;
    std::cout << "values size: " << values.size() << std::endl;
    values.push_back(10);
    std::cout << "values size after push_back: " << values.size() << std::endl;
    values.push_back(20);
    values.push_back(35);
    values.push_back(4);
    std::cout << "values size after more push_back: " << values.size() << std::endl;

    for (int i; i < values.size(); ++i)
    {
        std::cout << values[i] << " ";
    }

    std::vector<int> v;

    while (true)
    {
        int t;
        std::cin >> t;
        if (t == 0)
            break;
        v.push_back(t);
    }

    return 0;
}


#include "zip.hpp"

#include <vector>
#include <iostream>

int main() {
    std::vector<int> data1 = {1, 2, 3};
    std::vector<int> data2 = {2, 3, 4};

    apio::zip([](int & e1, int & e2) {
        std::cout << e1 << ", " << e2 << std::endl;
    }, data1.begin(), data1.end(), data2.begin());

    std::vector<int> zipped = apio::zip(std::plus<int>(), data1.begin(), data1.end(), data2.begin());

    for(const int & e : zipped)
        std::cout << e << std::endl;
}

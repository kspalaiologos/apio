
#include <apio/all.hpp>
#include <apio/zip.hpp>

#include <vector>
#include <iostream>

int main() {
    /// Example data for tests.
    std::vector<int> data1 = {1, 2, 3};
    std::vector<int> data2 = {2, 3, 4};

    /// The following two are equivalent:
    std::vector<int> result;
    apio::zip([&result](int & e1, int & e2) {
        result.push_back(e1 + e2);
    }, data1.begin(), data1.end(), data2.begin());

    std::vector<int> zipped = apio::zip(std::plus<int>(), data1.begin(), data1.end(), data2.begin());
    std::vector<bool> equal = apio::zip([](int & e1, int & e2) {
            return e1 == e2;
        }, result.begin(), result.end(), zipped.begin());
    
    return apio::all(std::identity(), equal.begin(), equal.end()) ? 0 : 1;
}

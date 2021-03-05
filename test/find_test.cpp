
#include <apio/find.hpp>
#include <apio/zip.hpp>
#include <apio/all.hpp>
#include <vector>
#include <numeric>
#include <functional>

int main(void) {
    std::vector<int> data(10);
    std::iota(data.begin(), data.end(), 0);
    std::vector<int> stuff2;
    std::vector<int> stuff = apio::find_all(data.begin(), data.end(),
        [](const int & e) { return e % 2 == 0; },
        [](const std::vector<int>::iterator & e) { return *e + 1; });
    apio::find_all(data.begin(), data.end(),
        [](const int & e) { return e % 2 == 0; },
        [&stuff2](const std::vector<int>::iterator & e) { stuff2.push_back(*e + 1); });
    std::vector<bool> equal = apio::zip(std::equal_to<int>(), stuff.begin(), stuff.end(), stuff2.begin());
    return apio::all(std::identity(), equal.begin(), equal.end()) ? 0 : 1;
}

//
// CTR58-CPP. Predicate function objects should not be mutable
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

namespace {

class MutablePredicate : public std::unary_function<int, bool>
{
    size_t timesCalled;

public:
    MutablePredicate() : timesCalled(0) {}

    bool operator()(const int& /*unused*/) { return ++timesCalled == 3; }
};

template <typename Iter> void print_container(Iter b, Iter e)
{
    std::cout << "Contains: ";
    std::copy(b, e, std::ostream_iterator<decltype(*b)>(std::cout, ", "));
    std::cout << std::endl;
}

int foo()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_container(v.begin(), v.end());

    v.erase(std::remove_if(v.begin(), v.end(), MutablePredicate()), v.end());
    print_container(v.begin(), v.end());

    return v.size();
}

int bar()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_container(v.begin(), v.end());

    int timesCalled = 0;
    v.erase(
        std::remove_if(v.begin(), v.end(),
                       [timesCalled](const int& /*unused*/) mutable { return ++timesCalled == 3; }),
        v.end());
    print_container(v.begin(), v.end());

    return v.size();
}

} // namespace

int main()
{
    if (bar() != 9) {
        return 1;
    }

    return static_cast<int>(9 != foo());
}

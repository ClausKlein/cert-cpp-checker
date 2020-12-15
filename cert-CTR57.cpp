//
// CTR57-CPP. Provide a valid ordering predicate
//

#include <functional>
#include <iostream>
#include <set>

namespace {

int bad()
{
    int result = 0;
    std::set<int, std::less_equal<int>> s{5, 10, 20};

    for (auto r = s.equal_range(10); r.first != r.second; ++r.first) {
        int i = *r.first;
        result += i;
        std::cout << i << ", ";
        std::cout << std::endl;
    }

    return result;
}

// ===========================

class S
{
    int i, j;

public:
    S(int i, int j) : i(i), j(j) {}

    friend bool operator<(const S& lhs, const S& rhs) { return lhs.i < rhs.i && lhs.j < rhs.j; }

    friend std::ostream& operator<<(std::ostream& os, const S& o)
    {
        os << "i: " << o.i << ", j: " << o.j;
        return os;
    }
};

void foo()
{
    std::set<S> t{S(1, 1), S(1, 2), S(2, 1)};
    if (t.size() != 2) {
        std::cout << "wrong! size() == " << t.size() << std::endl;
    }
    for (auto v : t) {
        std::cout << v << std::endl;
    }
}

} // namespace

int main()
{
    std::set<int> s{5, 10, 20};
    for (auto r = s.equal_range(10); r.first != r.second; ++r.first) {
        std::cout << *r.first << ", ";
        std::cout << std::endl;
    }

    foo();
    return static_cast<int>(0 == bad());
}

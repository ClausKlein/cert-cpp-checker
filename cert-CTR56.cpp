//
// CTR56-CPP. Do not use pointer arithmetic on polymorphic objects
//

#include <array>
#include <iostream>

namespace {

constexpr size_t SIZE = 5;
size_t globI{};
double globD{};

struct S
{
    int i;

    S() : i(globI++) {}
};

struct T : S
{
    double d;

    T() : d(globD++) {}
};

void foo(const S* someSes, std::size_t count)
{
    for (const S* end = someSes + count; someSes != end; ++someSes) { // undefined behavior
        std::cout << someSes->i << ", ";
    }
    std::cout << std::endl;
}

void bar(const S* someSes, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i) { // undefined behavior
        std::cout << someSes[i].i << ", ";
    }
    std::cout << std::endl;
}

void bad()
{
    T test[SIZE];
    foo(test, SIZE);
    bar(test, SIZE);
}

void fun(const S* const* someSes, std::size_t count)
{
    for (const S* const* end = someSes + count; someSes != end; ++someSes) {
        std::cout << (*someSes)->i << ", ";
    }
    std::cout << std::endl;
}

// ========================

void notGood()
{
    S* test[SIZE] = {new T, new T, new T, new T, new T};
    fun(test, SIZE);

    for (auto* v : test) {
        delete v;
    }

    bad();
}

template <typename Iter> void better(Iter i, Iter e)
{
    for (; i != e; ++i) {
        std::cout << (*i)->i << ", ";
    }
    std::cout << std::endl;
}

} // namespace

int main()
{
    std::array<S*, SIZE> test{new T, new T, new T, new T, new T};
    better(test.cbegin(), test.cend());

    for (auto* v : test) {
        delete v;
    }

    notGood();

    return static_cast<int>(globI < (4 * SIZE));
}

//
// MEM52-CPP. Detect and handle memory allocation errors
//

#include <array>
#include <cassert>
#include <cstring>
#include <memory>

namespace {
// The function is marked as noexcept, so the caller assumes this function does not throw any
// exceptions. Because ::operator new[](std::size_t) can throw an exception if the allocation fails, it
// could lead to abnormal termination of the program.
void foo(const int* array, std::size_t size) noexcept
{
    // FIXME: int* copy = new (std::nothrow) int[size];
    int* copy = new int[size]; // diagnostic required

    // TODO: if (copy == nullptr) return;

    std::memcpy(copy, array, size * sizeof(*copy));
    // ...
    delete[] copy;
}

struct A
{
    int a{40};
    /* ... */
};
struct B
{
    int b{2};
    /* ... */
};

int bar(A* a, B* b)
{
    int c = a->a + b->b;
    // ...
    delete a;
    delete b;

    return c;
}

// In this noncompliant code example, two memory allocations are performed within the same expression.
// Because the memory allocations are passed as arguments to a function call, an exception thrown as a
// result of one of the calls to new could result in a memory leak.
int bad() { return bar(new A, new B); } // diagnostic required

int heavy(std::unique_ptr<A> a, std::unique_ptr<B> b) { return a->a + b->b; }

int notGood() { return heavy(std::make_unique<A>(), std::make_unique<B>()); }

int good(A& a, B& b) { return a.a + b.b; }

int perfect()
{
    A a;
    B b;

    return good(a, b);
}
} // namespace

int main()
{
    constexpr std::array<int, 3> data{1, 2, 3};
    foo(data.data(), data.size());

    int value = bad();
    int i = notGood();
    if (value != i) {
        return -1;
    }

    if (perfect() != 42) {
        return -1;
    }
}

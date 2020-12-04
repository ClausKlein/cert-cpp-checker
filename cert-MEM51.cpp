#include <cstdlib>
#include <iostream>
#include <new>

namespace {

struct S
{
    S() { std::cout << "S::S()" << std::endl; }
    ~S() { std::cout << "S::~S()" << std::endl; }
};

void foo()
{
    alignas(struct S) char space[sizeof(struct S)];
    S* s1 = new (&space) S;

    // ...

    delete s1; // diagnostic required
}

void bar()
{
    int* array = new int[10];
    // ...
    delete array; // diagnostic required
}

int bad()
{
    int *i1;
    int *i2; // diagnostic required
    try {
        i1 = new int;
        i2 = new int;
    } catch (std::bad_alloc&) {
        delete i1;
        delete i2; // undefined behavior!
    }

    return *i1 * *i2; // diagnostic required
}

struct P
{
    const char* text{"test text"};
};

class C
{
    P* p;

public:
    C(P* p) : p(p) {}
    ~C() { delete p; } // diagnostic required

    void f() { std::cout << p->text << std::endl; }
};

void g(C c) { c.f(); }

void chaos()
{
    P* p = new P;
    C c(p);
    g(c);
}

void fun()
{
    int* i = static_cast<int*>(std::malloc(sizeof(int)));
    // ...
    delete i; // diagnostic required
}
} // namespace

int main()
{
    fun();
    foo();
    bar();
    chaos();

    return bad();
}

/* https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM51-CPP.+Properly+deallocate+dynamically+allocated+resources
 *
$ clang++ -std=c++17 -Wextra cert-MEM51.cpp
cert-MEM51.cpp:26:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'?  [-Wmismatched-new-delete]
  delete array;
  ^
        []
cert-MEM51.cpp:21:18: note: allocated with 'new[]' here
  int *array = new int[10];
               ^
1 warning generated.

cert-MEM51.cpp:16:5: warning: Argument to 'delete' is the address of the local variable 'space', which is not memory allocated by 'new' [clang-analyzer-cplusplus.NewDelete]

 */


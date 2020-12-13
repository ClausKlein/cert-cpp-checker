//
// EXP53-CPP. Do not read uninitialized memory
//

#include <iostream>

namespace {

void foo()
{
    int i;
    std::cout << i << std::endl;
}

void bar()
{
    int* i = new int;
    std::cout << i << ", " << *i << std::endl;
    delete i;
}

class S
{
    int c;

public:
    int f(int i) const { return i + c; }
};

void bad()
{
    S s;
    int i = s.f(10);
    std::cout << i << std::endl;
}

} // namespace

int main()
{
    foo();
    bar();
    bad();
}

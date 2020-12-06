//
// MEM53-CPP. Explicitly construct and destruct objects when manually managing object lifetime
//

#include <cstdlib>
#include <iostream>

namespace {

struct S
{
    int s;
    explicit S(int i) : s(i) {}

    // warning: The expression is an uninitialized value. The computed value will also be garbage
    // [clang-analyzer-core.uninitialized.Assign]
    int foo() { return ++s; } // diagnostic required
};

} // namespace

int main()
{
    int result{};

    for (int i = 0; i < 7; ++i) {
        S* s = static_cast<S*>(std::malloc(sizeof(S))); // diagnostic required
        result = s->foo();
        std::cout << result << std::endl;
        std::free(s); // diagnostic required
    }

    return result;
}

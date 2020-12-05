//
// MEM53-CPP. Explicitly construct and destruct objects when manually managing object lifetime
//

#include <cstdlib>

struct S
{
    int s;
    S(int i) : s(i)
    { /* non default */
    }

    // warning: The expression is an uninitialized value. The computed value will also be garbage
    // [clang-analyzer-core.uninitialized.Assign]
    int f() { return ++s; } // diagnostic required
};

int main()
{
    S* s = static_cast<S*>(std::malloc(sizeof(S)));
    int result = s->f();
    std::free(s);

    return result;
}

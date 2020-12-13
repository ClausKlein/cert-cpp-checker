//
// DCL50-CPP. Do not define a C-style variadic function
//

#include <cstdarg>
#include <iostream>

namespace {

int add(int first, int second, ...)
{
    int r = first + second;
    va_list va;
    va_start(va, second);
    while (int v = va_arg(va, int)) {
        r += v;
    }
    va_end(va);
    return r;
}

} // namespace

int main()
{
    for (int n = 0; n < 7; ++n) {
        int i = add(1, 1, 2, 3, 5, n); // diagnostic required
        std::cout << i << std::endl;
        if (i > 19) {
            throw i;
        }
    }
}

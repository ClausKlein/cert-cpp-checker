// safeComparison.cpp

#include <iostream>
#include <utility>

void unsafeComparison()
{

    std::cout << std::endl;

    std::cout << std::boolalpha;

    int x = -3;         // (1)
    unsigned int y = 7; // (2)

    std::cout << "-3 < 7:  " << (x < y) << std::endl;
    std::cout << "-3 <= 7: " << (x <= y) << std::endl;
    std::cout << "-3 > 7:  " << (x > y) << std::endl;
    std::cout << "-3 => 7: " << (x >= y) << std::endl;

    std::cout << std::endl;
}

void safeComparison()
{
#if __cpp_lib_integer_comparison_functions

    std::cout << std::endl;

    std::cout << std::boolalpha;

    int x = -3;
    unsigned int y = 7;

    std::cout << "3 == 7:  " << std::cmp_equal(x, y) << std::endl;
    std::cout << "3 != 7:  " << std::cmp_not_equal(x, y) << std::endl;
    std::cout << "-3 < 7:  " << std::cmp_less(x, y) << std::endl;
    std::cout << "-3 <= 7: " << std::cmp_less_equal(x, y) << std::endl;
    std::cout << "-3 > 7:  " << std::cmp_greater(x, y) << std::endl;
    std::cout << "-3 => 7: " << std::cmp_greater_equal(x, y) << std::endl;

    std::cout << std::endl;
#endif
}

int main()
{
    unsafeComparison();
    safeComparison();
}

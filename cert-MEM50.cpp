#include <cstring>
#include <iostream>
#include <memory>
#include <new>
#include <string>

std::string str_func() { return std::string("test text"); }
void display_string(const char* s)
{
    std::cout << s << std::endl;
}

void undefined()
{
    const char* str = str_func().c_str(); // diagnostic required
    display_string(str); /* Undefined behavior */
}


struct S
{
    int i{};
    int f() { return ++i; }
};

void foo() noexcept(false)
{
    S* s = new S;
    // ...
    delete s;
    // ...
    auto i = s->f(); // diagnostic required
    std::cout << i << std::endl;
}


void bar()
{
    int* array = new int[10]{};
    // ...
    delete[] array;

    auto i = (*array)++; // diagnostic required
    std::cout << i << std::endl;
}

void tests()
{
    foo();
    bar();
    undefined();
}


void bad() noexcept(false)
{
    char* ptr = static_cast<char*>(::operator new(0));
    *ptr = 0;
    // ...
    ::operator delete(ptr); /* Undefined behavior */
    display_string(ptr); /* Undefined behavior */
}


int main(int argc, const char* argv[])
{
    bad();
    tests();

    const char* s = "";
    if (argc > 1) {
        enum
        {
            BufferSize = 32
        };
        try {
            std::unique_ptr<char[]> buff(new char[BufferSize]);
            std::memset(buff.get(), 0, BufferSize);
            // ...
            s = std::strncpy(buff.get(), argv[1], BufferSize - 1);
        } catch (std::bad_alloc&) {
            // Handle error
        }
    }

    std::cout << s << std::endl; // diagnostic required
}

/*
 * https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM50-CPP.+Do+not+access+freed+memory
 *
 * cert-MEM50.cpp:15:23: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
    const char* str = str_func().c_str();
                      ^~~~~~~~~~
1 warning generated.

builddriver executing: 'run-clang-tidy cert-MEM50.cpp'
Compilation SUCCEED in 3.240367 seconds
Number of warnings: 6
WarningErrorEntry(path='cert-MEM50.cpp', lineno='16', severity='warning', message='Inner pointer of container used after re/deallocation [clang-analyzer-cplusplus.InnerPointer]', column='5')
WarningErrorEntry(path='cert-MEM50.cpp', lineno='32', severity='warning', message='Use of memory after it is freed [clang-analyzer-cplusplus.NewDelete]', column='14')
WarningErrorEntry(path='cert-MEM50.cpp', lineno='43', severity='warning', message='Use of memory after it is freed [clang-analyzer-cplusplus.NewDelete]', column='14')
WarningErrorEntry(path='cert-MEM50.cpp', lineno='57', severity='warning', message='do not declare variables of type va_list; use variadic templates instead [cppcoreguidelines-pro-type-vararg]', column='5')
WarningErrorEntry(path='cert-MEM50.cpp', lineno='58', severity='warning', message='Use of zero-allocated memory [clang-analyzer-cplusplus.NewDelete]', column='10')
WarningErrorEntry(path='cert-MEM50.cpp', lineno='80', severity='warning', message='do not use pointer arithmetic [cppcoreguidelines-pro-bounds-pointer-arithmetic]', column='42')
 */

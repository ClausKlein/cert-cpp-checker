#include <array>
#include <cstddef>
#include <iostream>
#include <new>

// MEM54-CPP. Provide placement new with properly aligned pointers to sufficient storage capacity

namespace {
// warning: Storage provided to placement new is only 2 bytes, whereas the allocated type requires 8
// bytes [clang-analyzer-cplusplus.PlacementNew]
void foo()
{
    short s{};
    long* lp = ::new (&s) long; // diagnostic required
    *lp = -1;
}

// Ensures that the long is constructed into a buffer of sufficient size, However:
// warning: Storage type is aligned to 1 bytes but allocated type is aligned to 8 bytes
// [clang-analyzer-cplusplus.PlacementNew]
void bar()
{
    unsigned char c{}; // Used elsewhere in the function
    unsigned char buffer[sizeof(long)];
    long* lp = ::new (buffer) long; // diagnostic required

    // ...
    c = 0x42;
    *lp = c;
}

struct S
{
    char* data{};

    S() : data(new char[16]) { std::cout << "S::S()" << std::endl; }
    ~S()
    {
        delete[] data;
        data = nullptr;
        std::cout << "S::~S()" << std::endl;
    }
};

constexpr size_t N = 3;

// This example attempts to allocate sufficient storage of the
// appropriate alignment for the array of objects of S.  However:
// warning: Storage provided to placement new is only 32 bytes, whereas the allocated array type
// requires more space for internal needs [clang-analyzer-cplusplus.PlacementNew]
void cookie()
{
    alignas(S) unsigned char buffer[sizeof(S) * N];
    S* sp = ::new (buffer) S[N];

    // ...
    // Destroy elements of the array.
    for (size_t i = 0; i != N; ++i) {
        sp[i].~S(); // diagnostic required
    }
}
} // namespace

#if 1
// The amount of overhead required by array new expressions is unspecified but ideally would be
// documented by quality implementations.
#    if defined(__clang__) || defined(__GNUG__)
constexpr size_t overhead = sizeof(size_t);
#    else
constexpr size_t overhead = 0;
static_assert(overhead, "you need to determine the size of your implementation's array overhead");
#    endif

void* operator new[](size_t n, void* p, size_t bufsize)
{
    if (n > bufsize) {
        throw std::bad_array_new_length();
    }
    return p;
}

static void good()
{
    alignas(S) unsigned char buffer[sizeof(S) * N + overhead];
    S* sp = ::new (buffer, sizeof(buffer)) S[N];

    // ...
    // Destroy elements of the array.
    for (size_t i = 0; i != N; ++i) {
        sp[i].~S();
    }
}
#endif

static void perfect()
{
    std::array<S, N> buffer{};

    // ...
    // Destroy elements of the array.
    for (auto& i : buffer) {
        i.~S();
    } // NOTE: not realy needed! CK
    std::cout << "buffer contains stil " << buffer.size() << " elements!" << std::endl;
}

int main()
{
    foo();
    bar();
    cookie();
    good();
    perfect();
}

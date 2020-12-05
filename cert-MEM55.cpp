//
// MEM55-CPP. Honor replacement dynamic storage management requirements
//

#include <cstdlib>
#include <new>

// warning: do not manage memory manually; use RAII [cppcoreguidelines-no-malloc]
void* operator new(std::size_t size) { return std::malloc(size); }

void operator delete(void* ptr) noexcept { std::free(ptr); }
void operator delete(void* ptr, std::size_t) noexcept; // Defined elsewhere

int main()
{
    int* p = new int;   // diagnositc requiered
    // ...
    delete p;
    // warning: Potential leak of memory pointed to by 'p' [clang-analyzer-unix.Malloc]
}

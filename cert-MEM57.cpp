//
// MEM57-CPP. Avoid using default operator new for over-aligned types
//

#include <cstdlib>
#include <cstring>
#include <new>

#undef USE_COMPIENT_SOLUTION

namespace {

// In particular, it is unsafe to use the storage for an object of a type with a stricter alignment
// requirement—an over-aligned type.
struct alignas(32) Vector
{
    char elems[32];

#ifdef USE_COMPIENT_SOLUTION
    static void* operator new(size_t nbytes)
    {
        if (void* p = std::aligned_alloc(alignof(Vector), nbytes)) {
            return p;
        }
        throw std::bad_alloc();
    }
    static void operator delete(void* p) { free(p); }
    // warning: do not manage memory manually; use RAII [cppcoreguidelines-no-malloc,hicpp-no-malloc]
#endif
};

Vector* createVector()
{
    auto* pv = new Vector; // undefined behavior
    memset(pv->elems, 0, sizeof(pv->elems));
    return pv;
}

} // namespace

int main()
{
    auto* pv = createVector();
    // ...
    delete pv;
}

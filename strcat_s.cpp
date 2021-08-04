#define __STDC_WANT_LIB_EXT1__ 1
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {

#if !(defined(__APPLE__) || defined(__BSD__))
// Like snprintf(3), the strlcpy() and strlcat() functions return the
// total length of the string they tried to create.
size_t strlcpy(char* dst, const char* src, size_t capacity)
{
    assert(dst != nullptr);
    int len = snprintf(dst, capacity, "%s", src);
    printf("dst = \"%s\", len = %d, capacity = %zu\n", dst, len, capacity);

    if (len >= 0 && (size_t)len >= capacity) {
        puts("Warning: truncated str at strlcpy()!");
    }

    return len;
}

// If the return value is >= dstsize, the output string has been
// truncated.  It is the caller's responsibility to handle this
size_t strlcat(char* dst, const char* src, size_t capacity)
{
    assert(dst != nullptr);
    size_t actual_used = strlen(dst);
    assert(actual_used < capacity);

    if (capacity > (actual_used + 1)) {
        return strlcpy(dst + actual_used, src, capacity - actual_used);
    }

    return actual_used + strlen(src); // NOTE: total_len
}
#endif

} // namespace

int main(void)
{
    char dst[15 + 2 * 6 + 1] = "Hello ";
    char src[6 + 1] = "World!";
    constexpr size_t capacity = sizeof(dst); // NOTE: 28

    size_t total_len = strlcat(dst, src, capacity);
    total_len = strlcat(dst, " .............#", capacity);
    printf("dst = \"%s\", len = %zu, capacity = %zu\n", dst, total_len, capacity);
    if (total_len >= capacity) {
        puts("Warning: truncated string!");
    }
    // XXX else
    {
        total_len = strlcat(dst, " Goodbye World!", capacity);
        printf("dst = \"%s\", len = %zu, capacity = %zu\n", dst, total_len, capacity);
        assert(total_len == 42);
    }
    // XXX puts(dst);

    total_len = strlcpy(dst, "Hello World! .............#1234567890", capacity);
    printf("dst = \"%s\", len = %zu, capacity = %zu\n", dst, total_len, capacity);
    assert(total_len == 37);

#if defined(__STDC_LIB_EXT1__) || defined(_WIN32)
    set_constraint_handler_s(ignore_handler_s);

    int r = strcpy_s(dst, capacity, src);
    printf("dst = \"%s\", r = %d\n", dst, r);
    r = strcpy_s(dst, capacity, "Take even more tests.");
    printf("dst = \"%s\", r = %d\n", dst, r);

    int err = strcat_s(dst, capacity, " .............. ");
    printf("dst = \"%s\", err = %d\n", dst, err);
    err = strcat_s(dst, capacity, " and this is too much");
    printf("dst = \"%s\", err = %d\n", dst, err);
#endif
}

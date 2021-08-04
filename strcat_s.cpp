#define __STDC_WANT_LIB_EXT1__ 1
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

namespace {

#if !(defined(__APPLE__) || defined(__BSD__))
// If the return value is >= dstsize, the output string has been
// truncated.  It is the caller's responsibility to handle this
size_t strlcpy(char* dst, const char* src, size_t capacity)
{
    int len = snprintf(dst, capacity, "%s", src);
    printf("dst = \"%s\", len = %d, capacity = %zu\n", dst, len, capacity);

    if(len >= 0 && (size_t)len >= capacity) {
        puts("Warning: truncated str at strlcpy()!");
    }

    return len;
}

size_t strlcat(char* dst, const char* src, size_t capacity)
{
    size_t actual_used = strlen(dst);
    if (capacity > (actual_used + 1)) {
        return strlcpy(dst + actual_used, src, capacity - actual_used);
    }

    return actual_used;
}
#endif
}

int main(void)
{
    char dst[15 + 2 * 6 + 1] = "Hello ";
    char src[6 + 1] = "World!";
    constexpr size_t capacity = sizeof(dst);

#if 1 // defined(__APPLE__) || defined(__BSD__)
    size_t actual_len = strlcat(dst, src, capacity);
    actual_len = strlcat(dst, " .............#", capacity);
    if (actual_len >= capacity) {
        puts("Warning: truncated string!");
    }
    //XXX else
    {
        actual_len = strlcat(dst, " Goodbye World!", capacity);
        printf("dst = \"%s\", len = %zu, capacity = %zu\n", dst, actual_len, capacity);
        assert(actual_len < capacity);
    }
    //XXX puts(dst);
#endif

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

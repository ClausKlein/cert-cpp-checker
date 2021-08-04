#define __STDC_WANT_LIB_EXT1__ 1
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(void)
{
    char dest[27] = "Hello ";
    char src[] = "World!";
    constexpr size_t capacity = sizeof(dest);

#if defined(__APPLE__) || defined(__BSD__)
    size_t actual_len = strlcat(dest, src, capacity);
    actual_len = strlcat(dest, " ..............", capacity);
    if (actual_len >= capacity) {
        puts("Warning: truncated string!");
    } else {
        strlcat(dest, " Goodbye World!", capacity);
    }
    puts(dest);
#endif

#if defined(__STDC_LIB_EXT1__) || defined(_WIN32)
    set_constraint_handler_s(ignore_handler_s);

    int r = strcpy_s(dst, capacity, src);
    printf("dst = \"%s\", r = %d\n", dst, r);
    r = strcpy_s(dst, capacity, "Take even more tests.");
    printf("dst = \"%s\", r = %d\n", dst, r);

    int err = strcat_s(dest, capacity, " .............. ");
    printf("dest = \"%s\", err = %d\n", dest, err);
    err = strcat_s(dest, capacity, " and this is too much");
    printf("dest = \"%s\", err = %d\n", dest, err);
#endif
}

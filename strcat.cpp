// Abstract
//
// The standard C library includes functions that are designed to prevent
// buffer overflows, particularly strncpy() and strncat(). These
// universally available functions discard data larger than the specified
// length, regardless of whether it fits into the buffer. These functions
// are deprecated for new Windows code because they are frequently used
// incorrectly.
//
// see too
// https://us-cert.cisa.gov/bsi/articles/knowledge/coding-practices/strncpy-and-strncat
// https://us-cert.cisa.gov/bsi/articles/knowledge/coding-practices/strlcpy-and-strlcat
// and
// https://us-cert.cisa.gov/bsi/articles/knowledge/coding-practices/strcpy_s-and-strcat_s
//
#include <cassert>
#include <cstring>
#include <iostream>

constexpr size_t MAXPATHLEN{256};
constexpr size_t MAX_STRING_LEN{50};
constexpr const char* source = {"A not too long sentence here! "};
constexpr const char* more = {"Too mutch ... text!!!!!"};
const char *dir = "/usr/local/etc/snmp/";
const char *file = "snmpd.conf";

namespace {

#if !(defined(__APPLE__) || defined(__BSD__))
// If the return value is >= dstsize, the output string has been
// truncated.  It is the caller's responsibility to handle this
size_t strlcpy(char* dst, const char* src, size_t len)
{
    int n = snprintf(dst, len, "%s", src);
    assert(n >= 0 && (size_t)n < len);

    return n;
}
#endif

void good_sample()
{
    char pname[MAXPATHLEN];
    size_t capacity = sizeof(pname);

    // ...

    size_t n = strlcpy(pname, dir, capacity);
    if (n >= capacity)
    {
        goto toolong;
    }

    capacity = sizeof(pname) - n ;
    if (strlcpy(pname + n, file, capacity ) >= capacity)
    {
        goto toolong;
    }

    std::cout << pname << std::endl;
    return;

toolong:
    std::cerr << "truncated pname!" << std::endl;
    exit(EXIT_FAILURE);
}

} // namespace local

int main()
{
    good_sample();

    char dest[MAX_STRING_LEN + 1];

#undef USE_STRNCPY
#ifndef USE_STRNCPY
    strlcpy(dest, source, MAX_STRING_LEN);
#else
    // The strncpy() function doesn't null terminate the destination
    // string if the source string is at least as long as the
    // destination. (This behavior is defined by the C99 specification.)
    // As a result, the destination string MUST be null terminated after
    // calling strncpy().
    strncpy(dest, source, MAX_STRING_LEN);
    dest[MAX_STRING_LEN] = '\0'; // NOTE: to be sure! CK

    // There's also a performance problem with strncpy() in that it fills
    // the entire destination buffer with null bytes after the source
    // data has been exhausted!
#endif

    std::cout << dest << std::endl;

#undef SHOW_THE_BUG
#ifdef SHOW_THE_BUG
    strncat(dest, source, MAX_STRING_LEN); // FIXME: buffer overflow!
    std::cout << dest << std::endl;
    dest[MAX_STRING_LEN] = '\0';
#endif

    // The problem is that the last argument to strncat() should NOT be
    // the total buffer length! It should be the space remaining after
    // the call to strncpy(). Both functions require that you specify the
    // remaining space and not the total size of the buffer.
    strncat(dest, more, sizeof(dest) - strlen(dest) - 1);

    assert(strlen(dest) == MAX_STRING_LEN);
    std::cout << dest << std::endl;
}

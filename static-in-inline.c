static int I = 112;

extern inline void func(int a)
{
    int b = a * I; // diagnostic required
                   /* ... */
}

int main() { func(42); }
/*
 * https://wiki.sei.cmu.edu/confluence/display/c/MSC40-C.+Do+not+violate+constraints
 * static-in-inline.c:4:15: clang warning: static variable 'I' is used in an
 * inline function with external linkage [-Wstatic-in-inline]
 */

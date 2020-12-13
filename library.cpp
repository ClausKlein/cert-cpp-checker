#include "library.h"

// library.cpp
void err59() /*** throw(int) ***/
{
    // ...
    if (true) {
        throw 42;
    }
}

void err60(S& s) { s.f(); }

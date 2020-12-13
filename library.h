// library.h
#pragma once

struct S
{
    virtual void f()
    { /* ... */
    }
};

void err59() /*** throw(int) ***/; // Implemented by the library
void err60(S& s);                  // Implemented by the library, calls S::f()

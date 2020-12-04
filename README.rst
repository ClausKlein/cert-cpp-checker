===================
usage examples:
===================


References:
===================

- https://wiki.sei.cmu.edu/confluence/display/cplusplus/2+Rules
- see too https://clang-analyzer.llvm.org
- and https://clang.llvm.org/extra/clang-tidy/


To check all files:
===================

::

  Claus-iMac:cert-test clausklein$ make -n check
  scan-build  --view --use-c++ clang++ make -j4 -B
  scan-build: Analysis run complete.
  scan-build: 26 bugs found.
  scan-build: Run 'scan-view /var/folders/wb/ckvxxgls5db7qyhqq4y5_l1c0000gq/T/scan-build-2020-12-04-214942-57798-1' to examine bug reports.
  scan-build: Viewing analysis results in '/var/folders/wb/ckvxxgls5db7qyhqq4y5_l1c0000gq/T/scan-build-2020-12-04-214942-57798-1' using scan-view.
    import imp
  Starting scan-view at: http://127.0.0.1:8181
    Use Ctrl-C to exit.


Or to check one file only:
===========================

::

    Claus-iMac:cert-test clausklein$ make -B cert-MEM54
    [
    {
    "directory": "/Users/clausklein/cert-test",
    "command": "clang++ -std=c++20 -Wall -Wextra -Wpedantic -isystem /usr/local/include -isystem /usr/local/Cellar/llvm/11.0.0/include/c++/v1/    cert-MEM54.cpp -o cert-MEM54 ",
    "file": "cert-MEM54.cpp"
    }
    ]
    clang-tidy cert-MEM54.cpp
    39022 warnings generated.
    /Users/clausklein/cert-test/cert-MEM54.cpp:14:16: warning: Storage provided to placement new is only 2 bytes, whereas the allocated type requires 8 bytes [clang-analyzer-cplusplus.PlacementNew]
        long* lp = ::new (&s) long; // diagnostic required
                   ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:109:5: note: Calling 'foo'
        foo();
        ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:13:5: note: 's' initialized to 0
        short s{};
        ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:14:16: note: Calling 'operator new'
        long* lp = ::new (&s) long; // diagnostic required
                   ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:14:16: note: Returning from 'operator new'
    /Users/clausklein/cert-test/cert-MEM54.cpp:14:16: note: Storage provided to placement new is only 2 bytes, whereas the allocated type requires 8 bytes
    /Users/clausklein/cert-test/cert-MEM54.cpp:25:16: warning: Storage type is aligned to 1 bytes but allocated type is aligned to 8 bytes [clang-analyzer-cplusplus.PlacementNew]
        long* lp = ::new (buffer) long; // diagnostic required
                   ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:24:5: note: 'buffer' initialized here
        unsigned char buffer[sizeof(long)];
        ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:25:16: note: Storage type is aligned to 1 bytes but allocated type is aligned to 8 bytes
        long* lp = ::new (buffer) long; // diagnostic required
                   ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:25:23: warning: do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay]
        long* lp = ::new (buffer) long; // diagnostic required
                          ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:32:8: warning: class 'S' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions]
    struct S
           ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:54:13: warning: Storage provided to placement new is only 24 bytes, whereas the allocated array type requires more space for internal needs [clang-analyzer-cplusplus.PlacementNew]
        S* sp = ::new (buffer) S[N];
                ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:53:5: note: 'buffer' initialized here
        alignas(S) unsigned char buffer[sizeof(S) * N];
        ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:54:13: note: Storage provided to placement new is only 24 bytes, whereas the allocated array type requires more space for internal needs
        S* sp = ::new (buffer) S[N];
                ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:54:20: warning: do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay]
        S* sp = ::new (buffer) S[N];
                       ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:59:9: warning: do not use pointer arithmetic [cppcoreguidelines-pro-bounds-pointer-arithmetic]
            sp[i].~S(); // diagnostic required
            ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:85:20: warning: do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay]
        S* sp = ::new (buffer, sizeof(buffer)) S[N];
                       ^
    /Users/clausklein/cert-test/cert-MEM54.cpp:90:9: warning: do not use pointer arithmetic [cppcoreguidelines-pro-bounds-pointer-arithmetic]
            sp[i].~S();
            ^
    Suppressed 39013 warnings (39009 in non-user code, 4 with check filters).
    Use -header-filter=.* to display errors from all non-system headers. Use -system-headers to display errors from system headers as well.



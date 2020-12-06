===================
Usage examples:
===================

:Author: Claus Klein

Contents:
=========

.. contents::


References:
===================

- https://wiki.sei.cmu.edu/confluence/display/cplusplus/2+Rules
- see too https://clang-analyzer.llvm.org
- and https://clang.llvm.org/extra/clang-tidy/


Compile all files with -Wextra warnings:
========================================

clausklein$ make all -B::

    cmake -B /Users/clausklein/cert-test/build -S /Users/clausklein/cert-test -G Ninja
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /Users/clausklein/cert-test/build
    ln -fs /Users/clausklein/cert-test/build/compile_commands.json compile_commands.json
    [
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM50.cpp   -o cert-MEM50
    cert-MEM50.cpp:12:23: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
        const char* str = str_func().c_str(); // diagnostic required
                          ^~~~~~~~~~
    1 warning generated.
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM51.cpp   -o cert-MEM51
    cert-MEM51.cpp:27:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete]
        delete array; // diagnostic required
        ^
              []
    cert-MEM51.cpp:25:18: note: allocated with 'new[]' here
        int* array = new int[10];
                     ^
    1 warning generated.
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM52.cpp   -o cert-MEM52
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM53.cpp   -o cert-MEM53
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM54.cpp   -o cert-MEM54
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM55.cpp   -o cert-MEM55
    clang++ -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM56.cpp   -o cert-MEM56
    ]


To check all files and get an html report:
==========================================

clausklein$ gmake check::


  /usr/local/opt/llvm/bin/scan-build --keep-going --view --use-c++ clang++ -o /Users/clausklein/cert-test/html gmake -j4 -B all
  scan-build: Using '/usr/local/Cellar/llvm/11.0.0/bin/clang-11' for static analysis
  gmake[1]: Entering directory '/Users/clausklein/cert-test'
  cmake -B /Users/clausklein/cert-test/build -S /Users/clausklein/cert-test -G Ninja
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM50.cpp   -o cert-MEM50
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM51.cpp   -o cert-MEM51
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM52.cpp   -o cert-MEM52
  -- Configuring done
  -- Generating done
  -- Build files have been written to: /Users/clausklein/cert-test/build
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM53.cpp   -o cert-MEM53
  cert-MEM51.cpp:27:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete]
      delete array; // diagnostic required
      ^
            []
  cert-MEM51.cpp:25:18: note: allocated with 'new[]' here
      int* array = new int[10];
                   ^
  cert-MEM50.cpp:12:23: warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
      const char* str = str_func().c_str(); // diagnostic required
                        ^~~~~~~~~~
  1 warning generated.
  1 warning generated.
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM54.cpp   -o cert-MEM54
  cert-MEM53.cpp:17:24: warning: The expression is an uninitialized value. The computed value will also be garbage [core.uninitialized.Assign]
      int foo() { return ++s; } // diagnostic required
                         ^~~
  1 warning generated.
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM55.cpp   -o cert-MEM55
  cert-MEM50.cpp:13:5: warning: Inner pointer of container used after re/deallocation [cplusplus.InnerPointer]
      display_string(str);                  /* Undefined behavior */
      ^~~~~~~~~~~~~~~~~~~
  cert-MEM50.cpp:28:14: warning: Use of memory after it is freed [cplusplus.NewDelete]
      auto i = s->f(); // diagnostic required
               ^~~~~~
  cert-MEM50.cpp:38:14: warning: Use of memory after it is freed [cplusplus.NewDelete]
      auto i = (*array)++; // diagnostic required
               ^~~~~~~~~~
  cert-MEM50.cpp:52:10: warning: Use of zero-allocated memory [cplusplus.NewDelete]
      *ptr = 0;
           ^
  4 warnings generated.
  /usr/local/Cellar/llvm/11.0.0/bin/../libexec/c++-analyzer -std=c++17 -Wextra -Wpedantic -isystem /usr/local/include     cert-MEM56.cpp   -o cert-MEM56
  cert-MEM51.cpp:20:5: warning: Argument to 'delete' is the address of the local variable 'space', which is not memory allocated by 'new' [cplusplus.NewDelete]
      delete s1; // diagnostic required
      ^~~~~~~~~
  cert-MEM51.cpp:27:5: warning: Memory allocated by 'new[]' should be deallocated by 'delete[]', not 'delete' [unix.MismatchedDeallocator]
      delete array; // diagnostic required
      ^~~~~~~~~~~~
  cert-MEM51.cpp:42:5: warning: Potential leak of memory pointed to by 'i1' [cplusplus.NewDeleteLeaks]
      return *i1 * *i2; // diagnostic required
      ^~~~~~~~~~~~~~~~
  cert-MEM51.cpp:42:5: warning: Potential leak of memory pointed to by 'i2' [cplusplus.NewDeleteLeaks]
      return *i1 * *i2; // diagnostic required
      ^~~~~~~~~~~~~~~~
  cert-MEM51.cpp:56:12: warning: Attempt to free released memory [cplusplus.NewDelete]
      ~C() { delete p; } // diagnostic required
             ^~~~~~~~
  cert-MEM51.cpp:74:5: warning: Memory allocated by malloc() should be deallocated by free(), not 'delete' [unix.MismatchedDeallocator]
      delete i; // diagnostic required
      ^~~~~~~~
  6 warnings generated.
  ln -fs /Users/clausklein/cert-test/build/compile_commands.json compile_commands.json
  [
  cert-MEM55.cpp:20:1: warning: Potential leak of memory pointed to by 'p' [unix.Malloc]
  }
  ^
  1 warning generated.
  cert-MEM54.cpp:14:16: warning: Storage provided to placement new is only 2 bytes, whereas the allocated type requires 8 bytes [cplusplus.PlacementNew]
      long* lp = ::new (&s) long; // diagnostic required
                 ^~~~~~~~~~~~~~~
  cert-MEM54.cpp:25:16: warning: Storage type is aligned to 1 bytes but allocated type is aligned to 8 bytes [cplusplus.PlacementNew]
      long* lp = ::new (buffer) long; // diagnostic required
                 ^~~~~~~~~~~~~~~~~~~
  cert-MEM54.cpp:54:13: warning: Storage provided to placement new is only 24 bytes, whereas the allocated array type requires more space for internal needs [cplusplus.PlacementNew]
      S* sp = ::new (buffer) S[N];
              ^~~~~~~~~~~~~~~~~~~
  3 warnings generated.
  ]
  gmake[1]: Leaving directory '/Users/clausklein/cert-test'
  scan-build: Analysis run complete.
  scan-build: 15 bugs found.
  scan-build: Run 'scan-view /Users/clausklein/cert-test/html/2020-12-06-112729-78820-1' to examine bug reports.
  scan-build: Viewing analysis results in '/Users/clausklein/cert-test/html/2020-12-06-112729-78820-1' using scan-view.


To get a textual report from clang-tidy:
========================================

after make all::

    clausklein$ builddriver run-clang-tidy

    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='9', severity='warning', message="returning a newly created resource of type 'void *' or 'gsl::owner<>' from a function whose return type is not 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='59')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='9', severity='warning', message='do not manage memory manually; consider a container or a smart pointer [cppcoreguidelines-no-malloc,hicpp-no-malloc]', column='66')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='11', severity='warning', message='do not manage memory manually; use RAII [cppcoreguidelines-no-malloc,hicpp-no-malloc]', column='44')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='11', severity='warning', message="calling legacy resource function without passing a 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='44')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='12', severity='warning', message="redundant 'operator delete' declaration [readability-redundant-declaration]", column='6')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='16', severity='warning', message="initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='18', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM55.cpp', lineno='20', severity='warning', message="Potential leak of memory pointed to by 'p' [clang-analyzer-unix.Malloc]", column='1')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM52.cpp', lineno='17', severity='warning', message="initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM52.cpp', lineno='23', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM52.cpp', lineno='41', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM52.cpp', lineno='42', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM52.cpp', lineno='50', severity='warning', message="initializing non-owner argument of type '(anonymous namespace)::A *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='24')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM52.cpp', lineno='50', severity='warning', message="initializing non-owner argument of type '(anonymous namespace)::B *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='31')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM53.cpp', lineno='17', severity='warning', message='The expression is an uninitialized value. The computed value will also be garbage [clang-analyzer-core.uninitialized.Assign]', column='24')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM53.cpp', lineno='27', severity='warning', message="initializing non-owner '(anonymous namespace)::S *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM53.cpp', lineno='27', severity='warning', message='do not manage memory manually; consider a container or a smart pointer [cppcoreguidelines-no-malloc,hicpp-no-malloc]', column='32')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM53.cpp', lineno='30', severity='warning', message='do not manage memory manually; use RAII [cppcoreguidelines-no-malloc,hicpp-no-malloc]', column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM53.cpp', lineno='30', severity='warning', message="calling legacy resource function without passing a 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='13', severity='warning', message='Inner pointer of container used after re/deallocation [clang-analyzer-cplusplus.InnerPointer]', column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='24', severity='warning', message="initializing non-owner 'S *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='26', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='28', severity='warning', message='Use of memory after it is freed [clang-analyzer-cplusplus.NewDelete]', column='14')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='34', severity='warning', message="initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='36', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='38', severity='warning', message='Use of memory after it is freed [clang-analyzer-cplusplus.NewDelete]', column='14')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='51', severity='warning', message='do not declare variables of type va_list; use variadic templates instead [cppcoreguidelines-pro-type-vararg,hicpp-vararg]', column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='52', severity='warning', message='Use of zero-allocated memory [clang-analyzer-cplusplus.NewDelete]', column='10')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM50.cpp', lineno='73', severity='warning', message='do not use pointer arithmetic [cppcoreguidelines-pro-bounds-pointer-arithmetic]', column='42')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='7', severity='warning', message="class 'S' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions,hicpp-special-member-functions]", column='8')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='16', severity='warning', message="initializing non-owner '(anonymous namespace)::S *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='20', severity='warning', message="Argument to 'delete' is the address of the local variable 'space', which is not memory allocated by 'new' [clang-analyzer-cplusplus.NewDelete]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='20', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='25', severity='warning', message="initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='27', severity='warning', message="Memory allocated by 'new[]' should be deallocated by 'delete[]', not 'delete' [clang-analyzer-unix.MismatchedDeallocator]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='27', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='32', severity='warning', message="variable 'i1' is not initialized [cppcoreguidelines-init-variables]", column='10')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='33', severity='warning', message="variable 'i2' is not initialized [cppcoreguidelines-init-variables]", column='10')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='35', severity='warning', message="assigning newly created 'gsl::owner<>' to non-owner 'int *' [cppcoreguidelines-owning-memory]", column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='36', severity='warning', message="assigning newly created 'gsl::owner<>' to non-owner 'int *' [cppcoreguidelines-owning-memory]", column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='38', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='39', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='42', severity='warning', message="Potential leak of memory pointed to by 'i1' [clang-analyzer-cplusplus.NewDeleteLeaks]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='42', severity='warning', message="Potential leak of memory pointed to by 'i2' [clang-analyzer-cplusplus.NewDeleteLeaks]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='50', severity='warning', message="class 'C' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions,hicpp-special-member-functions]", column='7')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='55', severity='warning', message='single-argument constructors must be marked explicit to avoid unintentional implicit conversions [hicpp-explicit-conversions]', column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='56', severity='warning', message='Attempt to free released memory [clang-analyzer-cplusplus.NewDelete]', column='12')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='65', severity='warning', message="initializing non-owner '(anonymous namespace)::P *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='72', severity='warning', message="initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='72', severity='warning', message='do not manage memory manually; consider a container or a smart pointer [cppcoreguidelines-no-malloc,hicpp-no-malloc]', column='32')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='74', severity='warning', message="Memory allocated by malloc() should be deallocated by free(), not 'delete' [clang-analyzer-unix.MismatchedDeallocator]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM51.cpp', lineno='74', severity='warning', message="deleting a pointer through a type that is not marked 'gsl::owner<>'; consider using a smart pointer instead [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='14', severity='warning', message="initializing non-owner 'long *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='14', severity='warning', message='Storage provided to placement new is only 2 bytes, whereas the allocated type requires 8 bytes [clang-analyzer-cplusplus.PlacementNew]', column='16')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='25', severity='warning', message="initializing non-owner 'long *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='25', severity='warning', message='Storage type is aligned to 1 bytes but allocated type is aligned to 8 bytes [clang-analyzer-cplusplus.PlacementNew]', column='16')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='25', severity='warning', message='do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay]', column='23')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='32', severity='warning', message="class 'S' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions,hicpp-special-member-functions]", column='8')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='54', severity='warning', message="initializing non-owner '(anonymous namespace)::S *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='54', severity='warning', message='Storage provided to placement new is only 24 bytes, whereas the allocated array type requires more space for internal needs [clang-analyzer-cplusplus.PlacementNew]', column='13')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='54', severity='warning', message='do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay]', column='20')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='59', severity='warning', message='do not use pointer arithmetic [cppcoreguidelines-pro-bounds-pointer-arithmetic]', column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='85', severity='warning', message="initializing non-owner '(anonymous namespace)::S *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='85', severity='warning', message='do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay]', column='20')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM54.cpp', lineno='90', severity='warning', message='do not use pointer arithmetic [cppcoreguidelines-pro-bounds-pointer-arithmetic]', column='9')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM56.cpp', lineno='12', severity='warning', message="initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]", column='5')
    WarningErrorEntry(path='/Users/clausklein/cert-test/cert-MEM56.cpp', lineno='17', severity='warning', message="class 'B' defines a default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions,hicpp-special-member-functions]", column='8')


If you want to run all samples you simply can:
==============================================

clausklein$ make test::

  cmake --build /Users/clausklein/cert-test/build -- -v all
  ninja: no work to do.
  cmake --build /Users/clausklein/cert-test/build -- -v test
  [0/1] cd /Users/clausklein/cert-test/build && /usr/local/Cellar/cmake/3.18.4/bin/ctest --force-new-ctest-process
  Test project /Users/clausklein/cert-test/build
      Start 1: test_cert-MEM50
  1/7 Test #1: test_cert-MEM50 ..................   Passed    0.38 sec
      Start 2: test_cert-MEM51
  2/7 Test #2: test_cert-MEM51 ..................Child aborted***Exception:   0.18 sec
      Start 3: test_cert-MEM52
  3/7 Test #3: test_cert-MEM52 ..................   Passed    0.19 sec
      Start 4: test_cert-MEM53
  4/7 Test #4: test_cert-MEM53 ..................***Failed    0.18 sec
      Start 5: test_cert-MEM54
  5/7 Test #5: test_cert-MEM54 ..................   Passed    0.18 sec
      Start 6: test_cert-MEM55
  6/7 Test #6: test_cert-MEM55 ..................   Passed    0.19 sec
      Start 7: test_cert-MEM56
  7/7 Test #7: test_cert-MEM56 ..................Child aborted***Exception:   0.18 sec
  
  57% tests passed, 3 tests failed out of 7
  
  Total Test time (real) =   1.52 sec
  
  The following tests FAILED:
  	  2 - test_cert-MEM51 (Child aborted)
  	  4 - test_cert-MEM53 (Failed)
  	  7 - test_cert-MEM56 (Child aborted)
  Errors while running CTest
  FAILED: CMakeFiles/test.util 
  cd /Users/clausklein/cert-test/build && /usr/local/Cellar/cmake/3.18.4/bin/ctest --force-new-ctest-process
  ninja: build stopped: subcommand failed.
  make: *** [test] Error 1

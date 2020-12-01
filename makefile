#
# from https://wiki.sei.cmu.edu/confluence/display/cplusplus/Clang
#
CXXFLAGS:=-std=c++20 -Wall -Wextra -Wpedantic -Werror -isystem /usr/local/Cellar/llvm/11.0.0/include/c++/v1/ -isystem /usr/local/include

#XXX CXXFLAGS+=-analyzer-checker=cplusplus    # EXP51-CPP. Do not delete an array through a pointer of the incorrect type

CXXFLAGS+=-Wdangling-initializer-list    # EXP54-CPP. Do not access an object outside of its lifetime
CXXFLAGS+=-Wdelete-incomplete    # EXP57-CPP. Do not cast or delete pointers to incomplete classes
CXXFLAGS+=-Wdelete-non-virtual-dtor    # OOP52-CPP. Do not delete a polymorphic object without a virtual destructor
CXXFLAGS+=-Wdynamic-class-memaccess    # EXP60-CPP. Do not pass a nonstandard-layout type object across execution boundaries
CXXFLAGS+=-Wexceptions    # ERR53-CPP. Do not reference base classes or class data members in a constructor or destructor function-try-block handler
# CXXFLAGS+=-Wexceptions    # ERR54-CPP. Catch handlers should order their parameter types from most derived to least derived
CXXFLAGS+=-Winvalid-noreturn    # MSC53-CPP. Do not return from a function declared [[noreturn]]
CXXFLAGS+=-Winvalid-offsetof    # EXP59-CPP. Use offsetof() on valid types and members
CXXFLAGS+=-Wmismatched-new-delete    # MEM51-CPP. Properly deallocate dynamically allocated resources
CXXFLAGS+=-Wreorder    # OOP53-CPP. Write constructor member initializers in the canonical order
CXXFLAGS+=-Wreserved-id-macro    # DCL51-CPP. Do not declare or define a reserved identifier
CXXFLAGS+=-Wreturn-type    # MSC52-CPP. Value-returning functions must return a value from all exit paths
CXXFLAGS+=-Wunevaluated-expression    # EXP52-CPP. Do not rely on side effects in unevaluated operands
CXXFLAGS+=-Wuninitialized    # EXP53-CPP. Do not read uninitialized memory
CXXFLAGS+=-Wunsequenced    # EXP50-CPP. Do not depend on the order of evaluation for side effects
CXXFLAGS+=-Wuser-defined-literals    # DCL51-CPP. Do not declare or define a reserved identifier
CXXFLAGS+=-Wvarargs    # EXP58-CPP. Pass an object of the correct type to va_start
CXXFLAGS+=-Wvexing-parse    # DCL53-CPP. Do not write syntactically ambiguous declarations

CXX:=clang++

#XXX 
MAKEFLAGS+=-B

.PHONY: init all check clean
PROGRAMS:=init dynamic_pointer_cast slide slice cereal-test
check:

all: init $(PROGRAMS)
	@echo ]
	@echo scan-build --use-c++ $(CXX) make

init:
	@echo [

%: %.cpp
	@echo \{
	@echo \"directory\": \"$(CURDIR)\",
	@echo -n \"command\": \"
	$(LINK.cc) $< -o $@
	@echo \"file\": \"$(<)\",
	@echo \},

check: all
	run-clang-tidy

clean:
	rm -rf *~ $(PROGRAMS)

MAKEFLAGS+= --warn-undefined-variables

COLOR?=
VERBOSE?=
MAKESILENT?=

GMAKE:=$(shell which gmake)
ifeq (NO$(GMAKE),NO)
  GMAKE:=make
else
  GMAKE:=gmake
endif

NINJA:=$(shell which ninja)
ifeq (NO$(NINJA),NO)
  GENERATOR:=
endif

GENERATOR?=-G Ninja

TARGET_ARCH:=
CPPFLAGS?=-isystem /usr/local/include

#XXX CC:=gcc-10
CC:=clang
CFLAGS:=-std=c11 -Wextra -Wpedantic -Wshadow

#XXX CXX:=g++-11
CXX:=clang++
CXXFLAGS:=-std=c++17 -Wextra -Wpedantic -Wshadow

LDLIBS:=$(CURDIR)/library.a
LDFLAGS:=-L/usr/local/lib
LOADLIBES:=


HTMLDIR?=$(CURDIR)/html
BUILDDIR?=$(CURDIR)/build


UNAME:=$(shell uname)
ifeq ($(UNAME),Darwin)
  SCAN_BUILD?=/usr/local/opt/llvm/bin/scan-build
  #XXX CPPFLAGS+=-isystem /usr/local/Cellar/llvm/11.0.0/include/c++/v1/
else
  CLANG_VERSION:=$(shell clang --version | grep -w version | perl -n -e 'print if s/^.*clang version (\d+)\..*/$$1/')
  SCAN_BUILD:=$(shell which scan-build-$(CLANG_VERSION) || which scan-build)
endif


#
#XXX # from https://wiki.sei.cmu.edu/confluence/display/cplusplus/Clang
#
#XXX CXXFLAGS+=-analyzer-checker=cplusplus    # EXP51-CPP. Do not delete an array through a pointer of the incorrect type

#XXX Not needed and problems with old clang-analyzer on debian! CK
## CXXFLAGS+=-Wdangling-gsl    # MEM50-CPP. Do not access freed memory
## CXXFLAGS+=-Wdangling-initializer-list    # EXP54-CPP. Do not access an object outside of its lifetime
## CXXFLAGS+=-Wdelete-incomplete    # EXP57-CPP. Do not cast or delete pointers to incomplete classes
## CXXFLAGS+=-Wdelete-non-virtual-dtor    # OOP52-CPP. Do not delete a polymorphic object without a virtual destructor
## CXXFLAGS+=-Wdynamic-class-memaccess    # EXP60-CPP. Do not pass a nonstandard-layout type object across execution boundaries
## CXXFLAGS+=-Wexceptions    # ERR53-CPP. Do not reference base classes or class data members in a constructor or destructor function-try-block handler
## # CXXFLAGS+=-Wexceptions    # ERR54-CPP. Catch handlers should order their parameter types from most derived to least derived
## CXXFLAGS+=-Winvalid-noreturn    # MSC53-CPP. Do not return from a function declared [[noreturn]]
## CXXFLAGS+=-Winvalid-offsetof    # EXP59-CPP. Use offsetof() on valid types and members
## CXXFLAGS+=-Wmismatched-new-delete    # MEM51-CPP. Properly deallocate dynamically allocated resources
## CXXFLAGS+=-Wreorder    # OOP53-CPP. Write constructor member initializers in the canonical order
## CXXFLAGS+=-Wreserved-id-macro    # DCL51-CPP. Do not declare or define a reserved identifier
## CXXFLAGS+=-Wreturn-type    # MSC52-CPP. Value-returning functions must return a value from all exit paths
## CXXFLAGS+=-Wunevaluated-expression    # EXP52-CPP. Do not rely on side effects in unevaluated operands
## CXXFLAGS+=-Wuninitialized    # EXP53-CPP. Do not read uninitialized memory
## CXXFLAGS+=-Wunsequenced    # EXP50-CPP. Do not depend on the order of evaluation for side effects
## CXXFLAGS+=-Wuser-defined-literals    # DCL51-CPP. Do not declare or define a reserved identifier
## CXXFLAGS+=-Wvarargs    # EXP58-CPP. Pass an object of the correct type to va_start
## CXXFLAGS+=-Wvexing-parse    # DCL53-CPP. Do not write syntactically ambiguous declarations


# CFLAGS+=-Wstatic-in-inline    # MSC40-C. Do not violate constraints


# for cmake:
export MAKESILENT
export VERBOSE
export COLOR
export CXX
export CC


.PHONY: init all build check test format clean distclean

TESTS:=$(wildcard cert-*.cpp)
#XXX TESTS+= strcat.cpp
#XXX TESTS+= cereal-test.cpp dynamic_pointer_cast.cpp safeComparison.cpp slice.cpp slide.cpp timeConversion.cpp to_string.cpp
PROGRAMS:=$(TESTS:%.cpp=%)

######################################
#
# c++17 cereal-test.cpp dynamic_pointer_cast.cpp slide.cpp
# c++20 slice.cpp
#
# PREPARED: static-in-inline.c
#
######################################
build: library.a

# An execution boundary is the delimitation between code compiled by differing compilers
library.a: library.o
	ar -rv $@ $<


library.o: CXX:=g++ CXXFLAGS:=-std=c++98
library.o: library.h
library.o: library.cpp
	g++ -std=c++98 -c $< -o $@


all: library.a $(PROGRAMS) #XXX init test #NO! check
	@echo ]

init: library.a GNUmakefile compile_commands.json
	@echo [

# %: %.cpp
# 	@echo \{
# 	@echo \"directory\": \"$(CURDIR)\",
# 	@echo -n \"command\": \"
# 	$(LINK.cc) $< -o $@
# 	@echo \",
# 	@echo \"file\": \"$(<)\"
# 	@echo \},
# 	clang-tidy $<

check: init
	$(SCAN_BUILD) --keep-going --use-c++ $(CXX) -o $(HTMLDIR) $(GMAKE) -j4 -B all

compile_commands.json: $(BUILDDIR)/compile_commands.json
	ln -fs $< $@

$(BUILDDIR)/compile_commands.json: CMakeLists.txt
	cmake -B $(@D) -S $(CURDIR) $(GENERATOR)

build: compile_commands.json
	cmake --build $(BUILDDIR) -- all

test: build
	cmake --build $(BUILDDIR) -- $@

format:
	clang-format -i *.cpp *.c *.h #XXX *.hpp

clean:
	rm -f *.a *.o $(PROGRAMS)
	-cmake --build $(BUILDDIR) -- $@

distclean: #XXX NO! clean
	rm -f .*~ *~ *.a *.o $(PROGRAMS)
	rm -rf $(BUILDDIR) $(HTMLDIR) compile_commands.json

GNUmakefile :: ;

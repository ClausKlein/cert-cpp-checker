#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <string>

/// FIO51-CPP. Close files when they are no longer needed
void f(const std::string& fileName)
{
    std::fstream file(fileName);
    if (!file.is_open()) {
        // Handle error
        return;
    }
    // ...
    std::terminate();
}

/// see too
/// https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP51-CPP.+Do+not+slice+derived+objects
struct S : std::exception
{
    const char* what() const noexcept override { return "My custom exception"; }
};

/// ERR61-CPP. Catch exceptions by lvalue reference
void e()
{
    try {
        throw S();
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

enum EnumType : int
{
    First,
    Second,
    Third
};

/// INT50-CPP. Do not cast to an out-of-range enumeration value
void bar(int intVar)
{
    auto enumVar = static_cast<EnumType>(intVar);

    if (enumVar < EnumType::First || enumVar > EnumType::Third) {
        // Handle error
        return;
    }

    std::cout << static_cast<int>(enumVar) << std::endl;
}

void good(const std::string& input)
{
    std::string email{input};

    std::replace(email.begin(), email.end(), ';', ' ');

    std::cout << email << std::endl;
}

void bad(const std::string& input)
{
    std::string email;

    // Copy input into email converting ";" to " "
    std::string::iterator loc = email.begin();
    for (auto i = input.begin(), e = input.end(); i != e; ++i, ++loc) {
        email.insert(loc, *i != ';' ? *i : ' ');
    }

    std::cout << email << std::endl;
}

class Base
{
    // NOTE: unused! int a{};

public:
    virtual void f() const { std::cout << "I am base!\n"; }
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    void f() const override { std::cout << "I am derived!\n"; }
    ~Derived() override = default;
};

int main()
{
    auto basePtr = std::make_shared<Base>();
    std::cout << "Base pointer says: ";
    basePtr->f();

    auto derivedPtr = std::make_shared<Derived>();
    std::cout << "Derived pointer says: ";
    derivedPtr->f();

    // static_pointer_cast to go up class hierarchy
    basePtr = std::static_pointer_cast<Base>(derivedPtr);
    std::cout << "Base pointer to derived says: ";
    basePtr->f();

    // dynamic_pointer_cast to go down/across class hierarchy
    auto downcastedPtr = std::dynamic_pointer_cast<Derived>(basePtr);
    if (downcastedPtr) {
        std::cout << "Downcasted pointer says: ";
        downcastedPtr->f();
    }

    // All pointers to derived share ownership
    std::cout << "Pointers to underlying derived: " << derivedPtr.use_count() << "\n";

    std::string test("test; after';'");
    good(test);
    bad(test);

    bar(42);

    e();
    f("/tmp/file.txt");
}

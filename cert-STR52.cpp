//
// STR52-CPP. Use valid references, pointers, and iterators to reference elements of a basic_string
//

#include <iostream>
#include <string>

namespace {

void foo(const std::string& input)
{
    std::string email;

    // Copy input into email converting ";" to " "
    std::string::iterator loc = email.begin();
    for (auto i = input.begin(), e = input.end(); i != e; ++i, ++loc) {
        /*loc =*/email.insert(loc, *i != ';' ? *i : ' '); // undefined behavior!
    }
}

void bad(std::string& exampleString)
{
    const char* data = exampleString.data();
    // ...
    exampleString.replace(33, 33, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    // ...
    puts(data); // undefined behavior!
}

void better(std::string& exampleString)
{
    exampleString.replace(0, 6, "better");
    // ...
    puts(exampleString.data());
}

} // namespace

int main()
{
    std::string s("hallo world;");
    foo(s);
    bad(s);
    better(s);
}

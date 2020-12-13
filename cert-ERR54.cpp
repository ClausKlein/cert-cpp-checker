//
// ERR54-CPP. Catch handlers should order their parameter types from most derived to least derived
//

#include <exception>

namespace {

// Classes used for exception handling
class B : public std::exception
{};
class D : public B
{};

void func() { throw D(); }

} // namespace

int main()
{
    try {
        func();
        // ...
    } catch (B& b) {
        // ...
        throw;
    } catch (D& d) { // diagnostic required
        // ...
    }
}

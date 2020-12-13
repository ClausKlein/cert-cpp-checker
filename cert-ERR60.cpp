//
// ERR60-CPP. Exception objects must be nothrow copy constructible
//

#include <exception>
#include <string>

namespace {

class S : public std::exception
{
    std::string m;

public:
    S(const char* msg) : m(msg) {}

    const char* what() const noexcept override { return m.c_str(); }
};

void g()
{
    // If some condition doesn't hold...
    throw S("Condition did not hold");
}

} // namespace

int main()
{
    try {
        g();
    } catch (S& s) {
        // Handle error
    }
}

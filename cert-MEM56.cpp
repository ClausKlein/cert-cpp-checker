//
// MEM56-CPP. Do not store an already-owned pointer value in an unrelated smart pointer
//

#include <iostream>
#include <memory>

namespace {

void doubleFree()
{
    int* i = ::new int(42); // diagnostic required
    std::shared_ptr<int> p1(i);
    std::shared_ptr<int> p2(i); // diagnostic required
}

struct B
{
    virtual ~B() = default; // Polymorphic object
                            // ...
};

struct D : B
{
    int i{};
    void foo() { std::cout << "D::foo() called " << ++i << ". time" << std::endl; }
};

void bar(const std::shared_ptr<D>& derived) { derived->foo(); }

void danglingPtr()
{
    std::shared_ptr<B> poly(new D); // diagnostic required
    // ...
    bar(std::shared_ptr<D>(dynamic_cast<D*>(poly.get()))); // diagnostic required
    // Any use of poly will now result in accessing freed memory.
}

struct S
{
    std::shared_ptr<S> g() { return std::shared_ptr<S>(this); } // diagnostic required
};

void realyBad()
{
    std::shared_ptr<S> s1 = std::make_shared<S>();
    // ...
    std::shared_ptr<S> s2 = s1->g();
}

void better()
{
    std::shared_ptr<B> poly = std::make_shared<D>();
    // ...
    bar(std::dynamic_pointer_cast<D, B>(poly));
    // poly is still referring to a valid pointer value.
}

struct Super : std::enable_shared_from_this<Super>
{
    std::shared_ptr<Super> g() { return shared_from_this(); }
};

void perfect()
{
    std::shared_ptr<Super> s1 = std::make_shared<Super>();
    std::shared_ptr<Super> s2 = s1->g();
}

} // namespace

int main()
{
    for (int i = 0; i < 21; ++i) {
        realyBad();
        doubleFree();
        danglingPtr();
        better();
        perfect();
    }
}

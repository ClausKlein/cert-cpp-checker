//
// ERR59-CPP. Do not throw an exception across execution boundaries
//

#include "library.h"

int main()
{
    try {
        err59();
    } catch (int& e) {
        // Handle error
    }
}

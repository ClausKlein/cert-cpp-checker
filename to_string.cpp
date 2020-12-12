#include "boost/lexical_cast.hpp"

#if __cpp_lib_format
#    include <format> // c++20 only
using std::format;
#else
#    include <fmt/core.h>
using ::fmt::format;
#endif

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main()
{
    double maxDouble = std::numeric_limits<double>::max();
    std::string str(std::to_string(maxDouble));

    std::cout << "std::to_string(" << std::setprecision(16) << maxDouble << ") == " << str
              << std::endl;
    std::cout << "boost::lexical_cast<std::string>(" << maxDouble << ") == " << std::setprecision(16)
              << boost::lexical_cast<std::string>(maxDouble) << std::endl;

    double back_stod = std::stod(str);
    double back_cast = boost::lexical_cast<double>(str);
    std::cout << "boost::lexical_cast<double>(" << back_cast << ") == " << back_stod << std::endl;

    std::string s = format("The format::answer is {}.", maxDouble);
    std::cout << s << std::endl;

    return 0;
}

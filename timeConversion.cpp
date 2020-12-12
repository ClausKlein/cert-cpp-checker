#include "timeConversion.h"

#include <ctime> // put_time
#include <iomanip>
#include <iostream>

//
// /usr/local/opt/llvm/include//c++/v1/ctime
//
int main()
{
    std::time_t t = std::time(nullptr);
    std::cout << "UTC:   " << std::put_time(std::gmtime(&t), "%c %Z") << '\n';

    auto start = system_clock::now();
    // ==============================

    struct timeval tv
    {};
    gettimeofday(&tv, nullptr);
    microseconds usecs = timevalToDuration(tv);

    timespec ts = timepointToTimespec(start);
    nanoseconds nsecs = timespecToDuration(ts);
    timespec TS = durationToTimespec(nsecs);

    // ==============================
    auto end = system_clock::now();
    duration<double> diff = end - start;

    if ((ts.tv_sec == TS.tv_sec) && (ts.tv_nsec == TS.tv_nsec)) {
        std::cout << "     seconds since 1970: "
                  << duration_cast<seconds>(start.time_since_epoch()).count() << std::endl;
        std::cout << "microseconds since 1970: " << duration_cast<microseconds>(usecs).count()
                  << std::endl;
        std::cout << " nanoseconds since 1970: " << duration_cast<nanoseconds>(nsecs).count()
                  << std::endl;
    }
    std::cout << "Time spend (ints) : " << diff.count() << " s\n";

    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof(buff), "%D %T", gmtime(&ts.tv_sec));
    std::cout << "Current time: " << buff << "." << std::setprecision(9) << ts.tv_nsec << " UTC"
              << std::endl;
}

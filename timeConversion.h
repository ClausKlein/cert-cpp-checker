//
// https://embeddedartistry.com/blog/2019/01/31/converting-between-timespec-stdchrono/
//

#include <sys/time.h>

#include <chrono>
#include <ctime>

/***
clock_gettime(CLOCK_REALTIME, timespec* ts)
struct timespec {
   time_t   tv_sec;
   long     tv_nsec;
}


int gettimeofday(struct timeval* tp, void* tzp);
struct timeval
{
    time_t         tv_sec;
    suseconds_t    tv_usec;
}
***/

namespace {

using namespace std::chrono; // for example brevity

constexpr nanoseconds timespecToDuration(timespec ts)
{
    auto duration = seconds{ts.tv_sec} + nanoseconds{ts.tv_nsec};

    return duration_cast<nanoseconds>(duration);
}

constexpr timespec durationToTimespec(nanoseconds dur)
{
    auto secs = duration_cast<seconds>(dur);
    dur -= secs;

    return timespec{secs.count(), dur.count()};
}

constexpr time_point<system_clock, nanoseconds> timespecToTimePoint(timespec ts)
{
    return time_point<system_clock, nanoseconds>{
        duration_cast<system_clock::duration>(timespecToDuration(ts))};
}

constexpr timespec timepointToTimespec(time_point<system_clock, nanoseconds> tp)
{
    auto secs = time_point_cast<seconds>(tp);
    auto ns = time_point_cast<nanoseconds>(tp) - time_point_cast<nanoseconds>(secs);

    return timespec{secs.time_since_epoch().count(), ns.count()};
}

constexpr microseconds timevalToDuration(timeval tv)
{
    auto duration = seconds{tv.tv_sec} + microseconds{tv.tv_usec};

    return duration_cast<microseconds>(duration);
}

} // namespace

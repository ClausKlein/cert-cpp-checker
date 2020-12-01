#include "math.h"

#include <cereal/archives/xml.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <random>

// Random Number Generation ==============================================
template <class T>
inline typename std::enable_if<std::is_floating_point<T>::value, T>::type
random_value(std::mt19937& gen)
{
    return std::uniform_real_distribution<T>(-10000.0, 10000.0)(gen);
}

template <class T>
inline typename std::enable_if<std::is_integral<T>::value && sizeof(T) != sizeof(char), T>::type
random_value(std::mt19937& gen)
{
    return std::uniform_int_distribution<T>(std::numeric_limits<T>::lowest(),
                                            std::numeric_limits<T>::max())(gen);
}

template <class T>
inline typename std::enable_if<std::is_integral<T>::value && sizeof(T) == sizeof(char), T>::type
random_value(std::mt19937& gen)
{
    return static_cast<T>(std::uniform_int_distribution<int64_t>(std::numeric_limits<T>::lowest(),
                                                                 std::numeric_limits<T>::max())(gen));
}

template <class T>
inline typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type
random_value(std::mt19937& gen)
{
    std::string s(std::uniform_int_distribution<int>(3, 30)(gen), ' ');
    for (char& c : s) {
        c = static_cast<char>(std::uniform_int_distribution<int>('A', 'Z')(gen));
    }
    return s;
}

size_t random_index(size_t min, size_t max, std::mt19937& gen)
{
    return std::uniform_int_distribution<size_t>(min, max)(gen);
}

template <class C> inline std::basic_string<C> random_basic_string(std::mt19937& gen)
{
    std::basic_string<C> s(std::uniform_int_distribution<int>(3, 30)(gen), ' ');
    for (C& c : s) {
        c = static_cast<C>(std::uniform_int_distribution<int>('A', 'Z')(gen));
    }
    return s;
}

template <size_t N> inline std::string random_binary_string(std::mt19937& gen)
{
    std::string s(N, ' ');
    for (auto& c : s) {
        c = static_cast<char>(std::uniform_int_distribution<int>('0', '1')(gen));
    }
    return s;
}
// =======================================================================

// Ostream overload for std::pair
template <class F, class S>
inline ::std::ostream& operator<<(::std::ostream& os, ::std::pair<F, S> const& p)
{
    os << "([" << p.first << "], [" << p.second << "])";
    return os;
}
// =======================================================================

struct unordered_naming
{
    int x;
    int y;
    int z;

    template <class Archive> void save(Archive& ar) const
    {
        ar(CEREAL_NVP(x), CEREAL_NVP(z), CEREAL_NVP(y));
    }

    template <class Archive> void load(Archive& ar)
    {
        ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z));
    }

    bool operator==(unordered_naming const& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

std::ostream& operator<<(std::ostream& os, unordered_naming const& s)
{
    os << "[x: " << s.x << " y: " << s.y << " z: " << s.z << "]";
    return os;
}

template <class IArchive, class OArchive> void test_unordered_load()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    auto rngB = [&]() { return random_value<int>(gen) % 2 == 0; };
    auto rngI = [&]() { return random_value<int>(gen); };
    auto rngF = [&]() { return random_value<float>(gen); };
    auto rngD = [&]() { return random_value<double>(gen); };
    // XXX auto rngS = [&](){ return random_basic_string<char>( gen ); };

    for (int i = 0; i < 2; ++i) {
        const auto* const name1 = "1"; // XXX or rngS()
        const auto* const name2 = "2";
        const auto* const name3 = "3";
        const auto* const name4 = "4";
        const auto* const name5 = "5";
        const auto* const name6 = "6";
        const auto* const name7 = "7";

        int o_int1 = rngI();
        double o_double2 = rngD();
        std::vector<bool> o_vecbool3 = {rngB(), rngB(), rngB(), rngB(), rngB()};
        int o_int4 = rngI();
        int o_int5 = rngI();
        int o_int6 = rngI();
        std::pair<float, unordered_naming> o_un7;
        o_un7.first = rngF();
        o_un7.second.x = rngI();
        o_un7.second.y = rngI();
        o_un7.second.z = rngI();

        {
            std::ofstream os("test.xml");
            OArchive oar(os);

            oar(cereal::make_nvp(name1, o_int1), cereal::make_nvp(name2, o_double2),
                cereal::make_nvp(name3, o_vecbool3), cereal::make_nvp(name4, o_int4),
                cereal::make_nvp(name5, o_int5), cereal::make_nvp(name6, o_int6),
                cereal::make_nvp(name7, o_un7));
        }
        std::cout << o_un7 << std::endl;

        decltype(o_int1) i_int1 = 0;
        decltype(o_double2) i_double2 = NAN;
        decltype(o_vecbool3) i_vecbool3;
        decltype(o_int4) i_int4 = 0;
        decltype(o_int5) i_int5 = 0;
        decltype(o_int6) i_int6 = 0;
        decltype(o_un7) i_un7;

        std::ifstream is("test.xml");
        {
            IArchive iar(is);

            iar(cereal::make_nvp(name7, o_un7), cereal::make_nvp(name2, i_double2),
                cereal::make_nvp(name4, i_int4), cereal::make_nvp(name3, i_vecbool3),
                cereal::make_nvp(name1, i_int1), cereal::make_nvp(name5, i_int5), i_int6, i_un7);
        }
        std::cout << i_un7 << std::endl;
    }
}

// ######################################################################
int main()
{
    test_unordered_load<cereal::XMLInputArchive, cereal::XMLOutputArchive>();

    return 0;
}

//
// CTR50-CPP. Guarantee that container indices and iterators are within the valid range
//

#include <cstddef>
#include <new>

namespace {

void bad_insert_in_table(int* table, std::size_t tableSize, int pos, int value)
{
    if (pos >= tableSize) { // NOTE: [-Wsign-compare]
        // Handle error
        return;
    }
    table[pos] = value;
}

void foo_insert_in_table(int* table, std::size_t tableSize, std::size_t pos, int value)
{
    if (pos >= tableSize) {
        // Handle error
        return;
    }
    table[pos] = value;
}

void insert_in_table(int* table, std::size_t tableSize, std::size_t pos, int value)
{ // #1
    if (pos >= tableSize) {
        // Handle error
        return;
    }
    table[pos] = value;
}

template <std::size_t N> void insert_in_table(int (&table)[N], std::size_t pos, int value)
{ // #2
    insert_in_table(table, N, pos, value);
}

} // namespace

int main()
{
    // Exposition only
    constexpr size_t SIZE = 100;
    int table1[SIZE];
    int* table2 = new int[SIZE];

    insert_in_table(table1, 0, 0); // Calls #2
    // XXX insert_in_table(table2, 0, 0); // Error, no matching function call
    insert_in_table(table1, SIZE, 0, 0); // Calls #1
    insert_in_table(table2, SIZE, 0, 0); // Calls #1

    bad_insert_in_table(table2, SIZE, -1, 0);
    foo_insert_in_table(table2, SIZE, 0, 0);
    delete[] table2;
}

#include<iostream>
#include<vector>

#include "main.h"

#include "vector_tests.h"
void run_iterator_tests(void);

// ============================================================================
// TESTING VECTOR AS A CONTAINER OF INTEGERS
// ============================================================================

int main( void )
{
    // Original values for later conference.
    constexpr std::array<int,5> values_i{1,2,3,4,5};
    constexpr std::array<int,5> source_i{6,7,8,9,10};
    std::cout << ">>> Testing out vector with integers.\n";
    run_regular_vector_tests<int,5>(values_i, source_i);

    std::array<std::string,5> values_s{"1","2","3","4","5"};
    std::array<std::string,5> source_s{"6","7","8","9","10"};
    std::cout << ">>> Testing out vector with strings.\n";
    run_regular_vector_tests<std::string,5>(values_s,source_s);

    std::cout << ">>> Testing out iterator operations on vector.\n";
    run_iterator_tests();

    return 1;
}

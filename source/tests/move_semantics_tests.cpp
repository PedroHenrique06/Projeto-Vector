#include <cstddef>
#include<iostream>
#include<vector>

#include "include/tm/test_manager.h"
#include "../include/vector.h"
#include "main.h"


// =============================================================
// Second batch of tests, focused on the iterator interface
// =============================================================

// Move Ctro.
#define MOVE_CTRO YES
// Move assignment operator.
#define MOVE_ASSIGNMENT YES
// Emplace back operator.
#define EMPLACE_BACK_INT YES
// Emplace back operator.
#define EMPLACE_BACK_STRING YES


void run_move_semantics_tests( void )
{

    // ========================================================================
    // Third batch of tests, focused on the iterator interface
    // ========================================================================
    TestManager tm{ "MOVE operations testing"};

#if MOVE_CTRO
    {
        BEGIN_TEST(tm, "MoveConstructor", "move the elements from another");

        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2( std::move( vec ) );

        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec2[i] );
    }
#endif

#if MOVE_ASSIGNMENT
    {
        BEGIN_TEST(tm, "MoveAssignOperator", "Move Assign Operator");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2;

        vec2 = std::move( vec );
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec2.empty() );
        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 0 );
        EXPECT_TRUE( vec.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( (int)i+1, vec2[i] );
    }
#endif

#if EMPLACE_BACK_INT
    {
        BEGIN_TEST(tm, "Emplace back integer", "vec<int>.emplace_back(value)");
        // Starting off with an empty vector.
        which_lib::vector<int> vec;

        constexpr std::array<int,5> values_i{1,2,3,4,5};

        EXPECT_TRUE( vec.empty() );
        for ( size_t i{0} ; i < std::size(values_i) ; ++i )
            vec.emplace_back( values_i[i] );
        EXPECT_FALSE( vec.empty() );
        EXPECT_EQ( vec.size(),  std::size(values_i) );

        // Checking if the vales are right.
        for ( size_t i{0} ; i < std::size(values_i) ; ++i )
            EXPECT_EQ( values_i[i], vec[i] );

        // Remove all elements.
        vec.clear();
        EXPECT_TRUE( vec.empty() );

        // Insert again.
        for ( size_t i{0} ; i < std::size(values_i) ; ++i )
            vec.emplace_back( values_i[i] );
        EXPECT_FALSE( vec.empty() );
        EXPECT_EQ( vec.size(),  std::size(values_i) );

        // Checking if the vales are right.
        for ( size_t i{0} ; i < std::size(values_i) ; ++i )
            EXPECT_EQ( values_i[i], vec[i] );
    }
#endif

#if EMPLACE_BACK_STRING
    {
        BEGIN_TEST(tm, "Emplace back string", "vec<string>.emplace_back(value)");
        // Starting off with an empty vector.
        which_lib::vector<std::string> vec;

        std::array<std::string,5> values_s{"1","2","3","4","5"};

        EXPECT_TRUE( vec.empty() );
        for ( size_t i{0} ; i < std::size(values_s) ; ++i )
            vec.emplace_back( values_s[i] );
        EXPECT_FALSE( vec.empty() );
        EXPECT_EQ( vec.size(),  std::size(values_s) );

        // Checking if the vales are right.
        for ( size_t i{0} ; i < std::size(values_s) ; ++i )
            EXPECT_EQ( values_s[i], vec[i] );

        // Remove all elements.
        vec.clear();
        EXPECT_TRUE( vec.empty() );

        // Insert again.
        for ( size_t i{0} ; i < std::size(values_s) ; ++i )
            vec.emplace_back( values_s[i] );
        EXPECT_FALSE( vec.empty() );
        EXPECT_EQ( vec.size(),  std::size(values_s) );

        // Checking if the vales are right.
        for ( size_t i{0} ; i < std::size(values_s) ; ++i )
            EXPECT_EQ( values_s[i], vec[i] );
    }
#endif
    tm.summary();
    std::cout << "\n\n";
}

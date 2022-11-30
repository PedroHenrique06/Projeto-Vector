#ifndef _VECTOR_TESTS_H_
#define _VECTOR_TESTS_H_

#include <cstdlib>
#include <iostream>

#include "include/tm/test_manager.h"
#include "../include/vector.h"

// ============================================================================
// TESTING VECTOR AS A CONTAINER OF INTEGERS
// ============================================================================

// Test default ctro's size and capacity initial values.
#define DEFAULT_CTRO YES
// Ctro that receives a size as argument. It crates an empty vector with size elements.
#define CTRO_SIZE YES
// Ctro that receives a list of values as its initial value.
#define LIST_CTRO YES
// Ctro that receives a range of values as its initial value.
#define CTRO_RANGE YES
// Copy Ctro: creates a vector based on another passed in as argument.
#define CTRO_COPY YES
// Assign operator, as in vec1 = vec2;
#define ASSIGN_OP YES
// Initializer list assignment, as in vector<int> vec = { 1, 2, 3 };
#define INITIALISZER_ASSIGNMENT YES
// Size method
#define SIZE YES
// Clear method
#define CLEAR YES
// Push back method
#define PUSH_BACK YES
// Pop back method
#define POP_BACK YES
// Reference front, as in vec.front() = 3;
#define REF_FRONT YES
// Const front, as in x = vec.front();
#define CONST_FRONT YES
// Reference back, as in vec.back() = 3;
#define REF_BACK YES
// Const back, as in x = vec.back();
#define CONST_BACK YES
// Assign `count` elements with `value` to the vector: vec.assign(3,value);
#define ASSIGN_COUNT_VALUES YES
// Const index access operator, as in x = vec[3];
#define CONST_INDEX_OP YES
// Reference index access operator, as in vec[3] = x;
#define REF_INDEX_OP YES
// Const index access operator with bounds check, as in x = vec.at(3);
#define CONST_AT_INDEX YES
// Reference index access operator with bounds check, as in vec.at(3) = x;
#define REF_AT_INDEX YES
// Reserve methos, that increases the vector storage capacity explicitly.
#define RESERVE YES
// Storage capacity of the vector.
#define CAPACITY YES
// Shrink storage memory so that the capacity is the same as the # of elements currently stored.
#define SHRINK YES
// Equality operator
#define EQUAL_OP YES
// Different operator
#define DIFFERENT_OP YES
// Insert a single values before pos
#define INSERT_SINGLE_VALUE YES
// Insert a range of elements before pos
#define INSERT_RANGE YES
// Insert a initializer list of elements before pos
#define INSERT_INITIALIZER YES
// Erase a range of elements begining at pos
#define ERASE_RANGE YES
// Erase a single values at pos
#define ERASE_SINGLE_VALUE YES

/// Tests the basic operations with a vector of integers.
template <typename T, size_t S>
void run_regular_vector_tests( const std::array<T,S>& values, const std::array<T,S>& source )
{
    TestManager tm{ "Testing regular operations on a vector"};

#if DEFAULT_CTRO
    {
        BEGIN_TEST(tm,"DefaultConstructor", "vector<T> vec;");
        // DISABLE();

        which_lib::vector<T> vec;

        EXPECT_EQ( vec.size(), 0);
        EXPECT_EQ( vec.capacity(), 0);
        EXPECT_TRUE( vec.empty() );
    }
#endif

#if CTRO_SIZE
    {
        BEGIN_TEST(tm,"ConstructorSize", "vec(size)");

        which_lib::vector<T> vec(10);

        EXPECT_EQ( vec.size(), 10);
        EXPECT_EQ( vec.capacity(), 10);
        EXPECT_FALSE( vec.empty() );
    }
#endif

#if LIST_CTRO
    {
        BEGIN_TEST(tm,"ListContructor", "vector<T> vec{1, 2, 3}");

        // Calling the constructor based on an anonymous list.
        which_lib::vector<T> vec{ values[0], values[1], values[2], values[3], values[4] };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_FALSE( vec.empty() );

        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( values[i], vec[i] );
    }
#endif

#if CTRO_RANGE
    {
        BEGIN_TEST(tm,"RangeConstructor", "vector<int> vec{first, last}");
        // Range = the entire vector.
        which_lib::vector<T> vec{ values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> vec2{ vec.begin(), vec.end() };

        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec.empty() );

        // Cheking out the if the stored values are the same as in the source vector.
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( values[i], vec[i] );

        // Creating a range that is part of an existing vector.
        auto offset{1};
        which_lib::vector<T> vec3{std::next(vec.begin(),offset), std::next(vec.begin(),3)};
        // which_lib::vector<T> vec3{vec.begin()+offset, vec.begin()+3};
        EXPECT_EQ( vec3.size(), 2 );
        EXPECT_FALSE( vec3.empty() );

        // Cheking out the if the stored values are the same as in the source vector.
        for( auto i{0u} ; i < vec3.size() ; ++i )
            EXPECT_EQ( vec[i+offset], vec3[i] );
    }
#endif

#if CTRO_COPY
    {
        BEGIN_TEST(tm, "CopyConstructor","vector<int> vec_clone{ vec }");

        // Original values for later conference.
        which_lib::vector<T> vec{ values[0], values[1], values[2], values[3], values[4] };
        // Creating a copy of the original source vector
        which_lib::vector<T> vec2{ vec };

        // Checking out the vector internal state.
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_EQ( vec2.capacity(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // Check whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( values[i], vec2[i] );

        // Change the source vector and check whether that also changes the second vec.
        // Of course, this should not happen.
        vec[0] = 10;
        vec[1] = 20;
        vec[2] = 30;
        vec[3] = 40;
        vec[4] = 50;
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( values[i], vec2[i] );
    }
#endif

#if ASSIGN_OP
    {
        BEGIN_TEST(tm, "AssignOperator", "vec1 = vec2");
        // Source vector
        which_lib::vector<T> vec{ values[0], values[1], values[2], values[3], values[4] };
        // Destination vector
        which_lib::vector<T> vec2;

        vec2 = vec; // Assigning here.

        // Internal state.
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_EQ( vec2.capacity(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // CHeck whether the assignment worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( values[i], vec2[i] );
    }
#endif

#if INITIALISZER_ASSIGNMENT
    {
        BEGIN_TEST(tm, "ListInitializerAssign", "vector<int> vec = { 1, 2, 3 }");
        // Assignind initial values.
        which_lib::vector<T> vec = { values[0], values[1], values[2], values[3], values[4] };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_FALSE( vec.empty() );

        // Check whether the copy worked.
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( values[i], vec[i] );
    }
#endif

#if SIZE
    {
        BEGIN_TEST(tm, "Size", "vec.size()");

        // Assignind initial values.
        which_lib::vector<T> vec = { values[0], values[1], values[2], values[3], values[4] };
        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        vec.clear();
        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 5 );

        size_t final_len{std::size(source)}; // The final length of array.
        which_lib::vector<T> vec2;
        EXPECT_EQ( vec2.size(), 0 );
        for( auto i{0u} ; i < final_len ; ++i )
        {
            vec2.push_back(source[i]);
            EXPECT_EQ( vec2.size(), i+1 );
        }

        which_lib::vector<T> vec3(vec2);
        EXPECT_EQ( vec3.size(), final_len );

        vec3.pop_back();
        vec3.pop_back();
        EXPECT_EQ( vec3.size(), final_len-2 );
        while(not vec3.empty())
            vec3.pop_back();
        EXPECT_EQ( vec3.size(), 0 );
    }
#endif

#if CLEAR
    {
        BEGIN_TEST(tm, "Clear", "vec.clear()");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_FALSE( vec.empty() );

        vec.clear();

        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_TRUE( vec.empty() );
    }
#endif

#if PUSH_BACK
    {
        BEGIN_TEST(tm, "PushBack", "vec.push_back(value)");
        // Starting off with an empty vector.
        which_lib::vector<T> vec;

        EXPECT_TRUE( vec.empty() );
        for ( auto i{0} ; i < std::size(values) ; ++i )
            vec.push_back( values[i] );
        EXPECT_FALSE( vec.empty() );
        EXPECT_EQ( vec.size(),  std::size(values) );

        // Checking if the vales are right.
        for ( auto i{0} ; i < std::size(values) ; ++i )
            EXPECT_EQ( values[i], vec[i] );

        // Remove all elements.
        vec.clear();
        EXPECT_TRUE( vec.empty() );

        // Insert again.
        for ( auto i{0} ; i < std::size(values) ; ++i )
            vec.push_back( values[i] );
        EXPECT_FALSE( vec.empty() );
        EXPECT_EQ( vec.size(),  std::size(values) );

        // Checking if the vales are right.
        for ( auto i{0} ; i < std::size(values) ; ++i )
            EXPECT_EQ( values[i], vec[i] );
    }
#endif

#if POP_BACK
    {
        BEGIN_TEST(tm, "PopBack", "vec.pop_back()");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        while( not vec.empty() )
        {
            vec.pop_back();
            // Check whether we have the same list except for the last.
            for( auto i{0u} ; i < vec.size() ; ++i )
                EXPECT_EQ( values[i], vec[i] );
        }
    }
#endif

#if REF_FRONT
    {
        BEGIN_TEST(tm, "Front", "reference front() version: vec.front() = x");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        T target_value{source[0]};
        auto i{0};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.front(), values[i++] );
            vec.front() = target_value; // Changing the first elemento with front().
            EXPECT_EQ( current_size, vec.size() );
            EXPECT_EQ( vec[0], target_value );

            // Remove the first element of the vector.
            vec.erase(vec.begin());
        }
    }
#endif

#if CONST_FRONT
    {
        BEGIN_TEST(tm, "FrontConst","const front() version: x = vec.front()");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        EXPECT_EQ( vec.front(), values[0] );

        auto i{0};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.front(), values[i++] );
            EXPECT_EQ( current_size, vec.size() );
            // Remove the first element of the vector.
            vec.erase(vec.begin());
        }
    }
#endif

#if REF_BACK
    {
        BEGIN_TEST(tm, "Back","reference back() version: vec.back() = x");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        T target_value{source[0]};
        auto i{std::size(values)};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.back(), values[--i] );
            vec.back() = target_value; // Changing the first elemento with front().
            EXPECT_EQ( current_size, vec.size() );
            EXPECT_EQ( vec[i], target_value );
            // Remove the first element of the vector.
            vec.pop_back();
        }
    }
#endif

#if CONST_BACK
    {
        BEGIN_TEST(tm, "BackConst","const back() version: x = vec.back()");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        auto i{std::size(values)};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.back(), values[--i] );
            EXPECT_EQ( current_size, vec.size() );
            // Remove the first element of the vector.
            vec.pop_back();
        }
    }
#endif

#if ASSIGN_COUNT_VALUES
    {
        BEGIN_TEST(tm, "AssignCountValue","Assign count value: vec.assign(3, value)");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        EXPECT_EQ( vec.size(), std::size(values) );
        auto original_cap = vec.capacity();

        // Test assign with a count SMALLER than the original vec size.
        T target_value{source[0]};
        vec.assign( size_t(3), target_value ); // 3 < 5 
        EXPECT_EQ( vec.size(), 3 );
        // Capacity should be the same, because we do not need to allocate new memory.
        EXPECT_EQ( vec.capacity(), original_cap );
        // Verify the elements.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( target_value, vec[i] );

        // Test assign with a count GREATER than the original vec size.
        target_value = source[1];
        vec.assign( size_t(10), target_value ); // 10 > 5
        EXPECT_EQ( vec.size(), 10 );
        EXPECT_GE( vec.capacity(), original_cap );
        // Verify the elements.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( target_value, vec[i] );
    }
#endif

#if CONST_INDEX_OP
    {
        BEGIN_TEST(tm, "OperatorBracketsRHS","Operator Brackets RHS: x = vec[i]");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        // Assign all values from vec to vec2.
        for ( auto i{0u} ; i < vec.size() ; ++i )
        {
            auto x = vec[i];
            EXPECT_EQ( x, vec[i]); // Are they the same?
        }
    }
#endif


#if REF_INDEX_OP
    {
        BEGIN_TEST(tm, "OperatorBracketsLHS","Operator Brackets LHS: vec[i] = x");
        // Creating a vector with a few elements.
        const which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> vec2(std::size(values)); // Same capacity as above.

        // Assign all values from vec to vec2.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            vec2[i] = vec[i]; // Assigning here.

        // Checking if they are equal.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec[i], vec2[i]); // Are they the same?
    }
#endif

#if CONST_AT_INDEX
    {
        BEGIN_TEST(tm, "AtRHS","at() as RHS: x = vec.at(i);");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        // Just accessing the element.
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec.at(i), values[i] );

        // Testing exception throwing.
        bool worked{false};
        try { vec.at( 40 ); }
        catch( std::out_of_range & e )
        { worked = true; }
        EXPECT_TRUE( worked );
    }
#endif

#if REF_AT_INDEX
    {
        BEGIN_TEST(tm, "AtLHS","at() as a LHS: vec.at(i) = x;");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec(std::size(values));// Creating an "empty" vector with some capacity.

        // Chaging internal values with the at()
        for ( auto i{0u} ; i < vec.size() ; ++i )
            vec.at(i) = values[i];
        // Did the assignment via at() work?
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec[i], values[i] );

        // Testing exception throwing.
        bool worked{false};
        auto target_value{source[0]};
        try { vec.at( vec.size() ) = target_value; }
        catch( std::out_of_range & e )
        { worked = true; }
        EXPECT_TRUE( worked );
    }
#endif

#if RESERVE
    {
        BEGIN_TEST(tm, "Reserve","reserve()");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        EXPECT_EQ( vec.capacity(), 5u ); // Initial capacity
        vec.reserve(10); // Increasing
        EXPECT_EQ( vec.capacity(), 10u );
        vec.reserve(3); // Nothing happens here.
        EXPECT_EQ( vec.capacity(), 10u );

        // Making sure the original elements are still there.
        // NOTE that we do not traverse until the vectors capacity,
        // rather we only test the elements inserted on the creation.
        for ( auto i{0u} ; i < std::size(values) ; ++i )
            EXPECT_EQ( vec[i], values[i] );
    }
#endif

#if CAPACITY
    {
        BEGIN_TEST(tm, "Capacity","capacity()");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        EXPECT_EQ( vec.capacity(), 5u );

        which_lib::vector<T> vec2{ vec };
        EXPECT_EQ( vec2.capacity(), 5u );

        which_lib::vector<T> vec3;
        EXPECT_EQ( vec3.capacity(), 0u );

        vec3 = vec2;
        EXPECT_EQ( vec2.capacity(), 5u );

        which_lib::vector<T> vec4 = { values[0], values[1], values[2]};
        EXPECT_EQ( vec4.capacity(), 3u );

        which_lib::vector<T> vec5( 100 );
        EXPECT_EQ( vec5.capacity(), 100u );
    }
#endif

#if SHRINK
    {
        BEGIN_TEST(tm, "ShrinkToFit","shrink_to_fit()");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        // Original cap is 5
        EXPECT_EQ( vec.capacity(), 5u );
        // Remove 2 elements.
        vec.pop_back();
        vec.pop_back();
        // Capacity should be still the same.
        EXPECT_EQ( vec.capacity(), 5u );
        vec.shrink_to_fit();
        // Now, capacity should be smaller.
        EXPECT_EQ( vec.capacity(), 3 );
        // Did we keep the original values?
        for ( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( vec[i], values[i] );
    }
#endif

#if EQUAL_OP
    {
        BEGIN_TEST(tm, "OperatorEqual","vec1 == vec2");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> vec2 { values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> vec3 { values[4], values[3], values[2], values[1], values[0] };
        which_lib::vector<T> vec4 { values[4], values[3], values[2] };

        EXPECT_EQ( vec , vec2 );
        EXPECT_FALSE( vec == vec3 );
        EXPECT_FALSE( vec == vec4 );
    }
#endif

#if DIFFERENT_OP
    {
        BEGIN_TEST(tm, "OperatorDifferent","vec1 != vec2");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> vec2 { values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> vec3 { values[4], values[3], values[2], values[1], values[0] };
        which_lib::vector<T> vec4 { values[4], values[3], values[2] };


        EXPECT_FALSE( vec != vec2 );
        EXPECT_TRUE ( vec != vec3 );
        EXPECT_TRUE ( vec != vec4 );
    }
#endif

#if INSERT_SINGLE_VALUE
    {
        BEGIN_TEST(tm, "InsertSingleValueAtPosition","vec.insert(pos, value)");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };

        // Insert at front
        vec.insert( vec.begin(), values[0] );
        EXPECT_EQ( vec , ( which_lib::vector<T>{ values[0], values[0], values[1], values[2], values[3], values[4] } ) );
        // Insert in the middle
        vec.insert( vec.begin()+3, values[4] );
        EXPECT_EQ( vec , ( which_lib::vector<T>{ values[0], values[0], values[1], values[4], values[2], values[3], values[4] } ) );
        // Insert at the end
        vec.insert( vec.end(), values[2] );
        EXPECT_EQ( vec , ( which_lib::vector<T>{ values[0], values[0], values[1], values[4], values[2], values[3], values[4], values[2]  } ) );
    }
#endif

#if INSERT_RANGE
    {
        BEGIN_TEST(tm, "InsertRange","vec.insert( pos, first, last)"); // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        auto backup{vec};
        which_lib::vector<T> src{ source[0], source[1], source[2], source[3], source[4] };
        which_lib::vector<T> expect1{ source[0], source[1], source[2], source[3], source[4],
                                        values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> expect2{ values[0], values[1], 
                                        source[0], source[1], source[2], source[3], source[4],
                                        values[2], values[3], values[4] };
        which_lib::vector<T> expect3{ values[0], values[1], values[2], values[3], values[4],
                                        source[0], source[1], source[2], source[3], source[4] };

        // Insert at the begining.
        vec.insert( vec.begin(), src.begin(), src.end() );
        EXPECT_EQ( vec , expect1 ); 

        // In the middle
        vec = backup;
        vec.insert( vec.begin()+2, src.begin(), src.end() );
        EXPECT_EQ( vec , expect2 ); 

        // At the end
        vec = backup;
        vec.insert( vec.end(), src.begin(), src.end() );
        EXPECT_EQ( vec , expect3 ); 
    }
#endif

#if INSERT_INITIALIZER
    {
        BEGIN_TEST(tm, "InsertInitializarList","vec.insert(pos, {1, 2, 3, 4 })");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        auto backup{vec};
        which_lib::vector<T> src{ source[0], source[1], source[2], source[3], source[4] };
        which_lib::vector<T> expect1{ source[0], source[1], source[2], source[3], source[4],
                                        values[0], values[1], values[2], values[3], values[4] };
        which_lib::vector<T> expect2{ values[0], values[1], 
                                        source[0], source[1], source[2], source[3], source[4],
                                        values[2], values[3], values[4] };
        which_lib::vector<T> expect3{ values[0], values[1], values[2], values[3], values[4],
                                        source[0], source[1], source[2], source[3], source[4] };

        // Insert at the begining.
        vec.insert( vec.begin(), {source[0], source[1], source[2], source[3], source[4] } );
        EXPECT_EQ( vec , expect1 ); 

        // In the middle
        vec = backup;
        vec.insert( vec.begin()+2, {source[0], source[1], source[2], source[3], source[4] }  );
        EXPECT_EQ( vec , expect2 ); 

        // At the end
        vec = backup;
        vec.insert( vec.end(), {source[0], source[1], source[2], source[3], source[4] }  );
        EXPECT_EQ( vec , expect3 ); 
    }
#endif

#if ERASE_RANGE
    {
        BEGIN_TEST(tm, "EraseRange","vec.erase(first, last)");
        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        auto backup{vec};
        which_lib::vector<T> expect1{ values[3], values[4] };
        which_lib::vector<T> expect2{ values[0], values[4] };
        which_lib::vector<T> expect3{ values[0], values[1] };

        // removing a segment from the beginning.
        auto past_last = vec.erase( vec.begin(), vec.begin()+3 );
        EXPECT_EQ( vec.begin() , past_last );
        EXPECT_EQ( vec , expect1 );
        // std::cout << *past_last <<" "<< *vec.begin()<< endl;
        EXPECT_EQ( vec.size() , 2 );

        // removing at the middle.
        vec = backup;
        past_last = vec.erase( vec.begin()+1, vec.begin()+4 );
        EXPECT_EQ( vec.begin()+1 , past_last );
        EXPECT_EQ( vec , expect2 );
        EXPECT_EQ( vec.size() , 2 );

        // removing a segment that reached the end.
        vec = backup;
        past_last = vec.erase( vec.begin()+2, vec.end() );
        EXPECT_EQ( vec.end() , past_last );
        EXPECT_EQ( vec , expect3 );
        EXPECT_EQ( vec.size() , 2 );

        // removing the entire vector.
        vec = backup;
        past_last = vec.erase( vec.begin(), vec.end() );
        EXPECT_EQ( vec.end() , past_last );
        EXPECT_TRUE( vec.empty() );
    }
#endif

#if ERASE_SINGLE_VALUE
    {
        BEGIN_TEST(tm, "ErasePos","vec.erase(pos)");

        // Creating a vector with a few elements.
        which_lib::vector<T> vec { values[0], values[1], values[2], values[3], values[4] };
        auto backup{vec};
        which_lib::vector<T> expect1{ values[1], values[2], values[3], values[4] };
        which_lib::vector<T> expect2{ values[0], values[1], values[3], values[4] };
        which_lib::vector<T> expect3{ values[0], values[1], values[2], values[3] };

        // removing a single element.
        auto past_last = vec.erase( vec.begin() );
        EXPECT_EQ( vec , expect1 );
        EXPECT_EQ( vec.begin() , past_last );
        EXPECT_EQ( vec.size() , 4 );

        // removing a single element in the middle.
        vec = backup;
        past_last = vec.erase( vec.begin()+2 );
        EXPECT_EQ( vec , expect2 );
        EXPECT_EQ( vec.begin()+2 , past_last );
        EXPECT_EQ( vec.size() , 4 );

        // removing a single element at the end.
        vec = backup;
        past_last = vec.erase( vec.begin()+vec.size()-1 );
        EXPECT_EQ( vec , expect3 );
        EXPECT_EQ( vec.end() , past_last );
        EXPECT_EQ( vec.size() , 4 );
    }
#endif

    tm.summary();
    std::cout << "\n\n";
}

#endif

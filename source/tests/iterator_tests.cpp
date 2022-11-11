#include<iostream>
#include<vector>

#include "include/tm/test_manager.h"
#include "../include/vector.h"
#include "main.h"


// =============================================================
// Second batch of tests, focused on the iterator interface
// =============================================================

// Test begin() method that should return a iterator to the first element in the container.
#define BEGIN YES
// Test cbegin() method that should return a const iterator to the first element in the container.
#define CBEGIN YES
// Test end() method that should return a iterator to a location just past the last elemento of a container.
#define END YES
// Test cend() method that should return a const iterator to a location just past the last elemento of a container.
#define CEND YES
// Pre-increment operator. ++it
#define PRE_INC YES
// Post-increment operator. it++
#define POST_INC YES
// Pre-decrement operator. --it
#define PRE_DEC YES
// Post-decrement operator. it--
#define POST_DEC YES
// Dreference operator. *it
#define DEREFERENCE YES
// Differentre between iterators. it1 - it2
#define DIFFERENCE YES
// Add a offset to a iterator. offset + it
#define ADD_OFFSET_IT YES
// Add an iterator and an offset. it + offset
#define ADD_IT_OFFSET YES
// Subtract an iterator and an offset. it - offset
#define SUB_IT_OFFSET YES
// Self addition iterator and offset. it += 0ffset
#define SELF_ADD_IT_OFFSET YES
// Self subtraction iterator and offset. it -= 0ffset
#define SELF_SUB_IT_OFFSET YES
// Less operator. it1 < it2
#define LESS YES
// Greater operator. it1 > it2
#define GREATER YES
// Less equal operator. it1 <= it2
#define LESS_EQ YES
// Greater equal operator. it1 >= it2
#define GREATER_EQ YES
// Equal operator. it1 == it2
#define EQUAL YES
// Different operator. it1 != it2
#define DIFFERENT YES


void run_iterator_tests( void )
{
    TestManager tm{ "Iterator testing"};

#if BEGIN
    {
        BEGIN_TEST(tm, "begin","vec.begin()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        EXPECT_EQ( *it , vec[0] );

        auto vec2 = vec;
        vec2[0] = 100; // Changing the copy
        it = vec2.begin();
        EXPECT_NE( *it , vec[0] );
        EXPECT_EQ( *it , vec2[0] );

        auto vec3 { vec };
        vec3[0] = 200; // Changing the copy
        it = vec3.begin();
        EXPECT_NE( *it , vec[0] );
        EXPECT_EQ( *it , vec3[0] );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        it = vec4.begin();
        EXPECT_EQ( *it , vec4[0] );
    }
#endif

#if CBEGIN
    {
        BEGIN_TEST(tm, "cbegin","vec.cbegin()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto cit = vec.cbegin();
        EXPECT_EQ( *cit , vec[0] );

        auto vec2 = vec;
        vec2[0] = 100; // Changing the copy
        cit = vec2.cbegin();
        EXPECT_NE( *cit , vec[0] );
        EXPECT_EQ( *cit , vec2[0] );

        auto vec3 { vec };
        vec3[0] = 200; // Changing the copy
        cit = vec3.cbegin();
        EXPECT_NE( *cit , vec[0] );
        EXPECT_EQ( *cit , vec3[0] );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        cit = vec4.cbegin();
        EXPECT_EQ( *cit , vec4[0] );
    }
#endif

#if END
    {
        BEGIN_TEST(tm, "end","vec.end()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end();
        EXPECT_EQ( *it , vec[vec.capacity()] );

        auto vec2 = vec;
        it = vec2.end();
        EXPECT_NE( it , vec.end() );
        EXPECT_EQ( it , vec2.end() );

        auto vec3 { vec };
        it = vec3.end();
        EXPECT_NE( it , vec.end() );
        EXPECT_EQ( it , vec3.end() );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        it = vec4.end();
        EXPECT_EQ( it , vec4.end() );
    }
#endif

#if CEND
    {
        BEGIN_TEST(tm, "cend","vec.cend()");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.cend();
        EXPECT_EQ( it , vec.cend() );

        auto vec2 = vec;
        it = vec2.cend();
        EXPECT_NE( it , vec.cend() );
        EXPECT_EQ( it , vec2.cend() );

        auto vec3 { vec };
        it = vec3.cend();
        EXPECT_NE( it , vec.cend() );
        EXPECT_EQ( it , vec3.cend() );

        which_lib::vector<int> vec4 =  { 1, 2, 4, 5, 6 };
        it = vec4.cend();
        EXPECT_EQ( it , vec4.cend() );
    }
#endif

#if PRE_INC
    {
        BEGIN_TEST(tm, "operator++()","Preincrement, ++it");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        size_t i{0};
        while( it != vec.end() )
        {
            // same address
            EXPECT_EQ( *it , vec[i++] );
            ++it;
        }
    }
#endif

#if POST_INC
    {
        BEGIN_TEST(tm, "operator++(int)","Postincrement, it++");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        size_t i{0};
        while( it != vec.end() )
        {
            // same address
            EXPECT_EQ( *it , vec[i++] );
            it++;
        }
    }
#endif

#if PRE_DEC
    {
        BEGIN_TEST(tm, "operator--()","Predecrement, --it");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end();
        size_t i{vec.capacity()};
        while( it != vec.begin() )
        {
            // std::cout << it << " == " << &vec[i] << "\n";
            // same address
            EXPECT_EQ( *it , vec[i--] );
            --it;
        }
        EXPECT_EQ( *it , vec[i] );
        // std::cout << it << " == " << &vec[i] << "\n";
    }
#endif

#if POST_DEC
    {
        BEGIN_TEST(tm, "operator--(int)","Postdecrement, it--");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end();
        size_t i{vec.capacity()};
        while( it != vec.begin() )
        {
            // same address
            EXPECT_EQ( *it , vec[i--] );
            it--;
        }
        EXPECT_EQ( *it , vec[i] );
    }
#endif

#if DEREFERENCE
    {
        BEGIN_TEST(tm, "operator*()"," x = *it1");

        which_lib::vector<int> vec { 1, 2, 3, 4, 5, 6 };

        auto it = vec.begin();
        int i{1};
        while( it != vec.end() )
            EXPECT_EQ( *it++ , i++ );
    }
#endif

#if DIFFERENCE
    {
        BEGIN_TEST(tm, "operator-()","it1 - it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.begin();
        ptrdiff_t i{0};
        while( it1 != vec.end() )
        {
            // same address
            EXPECT_EQ( it1-it2 , i );
            i++;
            it1++;
        }
    }
#endif

#if ADD_OFFSET_IT
    {
        BEGIN_TEST(tm, "operator+(int, iterator)","it = 2 + it");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            // same address
            EXPECT_EQ( *(i+it) , vec[i] );
            // std::cout << (i+it) << " == " << &vec[i] << "\n";
        }
    }
#endif

#if ADD_IT_OFFSET
    {
        BEGIN_TEST(tm, "operator+(iterator, int)","it = it + 2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.begin();
        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            // same address
            EXPECT_EQ( *(it+i) , vec[i] );
            // std::cout << (i+it) << " == " << &vec[i] << "\n";
        }
    }
#endif

#if SUB_IT_OFFSET
    {
        BEGIN_TEST(tm, "operator-(iterator, int)","it = it - 2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it = vec.end()-1;
        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            // same address
            EXPECT_EQ( *(it-i) , vec[vec.size()-i-1] );
        }
    }
#endif

#if SELF_ADD_IT_OFFSET
    {
        BEGIN_TEST(tm, "operator+=()","it += n");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            auto it = vec.begin();
            it += i;
            // same address
            EXPECT_EQ( *it , vec[i] );
        }
    }
#endif

#if SELF_SUB_IT_OFFSET
    {
        BEGIN_TEST(tm, "operator-=()","it -= n");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        for( size_t i{0} ; i < vec.size() ; ++i )
        {
            auto it = vec.end();
            it -= (vec.size()-i);
            // same address
            EXPECT_EQ( *it , vec[i] );
        }
    }
#endif

#if LESS
    {
        BEGIN_TEST(tm, "operator<()","it1 < it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.end();
        while( it1 != vec.end() ){
            EXPECT_TRUE(it1<it2);
            ++it1;
        }
    }
#endif

#if GREATER
    {
        BEGIN_TEST(tm, "operator>()","it1 > it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.end();
        while( it1 != vec.end() ){
            EXPECT_TRUE(it2>it1);
            ++it1;
        }
    }
#endif

#if LESS_EQ
    {
        BEGIN_TEST(tm, "operator<=()","it1 <= it2");

        which_lib::vector<int> vec { 1, 2, 3, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.end();
        while( it1 != vec.end() ){
            EXPECT_TRUE(it1<=it2);
            ++it1;
        }
    }
#endif

#if GREATER_EQ
    {
        BEGIN_TEST(tm, "operator>=()","it1 >= it2");

        which_lib::vector<int> vec { 1, 2, 3, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.end();
        while( it1 != vec.end() ){
            //std::cout << "it1 = " << *it1 << '\n';
            EXPECT_TRUE(it2>=it1);
            ++it1;
        }
    }
#endif

#if EQUAL
    {
        BEGIN_TEST(tm, "operator==()","it1 == it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.begin();
        while( it1 != vec.end() )
            EXPECT_EQ( it1++ , it2++ );
    }
#endif

#if DIFFERENT
    {
        BEGIN_TEST(tm, "operator!=()","it1 != it2");

        which_lib::vector<int> vec { 1, 2, 4, 5, 6 };

        auto it1 = vec.begin();
        auto it2 = vec.end();
        while( it1 != it2 )
        {
            EXPECT_TRUE( it1 != it2 );
            ++it1;
        }
        EXPECT_FALSE( it1 != it2 );
    }
#endif

    tm.summary();
}

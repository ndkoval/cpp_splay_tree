#ifndef SPLAY_CPP
#define SPLAY_CPP

#include <cstdlib>
#include <iostream>

//If
template<bool Condition, typename TrueResult, typename FalseResult>
struct IF;

template<typename TrueResult, typename FalseResult>
struct IF<true, TrueResult, FalseResult>
{
    typedef TrueResult result;
};

template<typename TrueResult, typename FalseResult>
struct IF<false, TrueResult, FalseResult>
{
    typedef FalseResult result;
};

//Check for same
template<typename A, typename B>
struct is_same
{
    static bool const result = false;
};

template<typename C>
struct is_same<C, C>
{
    static bool const result = true;
};

//defined empty tree
struct nil
{
};

//Constant
template<int Value>
struct constant
{
    static int const value = Value;
};

//Tree node
template<typename Data, typename Left, typename Right>
struct node
{
    typedef Data data;
    typedef Left left;
    typedef Right right;
};

//Tree methods

//Zig
//Zig-Zig
//Zig-Zag
//find
//merge
//split
//add
//remove

template<typename X>
struct zig<nil, X>
{
    typedef nil result;
};

//Tree size
template<typename Tree>
struct size
{
    static size_t const result = 1 + size<typename Tree::left>::result + size<typename Tree::right>::result;
};

template<>
struct size<nil>
{
    static size_t const result = 0;
};

template<typename Tree>
void print_tree()
{
    std::cout << " (";
    std::cout << Tree::data::value;
    print_tree<typename Tree::left>();
    print_tree<typename Tree::right>();
    std::cout << ")";
}

template<>
void print_tree<nil>()
{
    std::cout << " ()";
}

#endif



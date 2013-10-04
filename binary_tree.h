#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdlib>
#include <iostream>

#include "tools.h"

//defined empty tree
struct nil
{
    typedef nil left, right, data;
};

//Tree node
template<typename Data, typename Left, typename Right>
struct node
{
    typedef Data data;
    typedef Left left;
    typedef Right right;
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

//Find element
template<typename Tree, typename Value>
struct find
{
    typedef typename IF<Value::value == Tree::data::value,
        Tree,
        typename IF<(Value::value < Tree::data::value),
            typename find<typename Tree::left, Value>::result,
            typename find<typename Tree::right, Value>::result
        >::result
    >::result result;
};

template<typename Value>
struct find<nil, Value>
{
    typedef nil result;
};

//Is child
template<typename Tree, typename X>
struct is_child
{
    static bool const result = is_same<typename Tree::left, X>::result || is_same<typename Tree::right, X>::result;
};

template<typename X>
struct is_child<nil, X>
{
    static bool const result = false;
};

//Turn left rib
template<typename Tree>
struct turn_left_rib
{
    typedef node<typename Tree::left::data,
        typename Tree::left::left,
        node<typename Tree::data,
            typename Tree::left::right,
            typename Tree::right
        >
    > result;
};

//Turn right rib
template<typename Tree>
struct turn_right_rib
{
    typedef node<typename Tree::right::data,
        node<typename Tree::data,
            typename Tree::left,
            typename Tree::right::left
        >,
        typename Tree::right::right
    > result;
};

//Print tree to standart output
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

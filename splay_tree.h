#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <cstdlib>
#include <iostream>

#include "tools.h"
#include "binary_tree.h"

//Zig
template<typename Tree, bool is_left>
struct zig
{
    typedef typename IF<is_left,
        typename turn_left_rib<Tree>::result,
        typename turn_right_rib<Tree>::result
    >::result result;
};

//Zig-Zig
template<typename Tree, bool is_left>
struct zig_zig
{
    typedef typename IF<is_left,
        typename turn_left_rib<typename turn_left_rib<Tree>::result>::result,
        typename turn_right_rib<typename turn_right_rib<Tree>::result>::result
    >::result result;
};

//Zig-Zag
template<typename Tree, bool is_left>
struct zig_zag
{
    typedef typename IF<is_left,
        typename turn_left_rib<
            node<typename Tree::data,
                typename turn_right_rib<typename Tree::left>::result,
                typename Tree::right
            >
        >::result,
        typename turn_right_rib<
            node<typename Tree::data,
                typename Tree::left,
                typename turn_left_rib<typename Tree::right>::result
            >
        >::result
    >::result result;
};

//Splay
template<typename Tree, typename X>
struct splay
{
    typedef typename IF<is_child<Tree, X>::result,
        typename zig<Tree, is_same<typename Tree::left, X>::result >::result,
        typename IF<is_child<typename Tree::left, X>::result,
            typename IF<is_same<typename Tree::left::left, X>::result,
                typename zig_zig<Tree, true>::result,
                typename zig_zag<Tree, true>::result
            >::result,
            typename IF<is_child<typename Tree::right, X>::result,
                typename IF<is_same<typename Tree::right::left, X>::result,
                    typename zig_zag<Tree, false>::result,
                    typename zig_zig<Tree, false>::result
                >::result,
                typename IF<(X::data::value < Tree::data::value),
                    node<typename Tree::data,
                        typename splay<typename Tree::left, X>::result,
                        typename Tree::right
                    >,
                    node<typename Tree::data,
                        typename Tree::left,
                        typename splay<typename Tree::right, X>::result
                    >
                >::result
            >::result
        >::result
    >::result result;
};

template<typename X>
struct splay<nil, X>
{
    typedef nil result;
};

//Maximum
template<typename Tree>
struct max
{
    typedef typename IF<is_same<typename Tree::right, nil>::result,
        Tree,
        typename max<typename Tree::right>::result
    >::result result;
};

//Merge
template<typename Tree1, typename Tree2>
struct merge
{
private:
    typedef typename splay<Tree1, typename max<Tree1>::result>::result splaied_tree1;
public:
    typedef node<typename splaied_tree1::data,typename splaied_tree1::left, Tree2> result;
};

template<typename Tree1>
struct merge<Tree1, nil>
{
    typedef Tree1 result;
};

template<typename Tree2>
struct merge<nil, Tree2>
{
    typedef Tree2 result;
};

//Split
template<typename Tree, typename X>
struct split
{
private:
    typedef typename splay<Tree, X>::result splaied_tree;
    static bool const root_is_less = (X::value <= splaied_tree::data::value);
public:
    typedef typename IF<root_is_less,
        node<typename Tree::data,
            typename Tree::left,
            nil
        >,
        typename Tree::left
    >::result tree1;

    typedef typename IF<root_is_less,
        typename Tree::right,
        node<typename Tree::data,
            nil,
            typename Tree::right
        >
    >::result tree2;
};

template<typename Tree>
struct split<Tree, nil>
{
    typedef Tree tree1;
    typedef nil tree2;
};

template<typename X>
struct split<nil, X>
{
    typedef nil tree1, tree2;
};

//Add
template<typename Tree, typename Value>
struct add
{
    typedef node<Value,
        typename split<Tree, Value>::tree1,
        typename split<Tree, Value>::tree2
    > result;
};

//Remove
template<typename Tree, typename X>
struct remove
{
private:
    typedef typename splay<Tree, X>::result splaied_tree;
public:
    typedef typename merge<typename splaied_tree::left, typename splaied_tree::right>::result result;
};

#endif



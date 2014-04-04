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
struct splay_even
{
    typedef typename IF<(X::value < Tree::data::value),
        IF<(X::value < Tree::left::data::value), // at left side
            zig_zig< // at left left
                node<typename Tree::data,
                    node<typename Tree::left::data,
                        typename splay_even<typename Tree::left::left, X>::result,
                        typename Tree::left::right
                    >,
                    typename Tree::right
                >,
                true
            >,
            zig_zag< // at left right
                node<typename Tree::data,
                    node<typename Tree::left::data,
                        typename Tree::left::left,
                        typename splay_even<typename Tree::left::right, X>::result
                    >,
                    typename Tree::right
                >,
                true
            >
        >,
        IF<(X::value < Tree::right::data::value), // at right side
            zig_zag< // at right left
                node<typename Tree::data,
                    typename Tree::left,
                    node<typename Tree::right::data,
                        typename splay_even<typename Tree::right::left, X>::result,
                        typename Tree::right::right
                    >
                >,
                false
            >,
            zig_zig< // at right right
                node<typename Tree::data,
                    typename Tree::left,
                    node<typename Tree::right::data,
                        typename Tree::right::left,
                        typename splay_even<typename Tree::right::right, X>::result
                    >
                >,
                false
            >
        >
    >::result::result::result result;
};

template<typename Tree>
struct splay_even<Tree, typename Tree::data>
{
    typedef Tree result;
};

template<typename X>
struct splay_even<nil, X>
{
    typedef nil result;
};

template<typename Tree>
struct splay_even<Tree, nil>
{
    typedef Tree result;
};

template<typename Tree, typename X>
struct splay
{
private:
    typedef typename find<Tree, X>::result::data Y;
public:
    typedef typename IF<(depth<Tree, Y>::result % 2 == 0),
        splay_even<Tree, Y>,
        IF<(X::value < Tree::data::value),
            typename zig<
                node<typename Tree::data,
                    typename splay_even<typename Tree::left, Y>::result,
                    typename Tree::right
                >,
                true
            >::result,
            typename zig<
                node<typename Tree::data,
                    typename Tree::left,
                    typename splay_even<typename Tree::right, Y>::result
                >,
                false
            >::result
        >
    >::result::result result;
};

//Merge
template<typename Tree1, typename Tree2>
struct merge
{
private:
    typedef typename splay<Tree1, typename max<Tree1>::result::data>::result splaied_tree1;
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
    static bool const root_is_less = (splaied_tree::data::value <= X::value);
public:
    typedef typename IF<root_is_less,
        node<typename splaied_tree::data,
            typename splaied_tree::left,
            nil
        >,
        typename splaied_tree::left
    >::result tree1;

    typedef typename IF<root_is_less,
        typename splaied_tree::right,
        node<typename splaied_tree::data,
            nil,
            typename splaied_tree::right
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



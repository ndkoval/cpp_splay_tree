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

//Equals
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
    typedef nil left, right, data;
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

/*
 *Tree methods
*/

//Is child
template<typename Tree, typename X>
struct have_child
{
    static bool const result = is_same<typename Tree::left, X>::result || is_same<typename Tree::right, X>::result;
};

template<typename X>
struct have_child<nil, X>
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
    typedef typename IF<have_child<Tree, X>::result,
        typename zig<Tree, is_same<typename Tree::left, X>::result >::result,
        typename IF<have_child<typename Tree::left, X>::result,
            typename IF<is_same<typename Tree::left::left, X>::result,
                typename zig_zig<Tree, true>::result,
                typename zig_zag<Tree, true>::result
            >::result,
            typename IF<have_child<typename Tree::right, X>::result,
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

//Find
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



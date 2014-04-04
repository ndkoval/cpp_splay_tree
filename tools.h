#ifndef TOOLS_H
#define TOOLS_H

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

//Is same
template<typename A, typename B>
struct is_same
{
    static bool const result = false;
};

template<typename A>
struct is_same<A, A>
{
    static bool const result = true;
};

//Constant
template<int Value>
struct constant
{
    static int const value = Value;
};

//True
struct _true
{
    static bool const result = true;
};

//False
struct _false
{
    static bool const result = false;
};

#endif

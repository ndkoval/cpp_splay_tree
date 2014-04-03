#include "splay_tree.h"

int main(int nArgs, char **args)
{
    typedef node<constant<3>,
                node<constant<1>,
                    nil,
                    node<constant<2>,
                        nil,
                        nil
                    >
                >,
                node<constant<5>,
                    node<constant<4>,
                        nil,
                        nil
                    >,
                    node<constant<6>,
                        nil,
                        nil
                    >
                >
            > tree;

    typedef node<constant<-1>,
                nil,
                nil
            > tree2;

    print_tree<tree>();
    std::cout << std::endl;

    typedef merge<tree2, tree>::result merged_tree;
    print_tree<merged_tree>();
    std::cout << std::endl;

    typedef find<merged_tree, constant<4> >::result X;
    print_tree<X>();
    std::cout << std::endl;

    typedef splay<merged_tree, X>::result splay_tree;
    print_tree<splay_tree>();
    std::cout << std::endl;

    return 0;
}

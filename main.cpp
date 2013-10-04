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

    print_tree<tree>();
    typedef find<tree, constant<1> >::result X;
    std::cout << std::endl;
    print_tree<X>();

    typedef splay<tree, X>::result splay_tree;
    std::cout << std::endl;
    print_tree<splay_tree>();

    return 0;
}

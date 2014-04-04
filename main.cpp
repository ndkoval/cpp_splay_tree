#include "splay_tree.h"

int main(int nArgs, char **args)
{
    typedef node<constant<4>,
                node<constant<2>,
                    node<constant<1>,
                        nil,
                        nil
                    >,
                    node<constant<3>,
                        nil,
                        nil
                    >
                >,
                node<constant<7>,
                    node<constant<6>,
                        node<constant<5>,
                            nil,
                            nil
                        >,
                        nil
                    >,
                    node<constant<10>,
                        node<constant<8>,
                            nil,
                            nil
                        >,
                        node<constant<11>,
                            nil,
                            nil
                        >
                    >
                >
            > tree;

    typedef node<constant<-1>,
                nil,
                nil
            > tree2;

    print_tree<tree>();
    std::cout << std::endl;

    typedef find<tree, constant<11> >::result::data X;

    typedef splay<tree, X>::result splay_tree;
    print_tree<splay_tree>();
    std::cout << std::endl;

    return 0;
}

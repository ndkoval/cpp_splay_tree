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

    print_tree<tree>();
    std::cout << std::endl;

    typedef remove<tree, constant<7> >::result t1;

    print_tree<t1>();
    std::cout << std::endl;

    return 0;
}

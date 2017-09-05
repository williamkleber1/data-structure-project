#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include "tree.h"
#define MAX(a , b) a > b ? a : b


int balanced_factor(node *bt);
node* add_avl_node(node *root, int value);
node* balance(node* node);


node* rotate_left(node *bt);
node* rotate_right(node *bt);
int h(node *bt);

#endif // AVL_H_INCLUDED

#include "avl.h"
#include "tree.h"

//Calcula a altura da arvore Binaria
int h(node *bt){
    if (bt == NULL){
        return 0;
    } else {
        int h1=h(bt->left);
        int h2=h(bt->right);
        return 1 + (h1>h2 ? h1 : h2);
    }
}


//calcula o banceamento da arvore
int balanced_factor(node *bt){
    int l= h(bt->left);
    int r= h(bt->right);
    return l-r;
}

//rotaciona para esquerda
node* rotate_left(node *bt){
    node *subtree_root = NULL;
    if (bt != NULL && bt->right != NULL) {
        subtree_root = bt->right;
        bt->right = subtree_root->left;
        subtree_root->left = bt;

    }
    return subtree_root;

}

//rotaciona para direita
node* rotate_right(node *bt){
    node *subtree_root = NULL;
    if (bt != NULL && bt->right != NULL) {
        subtree_root = bt->left;
        bt->left = subtree_root->right;
        subtree_root->right = bt;

    }
    return subtree_root;
}


//balanceia a AVL.
node* balance(node* no){

    if(no==NULL){
        return no;
    }

    no->left=balance(no->left);// funcao chamada recursivamente para todos os nos
    no->right=balance(no->right);

    int f=balanced_factor(no);//fator de balanceamento da arvore


    //ver slide: casos de rotacao
    if (f == 2) {
         node* left_ = no->left;
        if(balanced_factor(left_) == -1){
           left_= rotate_left(left_);
        }
        no=rotate_right(no);
    } else if(f==-2){
         node* right_ = no->right;
        if(balanced_factor(right_) == 1){
           right_=rotate_right(right_);
        }
        no=rotate_left(no);
    }
    return no;
}




//adiciona Node na avl
node *add_avl_node(node *root, int value){
   root=add_node(root,value);
    return balance(root);
}




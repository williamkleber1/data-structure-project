#include "tree.h"

node *create_node(int item){
	node *new_node = (node*) malloc(sizeof(node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->value = item;
	return new_node;
}

void freetree(node* root){
    if(root==NULL){
        return;
    }
    freetree(root->left);
    freetree(root->right);
    free(root);
}


node *add_node(node *root, int value){
	if (root==NULL){
        root=create_node(value);
        return root;
	}

	if (value > root->value){
         root->right=add_node(root->right, value);
    }else if(value < root->value){
        root->left=add_node(root->left, value);
    }

    return root;
}




node *search_(node *root, int item,int* op){
	node *temp;
	temp = root;
	while (temp != NULL) {
        (*op)++;
		if (temp->value == item){
			return temp;
		}
		if (temp->value > item)
            temp = temp->left;
		else
            temp = temp->right;
	}
	return NULL;
}

void pre_order(node *pnode){
	if (pnode != NULL){
		printf("%d ", pnode->value);
		pre_order(pnode->left);
		pre_order(pnode->right);
	}else{
	    printf("NULL ");
	}
}

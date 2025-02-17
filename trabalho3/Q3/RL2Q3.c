#include <stdio.h>
#include <stdlib.h>
/*

Dupla: Thiago Quadros e Cauã Will

*/
#pragma region TREE_HEADER

typedef struct tree_node {
    int key;
    struct tree_node * parent;
    struct tree_node * left;
    struct tree_node * right;
} node;

typedef struct tree {
    node * root;
} tree;

node * createNode(int key) {
    node * x = malloc(sizeof(node));
    x->key = key;
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    return x;
}

tree * new_tree() {
    tree * tree = malloc(sizeof(tree));
    tree->root = NULL;
    return tree;
}

node * tree_minimum(node * x) {
    while(x->left != NULL)
        x = x->left;
    return x;
}

node * tree_maximum(node * x) {
    while(x->right != NULL)
        x = x->right;
    return x;
}

node * tree_search(tree * T, int k) {
    node * x = T->root;
    if(x == NULL)
        return x;
    while(x != NULL && x->key != k) {
        if(x->key > k)
            x = x->left;
        else x = x->right;
    }
    return x;
}

void tree_insert(tree * T, int k) {
    node * z = createNode(k);

    node * x = T->root;
    node * y = NULL;

    while(x != NULL) {
        y = x;
        if(x->key > z->key)
            x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if(y == NULL)
        T->root = z;
    else if(y->key > z->key)
        y->left = z;
    else y->right = z;
}

void tree_transplant(tree * T, node * u, node * v) {
    if(u->parent == NULL)
        T->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else u->parent->right = v;
    if(v != NULL)
        v->parent = u->parent; 
}

int tree_node_heigth(node * x) {
    int heigth  = -1;
    while(x != NULL) {
        x = x->parent;
        heigth = heigth + 1;
    }
    return heigth;
}

void tree_deletion(tree * T, node * z) {
    node * delete_node = z;
    if(z->left == NULL)
        tree_transplant(T, z, z->right);
    else if(z->right == NULL)
        tree_transplant(T, z, z->left);
    else {
        node * y = tree_minimum(z->right);
        if(y != z->right) {
            tree_transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y; 
        }
        tree_transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
}

void tree_inorder(node * root) {
    if(root != NULL) {
        tree_inorder(root->left);
        printf("%d (%d) ", root->key, tree_node_heigth(root));
        tree_inorder(root->right);
    }
}

void delete_tree_nodes(node * root) {
    if(root != NULL) {
        delete_tree_nodes(root->left);
        delete_tree_nodes(root->right);
        free(root);
    }
}

void delete_tree(tree * T) {
    if(T != NULL) {
        delete_tree_nodes(T->root);
        free(T);
    }
}

#pragma endregion

#pragma region FILE_HEADER

int read_first_int_from_file(FILE * fp, int *isFinalOfLine) {
    int factor = 1, sum = 0, stop = 0;
    char c;

    c = fgetc(fp);

    if(c == '-')
        factor = -1;
    else sum += c - '0';

    while(!stop) {
        c = fgetc(fp);
        if(c >= '0' && c <= '9')
            sum = sum * 10 + (c - '0');
        else stop = 1;
    }

    if(c == '\n')
        *isFinalOfLine = 1;

    sum = sum * factor;
    return sum;
}

void tree_inorder_in_file(FILE * fp, node * root, node * maximum) {
    if(root != NULL) {
        tree_inorder_in_file(fp, root->left, maximum);
        if(root != maximum)
            fprintf(fp, "%d (%d) ", root->key, tree_node_heigth(root));
        else fprintf(fp, "%d (%d)", root->key, tree_node_heigth(root));
        tree_inorder_in_file(fp, root->right, maximum);
    }
}
#pragma endregion

#pragma region MAIN
int main() {
    FILE * finput = fopen("L2Q3.in", "r");
    FILE * foutput = fopen("L2Q3.out", "w");

    if(finput == NULL || foutput == NULL) {
        printf("\nError: files cannot be open\n");
        return 1;
    }

    tree * T;
    node * z;
    char mode;
    int key;
    int stop = 0;
    int close = 0;
    int i = 0;

    while(!close) {
        i = 0;    
        stop = 0;
        T = new_tree();
        while(!stop) {
            mode = fgetc(finput);
            
            if(mode == 'a') {
                fgetc(finput);
                key = read_first_int_from_file(finput, &stop);
                tree_insert(T, key);
            }
            else if(mode == 'r') {
                fgetc(finput);
                key = read_first_int_from_file(finput, &stop);
                z = tree_search(T, key);
                if(z != NULL)
                    tree_deletion(T, z);
                else tree_insert(T, key);
            }
            else if(mode == '\n')
                stop = 1;
            else if(mode == EOF) {
                stop = 1;
                close = 1;
            }
        }
        tree_inorder(T->root);
        printf("\n");
        tree_inorder_in_file(foutput, T->root, tree_maximum(T->root));
        if(!close)
            fprintf(foutput,"\n");
        delete_tree(T);
    }

    fclose(finput);
    fclose(foutput);
}

#pragma endregion
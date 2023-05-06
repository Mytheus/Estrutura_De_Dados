#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int inf;
    struct no* filho;
    struct no* irmao;
} no;

no* create_node(int inf) {
    no* node = malloc(sizeof(no));
    node->inf = inf;
    node->filho=NULL;
    node->irmao=NULL;
    return node;
}

no* init_tree(int inf){
    return create_node(inf);
}

no* add_child(no* parent, int inf) {
    if (parent->filho==NULL){
        parent->filho = create_node(inf);
        return parent->filho;
    }
    else{
        no* ptr = parent->filho;
        while (ptr->irmao!=NULL){
            ptr = ptr->irmao;
        }
        ptr->irmao = create_node(inf);
        return ptr->irmao;
    }
}



void insert_node(no* node, int inf, int parentInf){
    if(!node) return;
    if(node->inf==parentInf){
        add_child(node, inf);
    }
    insert_node(node->filho, inf, parentInf);
    insert_node(node->irmao, inf, parentInf);
    return;
}

void print_tree(no* node) {
    if (!node) return;
    printf("%d(", node->inf);
    print_tree(node->filho);
    printf(")");
    print_tree(node->irmao);
}


void add_given_child(no* parent, no* child) {
    if (parent->filho==NULL){
        parent->filho = child;
        return;
    }
    else{
        no* ptr = parent->filho;
        while (ptr->irmao!=NULL){
            ptr = ptr->irmao;
        }
        ptr->irmao = child;
        return;
    }
}

int search(no* node,int inf){
    if (!node) return 0;
    if (node->inf==inf)return 1;
    return search(node->filho, inf)+search(node->irmao, inf)>0;
}

// int contains(no* tree1, no* tree2){
    
// }

no* union_trees(no* tree1, no* tree2) {
    if (!tree1) return NULL;
    no* tree3 = create_node(tree1->inf);
    if(tree1->inf==tree2->inf){
        add_given_child(tree3, tree2->filho);
        return tree3;
    }
    tree3->filho=union_trees(tree1->filho, tree2);
    tree3->irmao=union_trees(tree1->irmao, tree2);
    return tree3;
}




int main() {
    /*
    no* root = create_node('A');
    insert_node(root, 'B', 'A');
    insert_node(root, 'C', 'A');
    insert_node(root, 'D', 'A');
    insert_node(root, 'E', 'A');
    insert_node(root, 'F', 'B');
    insert_node(root, 'G', 'B');
    insert_node(root, 'I', 'F');
    insert_node(root, 'J', 'F');
    insert_node(root, 'K', 'F');
    insert_node(root, 'H', 'D');
    insert_node(root, 'L', 'H');
    insert_node(root, 'M', 'H');
    insert_node(root, 'X', 'H');
    printf("Antes:\n");
    print_tree(root);
    printf("\n");
    no* root2 = create_node('X');
    insert_node(root2, 'Y', 'X');
    insert_node(root2, 'Z', 'X');
    print_tree(root2);
    printf("\nDepois:\n");
    no* root3 = union_trees(root, root2);
    print_tree(root);
    printf("\n");
    print_tree(root2);
    printf("\n");
    print_tree(root3);
    printf("\n");
    */
    no* root = init_tree(12);
    insert_node(root, 24, 12);
    insert_node(root, 98, 12);
    insert_node(root, 2, 12);
    insert_node(root, 11, 12);
    insert_node(root, 28, 98);
    insert_node(root, 20, 24);
    insert_node(root, 77, 24);

    no* root2 = create_node(28);
    insert_node(root2, 8, 28);
    insert_node(root2, 9, 28);
    insert_node(root2, 64, 9);
    print_tree(root);
    printf("\n");
    print_tree(root2);
    printf("\n");
    printf("%d\n", search(root2, 64));
    // print_tree(root);
    // printf("\n");
    // print_tree(root2);
    // printf("\n");
    // printf("%d\n", is_equal(root, root));
    // printf("%d\n", is_equal(root, root2));
    // no* root3 = union_trees(root, root2);
    // print_tree(root3);
    // printf("\n");
    // printf("%d\n", is_equal(root, root3));
    // printf("%d\n", is_equal(root2, root3));
    // no* root2 = create_node(28);
    // insert_node(root2, 8, 28);
    // insert_node(root2, 9, 28);
    // insert_node(root2, 64, 9);
    // printf("Antes:\n");
    // print_tree(root);
    // printf("\n");
    // print_tree(root2);
    // printf("\nDepois:\n");
    // no* root3 = union_trees(root, root2);
    // print_tree(root);
    // printf("\n");
    // print_tree(root2);
    // printf("\n");
    // print_tree(root3);
    // printf("\n");
    return 0;
}
/*
no* intersection_trees(no* tree1, no* tree2) {
    if (tree1 == NULL || tree2 == NULL) {
        return NULL;
    } else {
        no* new_node = create_node(tree1->inf);
        for (int i = 0; i < MAX_CHILDREN; i++) {
            new_node->children[i] = intersection_trees(tree1->children[i], tree2->children[i]);
        }
        return new_node;
    }
}

no* complement_tree(no* tree) {
    if (tree == NULL) {
        return NULL;
    } else {
        no* new_node = create_node(~tree->inf);
        for (int i = 0; i < MAX_CHILDREN; i++) {
            new_node->children[i] = complement_tree(tree->children[i]);
        }
        return new_node;
    }
}
*/
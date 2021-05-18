//
// Created by yura on 04.05.2021.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int number =  1;

Tree *new_tree(Tree* tree){
    tree = (Tree*)malloc(sizeof (Tree));
    tree->node = NULL;
    return tree;
}

////////////////////////////////////////////////////////

List *insert_list(List* list, Info* info){
    if (list == NULL){
        list = (List*)malloc(sizeof (List));
        list->head = info;
        list->tail = info;
        list->n = 1;
    } else{
        list->tail->next_in_list = info;
        list->tail = info;
        info->next_in_list = NULL;
        list->n++;
    }
    return list;
}

Info *insert_to_form_list(Info *info_prev, Info* info){
    while (info_prev->next != NULL){
        info_prev = info_prev->next;
    }
    info_prev->next = info;
    info->next = NULL;
    return info_prev;
}

///////////////////////////////////////////////////////////////////



Node *new_node(Node* node, Info* info, unsigned int axis){
    node = (Node*)malloc(sizeof (Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->location = info->keys[(axis+1)%2];
    node->list = NULL;
    node->list = insert_list(node->list, info);
    return node;
}


void printList(List* list, int offset){
    Info *ptr = list->head;
    Info *info = list->head;
    for (int i = 0; i < number; i++){
        if (ptr != NULL){
            for (int k = 0; k < offset; k++){
                printf("\t");
            }
            printf("[%d;%d] ", info->keys[0], info->keys[1]);
            while (info != NULL){
                printf("(%s, %s) ", info->text1, info->text2);
                info = info->next;
            }
            printf("\n");
            ptr = ptr->next_in_list;
        }
    }
}

//////////////////////////////////////////////////////////////////////////

void print_tree(Node *node, int offset){
    if (node == NULL){
        return;
    } else{
        print_tree(node->left, offset+1);
        show_node(node, offset);
        printf("\n");
        print_tree(node->right, offset+1);
    }
}

void show_node(Node* node, int offset){
    if (node->right == NULL && node->left == NULL){
        printList(node->list, offset);
    } else{
        for (int k = 0; k < offset; k++){
            printf("\t");
        }
        printf("%d", node->location);
    }
}

void show_info(Info* info){
    printf("[%d;%d]", info->keys[0], info->keys[1]);
    while (info != NULL){
        printf(" (%s,%s) ", info->text1, info->text2);
        info = info->next;
    }
}



///////////////////////////////////////////////////////////////////


void node_add(Tree* tree, Info* info){
    if (tree->node == NULL){
        tree->node = new_node(tree->node, info, 1);
    } else{
        add_no_null(tree->node, info , 0);
    }
}

void add_no_null(Node* node, Info* info, unsigned int depth){
    unsigned int axis = depth%2;
    if (info->keys[axis] >= node->location){
        if (node->right == NULL && node->list->head->keys[axis] != info->keys[axis]){
            node->right = new_node(node->right, info, depth);
            node->right->parent = node;
        } else if (node->list->head->keys[0] == info->keys[0] && node->list->head->keys[1] == info->keys[1]){
            node->list->head = insert_to_form_list(node->list->head, info);
            return;
        } else if (node->right == NULL && node->list->head->keys[axis] == info->keys[axis]){
            node->right = new_node(node->right, node->list->head, depth);
            node->right->parent = node;
            add_no_null(node->right, info, depth+1);
            return;
        }else{
            add_no_null(node->right, info, depth+1);
        }
        if (node->left == NULL){
            node->left = new_node(node->left, node->list->head, depth);
            node->left->parent = node;
        }
    } else{
        if (node->left == NULL){
            node->left = new_node(node->left, info, depth);
            node->left->parent = node;
        } else{
            add_no_null(node->left, info, depth+1);
        }
        if (node->right == NULL){
            node->right = new_node(node->right, node->list->head, depth);
            node->right->parent = node;
        }
    }
}


Info *find_info(Node *node, Info* info, unsigned int depth){
    if (node == NULL){
        return NULL;
    }
    unsigned int axis = depth%2;
    if (info->keys[axis] > node->location && node->location != 0){
        return find_info(node->right, info, depth+1);
    } else if (info->keys[axis] <= node->location && node->location != 0 && info->keys[0] != node->list->head->keys[0] && info->keys[1] != node->list->head->keys[1]){
        return find_info(node->left, info, depth+1);
    }
    if (info->keys[0] == node->list->head->keys[0] && info->keys[1] == node->list->head->keys[1]){
        return node->list->head;
    } else{
        return NULL;
    }
}

Node *find_node(Node *node, Info* info, unsigned int depth){
    if (node == NULL){
        return NULL;
    }
    unsigned int axis = depth%2;
    if (info->keys[axis] > node->location){
        return find_node(node->right, info, depth+1);
    } else if (info->keys[axis] <= node->location && node->right != NULL && node->left != NULL){
        return find_node(node->left, info, depth+1);
    }
    if (info->keys[0] == node->list->head->keys[0] && info->keys[1] == node->list->head->keys[1]){
        return node;
    } else{
        return NULL;
    }
}

/////////////////////////////////////////////////////////////////


void delete_tree(Tree* tree){
    delete_node(tree->node);
    free(tree);
}

void delete_node(Node* node){
    if (node == NULL){
        return;
    } else{
        delete_node(node->left);
        delete_node(node->right);
        if (node->left == NULL && node->right == NULL){
            delete_node_next(node->list->head);
        }
        free(node);
    }
}


void delete_node_next(Info*  info){
    if (info == NULL){
        return;
    } else{
        delete_node_next(info->next);
        free(info->text1);
        free(info->text2);
        free(info);
    }
}

void delete_element(Tree *tree, Info* info){
    Node *node = NULL, *parent = NULL;
    Node *right = NULL, *left = NULL;
    Node *node_parent = NULL;
    node = find_node(tree->node, info, 0);
    if (node == NULL){
        return;
    }
    parent = node->parent;
    if (parent == NULL){
        delete_node_next(node->list->head);
        free(node);
        tree->node = NULL;
    } else if (parent->right == node){
        delete_node_next(node->list->head);
        node_parent = parent->parent;
        left = parent->left;
        if (node_parent == NULL){
            tree->node = left;
            left->parent = NULL;
        } else{
            if (node_parent->left == parent){
                node_parent->left = left;
            } else{
                node_parent->right = left;
            }
            parent->left->parent = node_parent;
        }
        reset_location(left);
        free(parent);
        free(node);
    } else{
        delete_node_next(node->list->head);
        node_parent = parent->parent;
        right = parent->right;
        if (node_parent == NULL){
            tree->node = right;
            right->parent = NULL;
        } else{
            if (node_parent->right == parent){
                node_parent->right = right;
            } else{
                node_parent->left = right;
            }
            right->parent = node_parent;
        }
        free(node->parent);
        free(node);
        reset_location(right);
    }
}

void reset_location(Node* node){
    if (node == NULL){
        return;
    } else{
        reset_location(node->left);
        reset_location(node->right);
        if (node->location == node->list->head->keys[0]){
            node->location = node->list->head->keys[1];
        } else{
            node->location = node->list->head->keys[0];
        }
    }
}


/////////////////////////////////////////////////////////////////

void find_max(Node* node, int key[]){
    if (node == NULL){
        return;
    } else{
        if (math(node->list->head->keys[0], node->list->head->keys[1]) > math(key[0], key[1])){
            key[0] = node->list->head->keys[0];
            key[1] = node->list->head->keys[1];
        }
        find_max(node->left, key);
        find_max(node->right, key);
    }
}

double math(int a, int b){
    return sqrt(a*a + b*b);
}














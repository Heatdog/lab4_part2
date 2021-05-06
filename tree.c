//
// Created by yura on 04.05.2021.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int number =  1;

Tree *new_tree(Tree* tree){
    tree = (Tree*)malloc(sizeof (Tree));
    tree->list = NULL;
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
        list->n++;
    }
    return list;
}

///////////////////////////////////////////////////////////////////



Node *new_node(Node* node, Info* info, unsigned int axis){
    node = (Node*)malloc(sizeof (Node));
    node->left = NULL;
    node->right = NULL;
    node->location = info->keys[(axis+1)%2];
    node->list = NULL;
    node->list = insert_list(node->list, info);
    return node;
}


void printList(List* list, int offset){
    Info *ptr = list->head;
    for (int i = 0; i < number; i++){
        if (ptr != NULL){
            for (int k = 0; k < offset; k++){
                printf("\t");
            }
            printf("[%d;%d] (%s, %s)", ptr->keys[0], ptr->keys[1], ptr->text1, ptr->text2);
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
    printf("[%d;%d]//%s,%s", info->keys[0], info->keys[1], info->text1, info->text2);
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
        if (node->right == NULL){
            node->right = new_node(node->right, info, depth);
        } else{
            add_no_null(node->right, info, depth+1);
        }
        if (node->left == NULL){
            node->left = new_node(node->left, node->list->head, depth);
        }
    } else{
        if (node->left == NULL){
            node->left = new_node(node->left, info, depth);
        } else{
            add_no_null(node->left, info, depth+1);
        }
        if (node->right == NULL){
            node->right = new_node(node->right, node->list->head, depth);
        }
    }
}


Info *find_info(Node *node, Info* info, unsigned int depth){
    if (node == NULL){
        return NULL;
    }
    unsigned int axis = depth%2;
    if (info->keys[axis] >= node->location && node->location != 0){
        return find_info(node->right, info, depth+1);
    } else if (info->keys[axis] < node->location && node->location != 0){
        return find_info(node->left, info, depth+1);
    }
    if (info->keys[0] == node->list->head->keys[0] && info->keys[1] == node->list->head->keys[1]){
        return node->list->head;
    } else{
        return NULL;
    }
}
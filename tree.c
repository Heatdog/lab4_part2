//
// Created by yura on 04.05.2021.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


Tree* new_tree(Tree* tree) {
    tree = (Tree*)malloc(sizeof(Tree));
    tree->node = NULL;
    return tree;
}

////////////////////////////////////////////////////////

List* insert_list(List* list, Info* info) {
    if (list == NULL) {
        list = (List*)malloc(sizeof(List));
        list->head = info;
        list->tail = info;
        list->n = 1;
    }
    else {
        list->tail->next = info;
        list->tail = info;
        info->next = NULL;
        list->n++;
    }
    return list;
}

///////////////////////////////////////////////////////////////////



Node* new_node(Node* node, Info* info, unsigned int axis) {
    node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->location = info->keys[(axis + 1) % 2];
    node->list = NULL;
    node->list = insert_list(node->list, info);
    return node;
}


void printList(List* list, int offset) {
    if (list == NULL) {
        return;
    }
    Info* ptr = list->head;
    Info* info = list->head;
    if (ptr != NULL) {
        for (int k = 0; k < offset; k++) {
            printf("\t");
        }
        printf("[%d;%d] ", info->keys[0], info->keys[1]);
        while (info != NULL) {
            printf("(%s, %s) ", info->text1, info->text2);
            info = info->next;
        }
        printf("\n");
    }
}

//////////////////////////////////////////////////////////////////////////

void print_tree(Node* node, int offset) {
    if (node == NULL) {
        return;
    }
    else {
        print_tree(node->left, offset + 1);
        show_node(node, offset);
        printf("\n");
        print_tree(node->right, offset + 1);
    }
}

void show_node(Node* node, int offset) {
    if (node->right == NULL && node->left == NULL) {
        printList(node->list, offset);
    }
    else {
        for (int k = 0; k < offset; k++) {
            printf("\t");
        }
        printf("%d", node->location);
    }
}



///////////////////////////////////////////////////////////////////


void node_add(Tree* tree, Info* info) {
    if (tree->node == NULL) {
        tree->node = new_node(tree->node, info, 1);
    }
    else {
        add_no_null(tree->node, info, 0);
    }
}

void add_no_null(Node* node, Info* info, unsigned int depth) {
    unsigned int axis = depth % 2;
    if (info->keys[axis] >= node->location) {
        if (node->list->head->keys[0] == info->keys[0] && node->list->head->keys[1] == info->keys[1] && node->left != NULL && node->right != NULL) {
            add_no_null(node->left, info, depth + 1);
        }
        else if (node->list->head->keys[0] == info->keys[0] && node->list->head->keys[1] == info->keys[1] && node->left == NULL && node->right == NULL) {
            node->list = insert_list(node->list, info);
            return;
        }
        else if (node->right == NULL && node->list->head->keys[axis] != info->keys[axis]) {
            node->right = new_node(node->right, info, depth);
            node->right->parent = node;
        }
        else if (node->right == NULL && node->list->head->keys[axis] == info->keys[axis]) {
            node->right = new_node(node->right, node->list->head, depth);
            node->right->parent = node;
            add_no_null(node->right, info, depth + 1);
            return;
        }
        else {
            add_no_null(node->right, info, depth + 1);
        }
        if (node->left == NULL) {
            node->left = new_node(node->left, node->list->head, depth);
            node->left->parent = node;
        }
    }
    else {
        if (node->left == NULL) {
            node->left = new_node(node->left, info, depth);
            node->left->parent = node;
        }
        else {
            add_no_null(node->left, info, depth + 1);
        }
        if (node->right == NULL) {
            node->right = new_node(node->right, node->list->head, depth);
            node->right->parent = node;
        }
    }
}


List *find_info(Node* node, int keys[], unsigned int depth) {
    if (node == NULL) {
        return NULL;
    }
    unsigned int axis = depth % 2;
    if (keys[axis] > node->location && node->location != 0) {
        return find_info(node->right, keys, depth + 1);
    }
    else if (keys[axis] <= node->location && node->location != 0 && keys[0] != node->list->head->keys[0] && keys[1] != node->list->head->keys[1]) {
        return find_info(node->left, keys, depth + 1);
    }
    if (keys[0] == node->list->head->keys[0] && keys[1] == node->list->head->keys[1]) {
        return node->list;
    }
    else {
        return NULL;
    }
}

void show_list(List* list){
    Info *ptr = NULL;
    ptr = list->head;
    printf("[%d;%d] ", ptr->keys[0], ptr->keys[1]);
    while (ptr != NULL){
        printf("(%s, %s) ", ptr->text1, ptr->text2);
        ptr = ptr->next;
    }
}

Node* find_node(Node* node, Info* info, unsigned int depth) {
    if (node == NULL) {
        return NULL;
    }
    unsigned int axis = depth % 2;
    if (info->keys[axis] > node->location) {
        return find_node(node->right, info, depth + 1);
    }
    else if (info->keys[axis] <= node->location && node->right != NULL && node->left != NULL) {
        return find_node(node->left, info, depth + 1);
    }
    if (info->keys[0] == node->list->head->keys[0] && info->keys[1] == node->list->head->keys[1]) {
        return node;
    }
    else {
        return NULL;
    }
}

/////////////////////////////////////////////////////////////////


void delete_tree(Tree* tree) {
    delete_node(tree->node);
    free(tree);
}

void delete_node(Node* node) {
    if (node == NULL) {
        return;
    }
    else {
        delete_node(node->left);
        delete_node(node->right);
        if (node->left == NULL && node->right == NULL) {
            delete_node_next(node->list->head);
        }
        free(node->list);
        free(node);
    }
}

int delete_list(List* list, int release) {
    Info* ptr = NULL, * ptr_prev = NULL;
    ptr = list->head;
    for (int i = 1; i < release; i++) {
        ptr_prev = ptr;
        ptr = ptr->next;
        if (ptr == NULL) {
            return 0;
        }
    }
    if (list->head == list->tail) {
        free(ptr->text1);
        free(ptr->text2);
        free(ptr);
        return 1;
    }
    if (ptr == list->head) {
        list->head = ptr->next;
        free(ptr->text1);
        free(ptr->text2);
        free(ptr);
        list->n--;
        return 0;
    }
    if (ptr == list->tail) {
        list->tail = ptr_prev;
        ptr_prev->next = NULL;
        free(ptr->text1);
        free(ptr->text2);
        free(ptr);
        list->n--;
        return 0;
    }
    ptr_prev->next = ptr->next;
    free(ptr->text1);
    free(ptr->text2);
    free(ptr);
    list->n--;
    return 0;
}


void delete_node_next(Info* info) {
    if (info == NULL) {
        return;
    }
    else {
        delete_node_next(info->next);
        free(info->text1);
        free(info->text2);
        free(info);
    }
}

void delete_element(Tree* tree, Info* info, int release) {
    Node* node = NULL, * parent = NULL;
    Node* right = NULL, * left = NULL;
    Node* node_parent = NULL, * reset = NULL;
    Node* min = NULL;
    node = find_node(tree->node, info, 0);
    if (node == NULL) {
        return;
    }
    parent = node->parent;
    if (parent == NULL) {
        int k = delete_list(node->list, release);
        if (k == 1) {
            free(node->list);
            free(node);
            tree->node = NULL;
        }
    }
    else if (parent->right == node) {
        int k = delete_list(node->list, release);
        if (k == 1) {
            node_parent = parent->parent;
            left = parent->left;
            if (node_parent == NULL) {
                tree->node = left;
                left->parent = NULL;
            }
            else {
                if (node_parent->left == parent) {
                    node_parent->left = left;
                }
                else {
                    node_parent->right = left;
                }
                parent->left->parent = node_parent;
            }
            reset_location(left);
            free(parent->list);
            free(parent);
            free(node->list);
            free(node);
        }
    }
    else {
        int k = delete_list(node->list, release);
        if (k == 1) {
            right = parent->right;
            min = find_min(right);
            if (min->parent->parent == NULL) {
                tree->node = min;
                min->parent = NULL;
                reset_location(min);
            }
            else {
                reset = min->parent->right;
                if (min->parent->parent->right == min->parent) {
                    min->parent->parent->right = reset;
                }
                else {
                    min->parent->parent->left = reset;
                }
                reset->parent = min->parent->parent;
                reset_location(reset);
                if (reset != min) {
                    parent->left = min;
                    if (parent->location == node->list->head->keys[0]) {
                        parent->location = min->list->head->keys[0];
                        min->location = min->list->head->keys[1];
                    }
                    else {
                        parent->location = min->list->head->keys[1];
                        min->location = min->list->head->keys[0];
                    }
                    min->parent = parent;
                }
            }
            free(parent->list);
            free(parent);
            free(node->list);
            free(node);
        }
    }
}

Node* find_min(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void reset_location(Node* node) {
    if (node == NULL) {
        return;
    }
    else {
        reset_location(node->left);
        reset_location(node->right);
        if (node->location == node->list->head->keys[0]) {
            node->location = node->list->head->keys[1];
        }
        else {
            node->location = node->list->head->keys[0];
        }
    }
}


/////////////////////////////////////////////////////////////////

void find_max(Node* node, int key[]) {
    if (node == NULL) {
        return;
    }
    else {
        if (node->left == NULL && node->right == NULL && math(node->list->head->keys[0], node->list->head->keys[1]) > math(key[0], key[1])) {
            key[0] = node->list->head->keys[0];
            key[1] = node->list->head->keys[1];
        }
        find_max(node->left, key);
        find_max(node->right, key);
    }
}

double math(int a, int b) {
    return sqrt(a * a + b * b);
}
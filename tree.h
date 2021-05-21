//
// Created by yura on 04.05.2021.
//

#ifndef LAB4B_1_TREE_H
#define LAB4B_1_TREE_H


typedef struct info_{
    char *text1;
    char *text2;
    struct info_ *next;
    int keys[2];
}Info;

typedef struct list_{
    Info *head;
    Info *tail;
    int n;
}List;


typedef struct node_{
    struct node_ *left;
    struct node_ *right;
    struct node_ *parent;
    List *list;
    int location;
}Node;

typedef struct tree_{
    Node *node;
}Tree;


Tree *new_tree(Tree*);
///////////////////////   Insertion  ////////////////////
List *insert_list(List *, Info*);
/////////////////////////////////////////////////////
Node *new_node(Node*, Info*, unsigned int);
void node_add(Tree*, Info*);
void add_no_null(Node*, Info*, unsigned int);
//////////////////////////   Show   /////////////////////////////
void print_tree(Node*, int);
void show_node(Node*, int);
//////////////////////////   Find   /////////////////////////////
List *find_info(Node *, int[], unsigned int);
void show_list(List*);
//////////////////////////   Delete  ///////////////////////////
void delete_element(Tree *, Info*, int);
Node *find_node(Node *, Info*, unsigned int);
void delete_tree(Tree*);
void delete_node(Node*);
void delete_node_next(Info*);
void reset_location(Node*);
Node *find_min(Node*);
int delete_list(List*, int);
List *copy_list(List*);
//////////////////////////   Distance  ///////////////////////////
void find_max(Node *, int[]);
double math(int, int);

#endif //LAB4B_1_TREE_H

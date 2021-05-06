//
// Created by yura on 04.05.2021.
//

#ifndef LAB4B_1_TREE_H
#define LAB4B_1_TREE_H


typedef struct info_{
    char *text1;
    char *text2;
    struct info_ *next;
    int release;
    int keys[2];
    struct info_ *next_in_list;
}Info;

typedef struct list_{
    Info *head;
    Info *tail;
    int n;
}List;


typedef struct node_{
    struct node_ *left;
    struct node_ *right;
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
void show_info(Info*);
//////////////////////////   Find   /////////////////////////////
Info *find_info(Node *, Info*, unsigned int);

#endif //LAB4B_1_TREE_H

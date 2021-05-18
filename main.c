#include "tree.h"
#include <stdio.h>
#include "dialog.h"


int main(){
    Tree *tree =  NULL;
    tree = new_tree(tree);
    dialog(tree);
    delete_tree(tree);
    printf("That`s all! Bye!");
    return 0;
}
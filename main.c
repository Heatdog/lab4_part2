#include "tree.h"
#include <stdio.h>
#include "dialog.h"


int main(){
    Tree *tree =  NULL;
    tree = new_tree(tree);
    dialog(tree);
    printf("That`s all! Bye!");
    return 0;
}
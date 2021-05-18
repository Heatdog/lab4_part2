//
// Created by yura on 04.05.2021.
//

#include "dialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Find the most distance element from (0;0)","6. Timing"};
const int N =sizeof(msgs) / sizeof(msgs[0]);

void dialog(Tree* tree)
{
    int rc = 0;
    while (1) {
        printf("\n-------------------\n");
        for (int i = 0; i < N; i++) {
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        scan_int(&rc);
        switch (rc) {
            case 0:{
                return;
            }
            case 1:{
                D_Add(tree);
                break;
            }
            case 2:{
                D_Find(tree);
                break;
            }
            case 3:{
                D_Delete(tree);
                break;
            }
            case 4:{
                D_Show(tree);
                break;
            }
            case 5:{
                D_Distance(tree);
                break;
            }
            default:{
                D_Timing();
                break;
            }
        }
    }
}


void scan_int(int* n) {
    int i = 0;
    do {
        i = scanf("%d", n);
        if (i != 1) {
            printf("You`re wrong! Please, try again!\n");
            scanf("%*c");
        }
    } while (i != 1);
}

char* scan_string(char* n) {
    int k = 0;
    n = (char*)malloc(100);
    do {
        k = scanf("%s", n);
        if (k != 1) {
            printf("Please, try again!\n");
        }
    } while (k != 1);
    unsigned int i = strlen(n);
    n = (char*)realloc(n, (i + 1) * sizeof(char));
    return n;
}

Info* scan_info(Info* info) {
    info = (Info*)malloc(sizeof(Info));
    printf("Please, enter x\nEnter-->");
    scan_int(&info->keys[0]);
    printf("Please, enter y\nEnter-->");
    scan_int(&info->keys[1]);
    printf("Please, enter message (2 string)\n");
    printf("First string-->");
    info->text1 = scan_string(info->text1);
    printf("Second string-->");
    info->text2 = scan_string(info->text2);
    info->next = NULL;
    return info;
}

void D_Add(Tree* tree) {
    Info* info = NULL;
    info = scan_info(info);
    node_add(tree, info);
}


void D_Show(Tree* tree) {
    printf("\n////////////////////// Tree //////////////////////\n\n");
    print_tree(tree->node, 0);
}

void D_Timing() {
    Tree* tree = NULL;
    tree = new_tree(tree);
    Info* info = NULL;
    int count, key[2];
    printf("Enter count of repeating\nEnter-->");
    scan_int(&count);
    printf("Start testing...\n");
    clock_t begin_add = clock();
    for (int i = 0; i < count; i++) {
        key[0] = rand();
        key[1] = rand();
        info = info_rand(info, key);
        node_add(tree, info);
    }
    clock_t end_add = clock();
    double time_spent_add = (double)(end_add - begin_add) / CLOCKS_PER_SEC;
    printf("Testing complete, result of adding-->%f", time_spent_add);
}


void D_Find(Tree* tree) {
    Info* info = NULL;
    info = (Info*)malloc(sizeof(Info));
    printf("Please, enter first key\nEnter-->");
    scan_int(&info->keys[0]);
    printf("Please, enter second key\nEnter-->");
    scan_int(&info->keys[1]);
    info = find_info(tree->node, info, 0);
    if (info == NULL) {
        printf("We can`t find this element!");
    }
    else {
        show_info(info);
    }
    free(info);
}

void D_Delete(Tree* tree) {
    Info* info = NULL;
    int release;
    info = (Info*)malloc(sizeof(Info));
    printf("Please, enter first key\nEnter-->");
    scan_int(&info->keys[0]);
    printf("Please, enter second key\nEnter-->");
    scan_int(&info->keys[1]);
    printf("Please, enter release\nEnter-->");
    scan_int(&release);
    delete_element(tree, info, release);
    free(info);
}

void D_Distance(Tree* tree) {
    int key[2] = { 0, 0 };
    find_max(tree->node, key);
    printf("[%d:%d]", key[0], key[1]);
}


/////////////////////////////////////


Info* info_rand(Info* info, int key[]) {
    info = (Info*)malloc(sizeof(Info));
    info->keys[0] = key[0];
    info->keys[1] = key[1];
    info->text1 = (char*)malloc(sizeof(char) * 2);
    *info->text1 = 'a';
    info->text2 = (char*)malloc(sizeof(char) * 2);
    *info->text2 = 'a';
    info->next = NULL;
    return info;
}
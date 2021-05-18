//
// Created by yura on 04.05.2021.
//

#ifndef LAB4B_1_DIALOG_H
#define LAB4B_1_DIALOG_H

#include "tree.h"

void dialog(Tree*);
void scan_int(int*);
void D_Add(Tree*);
void D_Show(Tree*);
void D_Timing();
void D_Find(Tree*);
void D_Delete(Tree*);
void D_Distance(Tree*);
char *scan_string(char *);
Info *scan_info(Info*);
Info *info_rand(Info*, int[]);

#endif //LAB4B_1_DIALOG_H

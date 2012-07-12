#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define L     20

typedef struct ItemNode{
    int id;
    int degree;
    struct ItemNode *self;
    char own;
    struct ItemNode *next;
}ItemNode;

typedef struct UIList{
    int counter;
    struct ItemNode *next;
}UIList;

typedef struct RecList{
    int counter;
    struct ItemNode *next;
}RecList;

typedef struct ItemList{
    int counter;
    struct ItemNode *next;
}ItemList;

typedef struct uNode{
    int id;
    struct uNode  *self;
    struct UIList *uilist;
    struct RecList *rlist;
    struct uNode   *next;
}uNode;

typedef struct uList{
    int counter;
    struct uNode *next;
}uList;

void UListInsert(uList *header,int cid,int iid,ItemNode *self);//往用户列表中按照扫描顺序插入节点
ItemNode *IListInsert(ItemList *header,int iid,int *position,ItemNode **reclist);//往商品列表中有序的插入节点
void UIListInsert(UIList *header,int iid,ItemNode *self);//往用户购买过的商品列表中有序的插入节点
void RECListInsert(RecList *header,int id,int degree);//往用户推荐列表中有顺序的插入节点
void IListSequence(ItemList *header,int id,int degree);

/*----------------------------------------------------Defination of Quick Sort Handling----*/
void swap(ItemNode **a,ItemNode **b);
int  division(ItemNode **list,int left,int right,int pivot_index);
void quickSort(ItemNode **list,int left,int right);
void insert_sort(ItemNode **list,int left,int right);
/*-----------------------------------------------------End---------------------------------*/

int  get_nozero_position(ItemNode **list,int left,int right);

float Get_QIJL(RecList *target,RecList *sim);
char found(UIList *header,int id);
#endif // NODE_H_INCLUDED

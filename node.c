#include "node.h"

void UIListInsert(UIList *header,int iid,ItemNode *self){

    int i;
    ItemNode *list;
    char flag = FALSE;
    if(header->counter != 0){

        list = header->next;

        for(i = 0;i < header->counter;i++){

            if( list->id == iid) {
                flag = TRUE;
                break;
            }
            else if(list->next != NULL){
                list = list->next;
            }
        }
        if( flag != TRUE){

        list->next = malloc(sizeof(ItemNode));
        list = list->next;
        list->id = iid;
        list->self = self;
        list->next = NULL;

        header->counter++;
        }

}
    else {
        header->next = malloc(sizeof(ItemNode));
        header->next->id = iid;
        header->next->self = self;
        header->next->next = NULL;
        header->counter++;
    }

}

ItemNode *IListInsert(ItemList *header,int id,int *position,ItemNode **reclist){

    ItemNode *list,*lastNode;
    int      i;
    char flag = FALSE;

     if(header->next == NULL){
        header->next = malloc(sizeof(ItemNode));
        list = header->next;
        list->id = id;
        list->degree = 1;
        list->own    = FALSE;

        list->next = NULL;
        if( (position != NULL) &&(reclist != NULL) ){
            (*position)++;
            reclist[*position] = list;
        }
        header->counter++;
     }
     else{
            list = header->next;
            for(i = 0;i < header->counter;i++){

                if( list->id == id) {
                    list->degree++;
                    flag = TRUE;
                    break;
                }
                else if(list->next != NULL){
                    list = list->next;
                }
            }
            //printf("Flag:%d\n",flag);
        /*while( (list != NULL) && (flag != TRUE)){
            if( list->next == NULL)lastNode = list;
            if( list->id == id){
                list->degree++;
                flag = TRUE;
            }
            list = list->next;
        }*/
            if( flag != TRUE ){
            //printf("Testing\n");

            list->next = malloc(sizeof(ItemNode));
            list = list->next;
            list->id = id;
            list->degree = 1;
            list->own    = FALSE;

            list->next = NULL;
            if( (position != NULL) &&(reclist != NULL) ){
                (*position)++;
                reclist[*position] = list;
                }
            header->counter++;
            }
        }
    return      list;
}

char found(UIList *header,int id){
    ItemNode *list;
    list = header->next;

    while(list != NULL){
        if( list->id == id){
            return TRUE;
        }
        list = list->next;
    }

    return FALSE;
}
void RECListInsert(RecList *header,int id,int degree){
    char found = FALSE;
    int step = 0;
    ItemNode *backward,*forward,*middle;

    if( header->counter != 0 ){

        forward = header->next;
        backward = NULL;
        middle = NULL;
        //printf("F%d\n",header->counter);
        while( (forward != NULL) && (found != TRUE) ){
        if(forward->id != id){
            if( forward->degree > degree){

                if( forward->next == NULL){

                        forward->next = malloc(sizeof(ItemNode));
                        backward  = forward->next;
                        backward->id = id;
                        backward->degree = degree;
                        backward->next = NULL;

                        found = TRUE;
                        header->counter++;
                        //printf("Add End %d\n",header->counter);

                }
            }
            else if( forward->degree < degree){


                                if( step == 0){

                                    middle = malloc(sizeof(ItemNode));
                                    //printf("Step 0\n");
                                    middle->next = header->next;
                                    header->next = middle;
                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;
                                        /*if(header->counter > RECOMMENND_MAX){

                                         backward = header->next;
                                         forward = backward->next;

                                         while( forward->next != NULL){
                                            forward = forward->next;
                                            backward = backward->next;
                                        }

                                        backward->next = NULL;
                                        header->counter = RECOMMENND_MAX;
                                        //printf("Add Middle success %d\n",header->counter);

                                    }*/

                                        found = TRUE;
                                }
                                else if(step != 0){

                                    middle = malloc(sizeof(ItemNode));
                                    backward->next = middle;
                                    middle->next  = forward;
                                    //printf("Step  No  Zero\t\t");
                                    //getchar();
                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;

                                    found = TRUE;
                                }

            }else if( (forward->degree == degree)  && (forward->id != id) ){

                        if( step == 0){

                                    middle = malloc(sizeof(ItemNode));

                                    middle->next = header->next;
                                    header->next = middle;
                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;

                                    found = TRUE;
                                }
                                else if(step != 0){

                                    middle = malloc(sizeof(ItemNode));
                                    backward->next = middle;
                                    middle->next  = forward;

                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;

                                    found = TRUE;
                                }
                }
        }
        else  {
            break;
        }
            backward = forward;
            forward = forward->next;
            step++;
        }

}
    else if(header->counter == 0) {
        header->next = malloc(sizeof(ItemNode));
        header->next->id = id;
        header->next->degree = degree;
        header->next->next = NULL;
        header->counter++;
        //printf("Add Head\n");

    }
}

void IListSequence(ItemList *header,int id,int degree){
    char found = FALSE;
    int step = 0;
    ItemNode *backward,*forward,*middle;

    if( header->counter != 0 ){

        forward = header->next;
        backward = NULL;
        middle = NULL;
        //printf("F%d\n",header->counter);
        while( (forward != NULL) && (found != TRUE) ){
        if(forward->id != id){
            if( forward->degree > degree){

                if( forward->next == NULL){

                        forward->next = malloc(sizeof(ItemNode));
                        backward  = forward->next;
                        backward->id = id;
                        backward->degree = degree;
                        backward->next = NULL;

                        found = TRUE;
                        header->counter++;
                        //printf("Add End %d\n",header->counter);

                }
            }
            else if( forward->degree < degree){


                                if( step == 0){

                                    middle = malloc(sizeof(ItemNode));
                                    //printf("Step 0\n");
                                    middle->next = header->next;
                                    header->next = middle;
                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;
                                        /*if(header->counter > RECOMMENND_MAX){

                                         backward = header->next;
                                         forward = backward->next;

                                         while( forward->next != NULL){
                                            forward = forward->next;
                                            backward = backward->next;
                                        }

                                        backward->next = NULL;
                                        header->counter = RECOMMENND_MAX;
                                        //printf("Add Middle success %d\n",header->counter);

                                    }*/

                                        found = TRUE;
                                }
                                else if(step != 0){

                                    middle = malloc(sizeof(ItemNode));
                                    backward->next = middle;
                                    middle->next  = forward;
                                    //printf("Step  No  Zero\t\t");
                                    //getchar();
                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;

                                    found = TRUE;
                                }

            }else if( (forward->degree == degree)  && (forward->id != id) ){

                        if( step == 0){

                                    middle = malloc(sizeof(ItemNode));

                                    middle->next = header->next;
                                    header->next = middle;
                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;

                                    found = TRUE;
                                }
                                else if(step != 0){

                                    middle = malloc(sizeof(ItemNode));
                                    backward->next = middle;
                                    middle->next  = forward;

                                    middle->id = id;
                                    middle->degree = degree;

                                    header->counter++;

                                    found = TRUE;
                                }
                }
        }
        else  {
            break;
        }
            backward = forward;
            forward = forward->next;
            step++;
        }

}
    else if(header->counter == 0) {
        header->next = malloc(sizeof(ItemNode));
        header->next->id = id;
        header->next->degree = degree;
        header->next->next = NULL;
        header->counter++;
        //printf("Add Head\n");

    }
}
void UListInsert(uList *header,int cid,int iid,ItemNode *self){

    int i;
    uNode *list;
    uNode *lastNode;
    char found = FALSE;
    /*header->next = malloc(sizeof(uNode));
    header->counter++;
    header->next->id = 123;*/
    if(header->counter != 0){

        list = header->next;

        for(i = 0;i < header->counter;i++){
            if( list->next == NULL){
                lastNode = list;
            }
            if( list->id == cid) {
            //find user in the list & insert
                UIListInsert(list->uilist,iid,self);
                found = TRUE;
                break;
            }
            else if(list->next != NULL){
                list = list->next;
            }
        }

        if( found == FALSE){

        list->next = malloc(sizeof(uNode));
        list = list->next;
        list->id = cid;

        list->uilist = malloc(sizeof(UIList));
        list->uilist->counter = 0;
        list->uilist->next = NULL;

        list->rlist = malloc(sizeof(ItemNode));
        list->rlist->counter = 0;
        list->rlist->next = NULL;

        list->self   = NULL;
        list->next = NULL;

        header->counter++;

        /*list->iList->next = malloc(sizeof(ItemNode));
        list->iList->counter++;
        list->iList->next->id = iid;*/
        UIListInsert(list->uilist,iid,self);

        }
        //printf("ID is %d\n",list->id);
    }
    else {
        header->next = malloc(sizeof(uNode));
        list = header->next;
        list->id = cid;

        list->uilist = malloc(sizeof(UIList));
        list->uilist->counter = 0;
        list->uilist->next = NULL;

        list->rlist = malloc(sizeof(ItemNode));
        list->rlist->counter = 0;
        list->rlist->next = NULL;

        list->self   = NULL;
        list->next = NULL;

        header->counter++;

        UIListInsert(list->uilist,iid,self);
    }
}

void swap(ItemNode **a,ItemNode **b){
    ItemNode *tem;

    tem = *b;
    *b  = *a;
    *a  = tem;
}
int division(ItemNode **list,int left,int right,int pivot_index){
    double pivot = list[pivot_index]->degree;
    int storeIndex = left;
    int i;
    swap(&list[pivot_index],&list[right]);

    for(i = left;i <= right - 1;i++){

        if( list[i]->degree > pivot){
            swap(&list[i],&list[storeIndex]);
            storeIndex++;
        }
    }
    swap(&list[right],&list[storeIndex]);
    return storeIndex;
}
void insert_sort(ItemNode **list,int left,int right){
    ItemNode *sentry;
    int    i,j;
    //printf("enter insert sort\n");
    for(i = left + 1;i <= right;i++){
        if( list[i]->degree > list[i - 1]->degree){
            sentry = list[i];
            list[i] = list[i - 1];
            for( j = i -2;(j >= 0) && (sentry->degree > list[j]->degree);j--) {

                list[j + 1] = list[j];
            }
            list[j + 1] = sentry;
        }
    }
}

void quickSort(ItemNode **list,int left,int right){
    int index,pivot_index = (left + right) / 2;

    if( left < right){
        if( right - left + 1 <= 16){
            insert_sort(list,left,right);
        }
        else{
            index = division(list,left,right,pivot_index);
            quickSort(list,left,index - 1);
            quickSort(list,index + 1,right);

        }
    }
}

float Get_QIJL(RecList *target,RecList *sim){
    ItemNode *ptrTarget,*ptrSim;
    float  ct = 0;

    ptrSim = sim->next;

    while( ptrSim != NULL){
        ptrTarget = target->next;

        while( ptrTarget != NULL){

            if(ptrTarget->id == ptrSim->id) {
                ct++;
                break;
            }
            ptrTarget = ptrTarget->next;
        }
        ptrSim = ptrSim->next;
    }
    return ct;
}
int  get_nozero_position(ItemNode **list,int left,int right){
    int tp = 0,k = 0,len = 7;
    int i = 0,j = right;
    for(k = 0;k < len;k++){
        i = 0;
        j = right;
        if(left < right){
        while( i < j){
            while( (j > i) && (list[j]->degree == (k + 1) ) ) j--;

            while( (j > i) && (list[i]->degree > (k + 1) )) i++;

                if( j == i) {
                    tp = i;
                }
                else{

                    swap(&list[i],&list[j]);
                }

            }
        }
        right = tp;
    }

    return tp;
}

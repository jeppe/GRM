#include "node.h"
#include <math.h>
/*-------------------------Defination of Variables-----------------*/
char probeData[] = "./delicious/probe.data",trainData[] = "./delicious/train.data",resultData[] = "./delicious/results.data";

FILE *probe,*train,*result;

//initialize lists for User and Items
uList *ulist,*probe_header;

uNode *train_User,*probe_User;

ItemList *ilist;

ItemNode *itemlist,*bufferNode,*CItem;

char flag = FALSE,dou;
int t[4] = {0};
unsigned int counter = 0;
//define variables for  Custom  Item  Score
int     CID,IID,SCORE,
        RecordCounterProbe = 0,
        length = 0,k,
        position = -1,index_position = 0,
        recLength = 0,
        checkRecord = 0;
double  RS = 0.0 ,EPL = 0,HL = 0,MEANIL = 0,IL;
float   rank = 0.0,DIL = 0,kDegree = 0;

/*----------End of Variabless Defination--------------*/

/*--------------------------------------------------------------------Quick Sort------------------*/
int main()
{
    ItemNode *reclist[232657] = {NULL};
    train = fopen(trainData,"r");

    ulist = malloc(sizeof(uList));
    ulist->counter = 0;
    ulist->next = NULL;

    probe_header = malloc(sizeof(uList));
    probe_header->counter = 0;
    probe_header->next = NULL;

    ilist  = malloc(sizeof(ItemList));
    ilist->counter = 0;
    ilist->next = NULL;
    result = fopen(resultData,"a+");

    //��ʼ���û�����Ʒ�б�
    while(fscanf(train,"%d%d",&CID,&IID) != EOF){
        CItem = IListInsert(ilist,IID,&position,reclist);
        UListInsert(ulist,CID,IID,CItem);
        counter++;
        if( counter > 1000000) printf("%d\n",counter);
    }
    counter = 0;
    //printf("R0:%d\tR1:%d\tR2:%d\tR3:%d\n",t[0],t[1],t[2],t[3]);

    fclose(train);
/*----------------------------------------------------------------------------Initial Probe User List-----------*/
    probe = fopen(probeData,"r");
    while(fscanf(probe,"%d%d",&CID,&IID) != EOF ){
        UListInsert(probe_header,CID,IID,NULL);
    }
    printf("\ntest\n");
    index_position = get_nozero_position(reclist,0,position);
    printf("fish\n");
    quickSort(reclist,0,index_position);      //������ƷDegree������ʼ�γ��û����Ƽ���
    printf("t\n");
    //getchar();
    printf("FinishRec\n");
    printf("TotalUser:%d\tTotalItems:%d\n",ulist->counter,ilist->counter);

    //���γɵ��Ƽ��б���в���


    train_User = ulist->next;



    while(train_User != NULL){
        //printf("User:%d\n",train_User->id);
        itemlist = train_User->uilist->next;

        while(itemlist != NULL){
            itemlist->self->own = TRUE;
            itemlist = itemlist->next;
        }

        k  = 0;
        recLength = 0;
        /*--------------------------------------------------------------Initial Top L reclist-----*/
        while(recLength < L){
            if(reclist[k]->own != TRUE){
                RECListInsert(train_User->rlist,reclist[k]->id,reclist[k]->degree);
                recLength++;
            }
            k++;
        }


        /*---------------------------------------------------------------End Top L Reclist--------*/
        probe_User = probe_header->next;
        flag  = FALSE;

        while( (probe_User != NULL) && (flag != TRUE) ){

            if(probe_User->id == train_User->id){
                probe_User->self  =  train_User;

                itemlist = probe_User->uilist->next;
                //RecordCounterProbe += probe_User->uilist->counter;
                counter++;
                DIL  = 0;
                while(itemlist != NULL){

                    length = ilist->counter - train_User->uilist->counter;
                    dou   = FALSE;
                    rank = 0;

                    for(k = 0;(k <= position)&&(dou != TRUE) ;k++){
                        if( reclist[k]->own != TRUE ){
                            rank++;
                            if(reclist[k]->id == itemlist->id){
                                RecordCounterProbe++;

                                RS += (rank / length);
                                if( rank <= L)DIL++;
                                dou = TRUE;
                            }
                        }
                    }
                    itemlist = itemlist->next;
                }
                EPL  = EPL + DIL / L;
                flag = TRUE;
            }
            probe_User = probe_User->next;
        }

        /*--------------------------------------------------------------Initial itemlist----------*/
        itemlist = train_User->uilist->next;
        while(itemlist != NULL){
            itemlist->self->own = FALSE;
            itemlist = itemlist->next;
        }
        train_User = train_User->next;
    }

    RS = RS / RecordCounterProbe;
    EPL = EPL / counter;

    EPL = (EPL * ulist->counter  / RecordCounterProbe) * ilist->counter;
    //printf("Test finish\n");
    fclose(probe);

    /*-----------------------------------------------------------------------------------------Diversity Test Begin-----------------*/
    probe_User = probe_header->next;
    uNode *neighbor;
    counter = 0;
    RecordCounterProbe = 0;
    HL                 = 0;
    int total = 0;
    while( probe_User->next != NULL ){
        kDegree  = 0;
        IL       = 0;
        if( probe_User->self != NULL ){
            RecordCounterProbe++;
            neighbor = probe_User->next;

            itemlist = probe_User->self->rlist->next;

            while( itemlist != NULL){
                kDegree  = itemlist->degree;
                IL += log2f( ( ulist->counter / kDegree) );
                itemlist = itemlist->next;
            }

            IL = IL / L;
            MEANIL += IL;
            while( neighbor != NULL){

                if( neighbor->self != NULL){

                    HL += (1 - Get_QIJL(probe_User->self->rlist,neighbor->self->rlist) / L);

                    counter++;
                }
                neighbor = neighbor->next;
            }

            total = counter;
        }

        probe_User = probe_User->next;
    }

    HL = HL / counter;

    MEANIL = MEANIL / RecordCounterProbe;

    /*-----------------------------------------------------------------------------------------Diversity Test END-----------------*/
    printf("\nRS:%f\tEPL:%f\tHL:%f\tMEANIL:%f\n",RS,EPL,HL,MEANIL);
    fprintf(result,"RS:%1.4f\tEPL:%f\tHL:%f\tMEANIL:%f\n",RS,EPL,HL,MEANIL);
    fclose(result);
    return 0;
}

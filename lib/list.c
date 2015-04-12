/*
 * Created by zhuangjf, 2015/4/7
 * All Rights Reserved
 */

#include <list.h>

void list_init(struct list *A)
{
    if(NULL == A) {
        return;
    }
    
    A->next = NULL;
}

void list_add(struct list *A, struct list *B)
{
    if((NULL == A) || (NULL == B)) {
        return;
    }

    A->next = B;
}




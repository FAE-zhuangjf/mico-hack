/*
 * Created by zhuangjf, 2015/4/7
 * All Rights Reserved
 */

#ifndef _LIST_H_
#define _LIST_H_

struct list
{
    struct list *next;
};

struct list_head {
    struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new, 
                            struct list_head *prev,
                            struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

void list_init(struct list *A);
void list_add(struct list *A, struct list *B);

#endif
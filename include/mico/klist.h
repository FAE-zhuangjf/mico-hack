/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#ifndef _MICO_KLIST_H_
#define _MICO_KLIST_H_

#include <mico/types.h>
#include <mico/kref.h>

#include <list.h>

struct klist_node
{
    void *n_klist;  /* ref to the node container */
    struct list_head n_node; /* keep relationship */
    struct kref n_ref;  /* the object referenced count */
};

struct klist
{
    struct list_head k_list;
    void (*get)(struct klist_node *);
    void (*put)(struct klist_node *);
};

struct klist_iter {
	struct klist		*i_klist;
	struct klist_node	*i_cur;
};

void klist_add_tail(struct klist_node *n, struct klist *k);
struct klist_node *klist_next(struct klist_iter *i);

#endif


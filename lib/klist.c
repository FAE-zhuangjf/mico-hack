/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#include <mico/klist.h>
#include <mico/kref.h>
#include <mico/kernel.h>

#include <types.h>

/*
 * Use the lowest bit of n_klist to mark deleted nodes and exclude
 * dead ones from iteration.
 */
#define KNODE_DEAD		1LU
#define KNODE_KLIST_MASK	~KNODE_DEAD

static struct klist_node *to_klist_node(struct list_head *n)
{
	return container_of(n, struct klist_node, n_node);
}

static void knode_set_klist(struct klist_node *knode, struct klist *klist)
{
    knode->n_klist = klist;
}

static void klist_node_init(struct klist *k, struct klist_node *n)
{
    INIT_LIST_HEAD(&n->n_node);
    kref_init(&n->n_ref);
    knode_set_klist(n, k);
    if(k->get) {
        k->get(n);
    }
}

static void add_tail(struct klist *k, struct klist_node *n)
{
    list_add_tail(&n->n_node, &k->k_list);
}

void klist_add_tail(struct klist_node *n, struct klist *k)
{
    klist_node_init(k, n);
    add_tail(k, n);
}

int klist_node_attached(struct klist_node *n)
{
    return (n->n_klist != NULL);
}

/**
 * klist_iter_init_node - Initialize a klist_iter structure.
 * @k: klist we're iterating.
 * @i: klist_iter we're filling.
 * @n: node to start with.
 *
 * Similar to klist_iter_init(), but starts the action off with @n,
 * instead of with the list head.
 */
void klist_iter_init_node(struct klist *k, struct klist_iter *i,
			  struct klist_node *n)
{
	i->i_klist = k;
	i->i_cur = n;
	if (n)
		kref_get(&n->n_ref);
}

/**
 * klist_iter_exit - Finish a list iteration.
 * @i: Iterator structure.
 *
 * Must be called when done iterating over list, as it decrements the
 * refcount of the current node. Necessary in case iteration exited before
 * the end of the list was reached, and always good form.
 */
void klist_iter_exit(struct klist_iter *i)
{
	if (i->i_cur) {
		i->i_cur = NULL;
	}
}

static bool knode_dead(struct klist_node *knode)
{
	return (unsigned long)knode->n_klist & KNODE_DEAD;
}

struct klist_node *klist_next(struct klist_iter *i)
{
	struct klist_node *last = i->i_cur;
	struct klist_node *next;

	if (last) {
		next = to_klist_node(last->n_node.next);
	} else {
		next = to_klist_node(i->i_klist->k_list.next);
	}

	i->i_cur = NULL;
	while (next != to_klist_node(&i->i_klist->k_list)) {
        /* if the knode is not deleted */
		if (!knode_dead(next)) {
			i->i_cur = next;
			break;
		}
        /* skip the deleted knode */
		next = to_klist_node(next->n_node.next);
	}

	return i->i_cur;
}



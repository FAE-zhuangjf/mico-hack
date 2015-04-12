/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#ifndef _KREF_H_
#define _KREF_H_

struct kref {
    int refcount;
};

static inline void kref_init(struct kref *kref)
{
    kref->refcount = 1;
}

/**
 * kref_get - increment refcount for object.
 * @kref: object.
 */
static inline void kref_get(struct kref *kref)
{
	/* If refcount was 0 before incrementing then we have a race
	 * condition when this kref is freeing by some other thread right now.
	 * In this case one should use kref_get_unless_zero()
	 */
	kref->refcount++;
}


#endif


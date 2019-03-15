/* rt_heap.h: definitions to enable retargetting of heap implementation
 *
 * Copyright 1999 ARM Limited. All rights reserved.
 *
 * RCS $Revision: 185914 $
 * Checkin $Date: 2014-06-24 07:41:38 +0100 (Tue, 24 Jun 2014) $
 * Revising $Author: petpav01 $
 */

#ifndef __RT_HEAP_H
#define __RT_HEAP_H
#define __ARMCLIB_VERSION 5060002

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This is the structure that defines the heap descriptor. The
 * first section of it is used by the C library and so the format
 * is fixed. Space after that can be used as the user wishes.
 */
struct __Heap_Descriptor;

/*
 * Define all these functions to override the heap. __Heap_DescSize
 * must return the size of the __Heap_Descriptor structure.
 */
extern int __Heap_DescSize(int zero);
extern void __Heap_Initialize(struct __Heap_Descriptor *h);
extern void __Heap_Finalize(struct __Heap_Descriptor *h);
extern void __Heap_ProvideMemory(struct __Heap_Descriptor *, void *, size_t);
extern void *__Heap_Alloc(struct __Heap_Descriptor *, size_t);
extern void __Heap_Free(struct __Heap_Descriptor *, void *);
extern void *__Heap_Realloc(struct __Heap_Descriptor *, void *, size_t);
extern void *__Heap_Stats(struct __Heap_Descriptor *,
                          int (* /*print*/)(void *, char const *format, ...),
                          void * /*printparam*/);
extern int __Heap_Valid(struct __Heap_Descriptor *,
                        int (* /*print*/)(void *, char const *format, ...),
                        void * /*printparam*/, int /*verbose*/);

/*
 * The heap can call these functions when it is full or
 * inconsistent. __Heap_Full is passed the extra size that the heap
 * needs, and will call back to __Heap_ProvideMemory if it can find
 * some more storage. These are not functions you should override.
 */

extern int __Heap_Full(struct __Heap_Descriptor *, size_t);
extern void __Heap_Broken(struct __Heap_Descriptor *);

/*
 * Call _init_alloc, and define __rt_heap_extend, if you are trying
 * to run a heap on the bare metal.
 */
extern void _init_alloc(uintptr_t /*base*/, uintptr_t /*top*/);
extern size_t __rt_heap_extend(size_t /*size*/, void ** /*block*/);

#ifdef __cplusplus
}
#endif

#endif


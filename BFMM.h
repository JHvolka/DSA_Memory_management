#pragma once

#include <stdlib.h>
#include <stdint.h>

/** @file BFMM.h
 *
 */

/**
 * The enumeration of node color
 */
enum color_t {
    BLACK,
    RED
};

/**
 * A structure to represent doubly linked list for memory management.
 *
 * This part of heap node is not deleted when given memory segment is in use, as
 * it is required for merging freed blocks of memory.
 */
typedef struct HEAP_LIST {
    struct HEAP_NODE *prev;
    struct HEAP_NODE *next;
    uint8_t used;
} heapList_t;

/**
 * A structure to represent red-black tree node for memory management.
 *
 * This part of heap node may be overwritten when given memory segment is in
 * use.
 */
typedef struct HEAP_TREE {
    struct HEAP_NODE *parent;
    struct HEAP_NODE *left;
    struct HEAP_NODE *right;
    enum color_t color;
    unsigned int size;
} heapTree_t;

/**
 * A structure to represent heap node.
 * It is split into two parts:
 *      list - doubly linked list
 *      tree - red-black tree
 */
typedef struct HEAP_NODE {
    heapList_t list;
    heapTree_t tree;
} heapNode_t;


static unsigned char *Heap;
static heapNode_t *heap_root;


/**
 * Searches heap tree for free block of memory that is a best fit for given size
 * of data. Returns NULL if no free block is large enough.
 *
 * @param[in] size of data
 * @return pointer to data location or NULL if not found
 */
heapNode_t *find_best_fit(unsigned int size);;

//==============================================================================

/**
 * TODO
 * @param ptr
 * @param size
 */
void memory_init(void *ptr, unsigned int size);

/**
 * TODO
 * @param[in] size
 * @return
 */
void *memory_alloc(unsigned int size);

/**
 * TODO
 * @param valid_ptr
 * @return
 */
int memory_free(void *valid_ptr);

/**
 * TODO
 * @param ptr
 * @return
 */
int memory_check(void *ptr);


#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/** @file BFMM.h
 * TODO documentation
 */

/**
 * The enumeration of node color
 */
enum color_t {
    BLACK,
    RED
};

/**
 * A structure to represent doubly linked list for memory management. ABC
 *
 * This part of heap node is not deleted when given memory segment is in use, as
 * it is required for merging freed blocks of memory.
 */
typedef struct HEAP_LIST {
    struct HEAP_NODE *prev; /**< pointer to previous node */
    struct HEAP_NODE *next; /**< pointer to next node */
    uint8_t used;           /**< flag if block is allocated or free */
} heapList_t;

/**
 * A structure to represent red-black tree node for memory management.
 *
 * This part of heap node may be overwritten when given memory segment is in
 * use. It creates an overhead only if new tree node doesn't fit at the end of
 * block that would have been split up, and thus the space is left unused.
 */
typedef struct HEAP_TREE {
    struct HEAP_NODE *parent; /**< parent node pointer */
    struct HEAP_NODE *left;   /**< smaller node pointer */
    struct HEAP_NODE *right;  /**< bigger node pointer */
    enum color_t color;       /**< node color (red or black) */
    unsigned int size;        /**< size of available memory in block */
} heapTree_t;

/**
 * A structure to represent heap node.
 * It is split into two parts:
 *      list - doubly linked list
 *      tree - red-black tree
 */
typedef struct HEAP_NODE {
    /** Node of doubly linked list. Used to keep relative position of blocks */
    heapList_t list;
    heapTree_t tree; /**< A node of red-black tree for fast best fit search. */
} heapNode_t;

/// Global heap pointer
static unsigned char *Heap = NULL;

/// Global pointer to free heap blocks (BST)
static heapNode_t *heap_root = NULL;


/**
 * Searches heap tree for free block of memory that is a best fit for given size
 * of data. Returns NULL if no free block is large enough.
 *
 * @param[in] size of data
 * @return pointer to data location or NULL if not found
 */
heapNode_t *find_best_fit(unsigned int size);

/**
 * Inserts a node into red-black tree of free memory blocks. Node size is taken as key.
 * @param[in] node_insert
 * TODO finish documentation
 */
void insert_node(heapNode_t * node_insert);
void delete_node(heapNode_t * node_delete);

//==============================================================================

/**
 * TODO documentation
 * @param ptr
 * @param size
 */
void memory_init(void *ptr, unsigned int size);

/**
 * TODO documentation
 * @param[in] size
 * @return
 */
void *memory_alloc(unsigned int size);

/**
 * TODO documentation
 * @param valid_ptr
 * @return
 */
int memory_free(void *valid_ptr);

/**
 * TODO documentation
 * @param ptr
 * @return
 */
int memory_check(void *ptr);


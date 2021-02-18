#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/** @file BFMM.h
 * \todo documentation
 */

/// Global heap pointer
static unsigned char *Heap = NULL;

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
    /** Size of available memory in block. Does include memory used for
     * heapTree, but not for heapList */
    unsigned int size;
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

/**
 *
 */
typedef struct HEAP_HEAD{
    /** Total size of memory block available, including all overheads */
    unsigned int size;
    heapNode_t * tree_root;    /**< Pointer to tree root */
}heapHead_t;

/**
 * Searches heap tree for free block of memory that is a best fit for given size
 * of data. Returns NULL if no free block is large enough.
 *
 * @param[in] size of data
 * @return pointer to data location or NULL if not found
 */
heapNode_t *find_best_fit(unsigned int size);

/**
 * Inserts a node into red-black tree of free memory blocks. Node size is taken
 * as key.
 * @param[in] node_insert
 * \todo finish documentation
 */
void insert_node(heapNode_t * node_insert);
void delete_node(heapNode_t * node_delete);

//==============================================================================

/// \todo check inline support in msvc and add preprocessor directives if needed or put inside define

/**
 * Function returns heap header.
 * @return heap header
 */
inline heapHead_t * get_head ();

/**
 * Function returns heap tree root.
 * @return heap tree root
 */
inline heapNode_t * get_tree_root ();

/**
 * Function returns first heap list entry.
 * @return  fisrt heap tree entry
 */
inline heapNode_t * get_list_root ();

//==============================================================================

/**
 * \todo documentation
 * @param ptr
 * @param size
 */
void memory_init(void *ptr, unsigned int size);

/**
 * \todo documentation
 * @param[in] size
 * @return
 */
void *memory_alloc(unsigned int size);

/**
 * \todo documentation
 * @param valid_ptr
 * @return
 */
int memory_free(void *valid_ptr);

/**
 * \todo documentation
 * @param ptr
 * @return
 */
int memory_check(void *ptr);

// Debug only functions
#if DEBUG == 1
unsigned int get_largest_available_block_size();
#endif


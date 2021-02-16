#include "BFMM.h"

heapNode_t *find_best_fit(unsigned int size) {
    heapNode_t *tmp = heap_root;

    // Perform inorder search
    while (tmp->tree.left != NULL && tmp->tree.right != NULL) {

        // Go to smaller node, if it exists and is large enough
        if (tmp->tree.left && tmp->tree.left->tree.size >= size)
            tmp = tmp->tree.left;

            // Else use this node if sufficient
        else if (tmp->tree.size >= size)
            break;

            // Else larger size node needed
        else if (tmp->tree.right)
            tmp = tmp->tree.right;
    }

    // If fitting node found
    if (tmp->tree.size >= size)
        return tmp;

    // No node of given size or larger available
    return NULL;
}

void memory_init(void *ptr, unsigned int size) {
    Heap = (unsigned char *) ptr;
    heap_root = (heapNode_t *) ptr;

    // Initialize list part
    heap_root->list.prev = NULL;
    heap_root->list.next = NULL;
    heap_root->list.used = 0;

    // Initialize tree part
    heap_root->tree.parent = NULL;
    heap_root->tree.left = NULL;
    heap_root->tree.right = NULL;
    heap_root->tree.color = BLACK;
    // Only list part is overhead
    heap_root->tree.size = size - sizeof(heapList_t);
}

void*memory_alloc(unsigned int size) { // TODO check whole function

    heapNode_t * remaining_block;

    // Check if memory was initialized and if any memory is free for allocation
    if (Heap == NULL || heap_root == NULL) {
        return NULL;
    }

    // Find free memory space
    heapNode_t *new_block = find_best_fit(size);

    // Return NULL if no available block of given size is available
    if (new_block == NULL)
        return NULL;



    // Tag new block as used
    new_block->list.used = 0;

    // Remove from tree of free memory blocks
    delete_node(new_block);

    // Split up found memory, if remainder will be of usable size. Enough space
    // for new heapNode needs to be left after _size_ of memory is subtracted.
    // Even if exactly `sizeof(heapNode_t)` space is left over, the part of node
    // used for tree can still be allocated.
    if (new_block->tree.size >= size + sizeof(heapNode_t)) {

        // Create block with remaining space and insert it after new_block in list TODO better explanation
        remaining_block = new_block + size + sizeof(heapNode_t); // todo check if sizeof is correct
        remaining_block->list.used = 0;
        remaining_block->list.next = new_block->list.next;
        remaining_block->list.prev = new_block;

        // Add remaining block into tree of free memory
        insert_node(remaining_block);
    } else{

    }

    // Return address where tree starts. Tree node part is no longer needed, and
    // can be used by the caller
    return (void*) &new_block->tree;
}

int memory_free(void *valid_ptr) {
    // Assignment says we can assume this is never fails, but... ¯\_(ツ)_/¯
    assert( memory_check(valid_ptr) );


    return 0;
}

int memory_check(void *ptr) {
    // TODO implement
    return 0;
}

#include "BFMM.h"

heapNode_t *find_best_fit(unsigned int size) {
    heapNode_t *tmp = get_tree_root();

    // Perform inorder search
    while (1) {

        // Go to smaller node, if it exists and is large enough
        if ( tmp->tree.left != NULL && tmp->tree.left && tmp->tree.left->tree.size >= size)
            tmp = tmp->tree.left;

            // Else use this node if sufficient
        else if (tmp->tree.size >= size)
            return tmp;

            // Else larger size node needed
        else if (tmp->tree.right)
            tmp = tmp->tree.right;

            // No valid options available
        else
            return NULL;
    }
}

void memory_init(void *ptr, unsigned int size) {
    Heap = (unsigned char *) ptr;

    // Initialize header
    heapHead_t * head = get_head();
    head->tree_root = (heapNode_t *) (head + sizeof(heapHead_t));
    head->size = size;

    heapNode_t * root = head->tree_root;

    // Initialize list part
    root->list.prev = NULL;
    root->list.next = NULL;
    root->list.used = 0;

    // Initialize tree part
    root->tree.parent = NULL;
    root->tree.left = NULL;
    root->tree.right = NULL;
    root->tree.color = BLACK;
    // Only list part is overhead
    root->tree.size = size - sizeof(heapList_t);
}

void *memory_alloc(unsigned int size) { /// \todo redo with new head layout and check whole function

    heapNode_t *remaining_block;

    // Check if memory was initialized and if any memory is free for allocation
    if (Heap == NULL) {
        return NULL;
    }

    // Find unused memory space
    heapNode_t *new_block = find_best_fit(size);

    // Return NULL if no available block for given size is available
    if (new_block == NULL)
        return NULL;

    // Tag new block as used
    new_block->list.used = 0;

    // Remove from tree of unused memory blocks
    delete_node(new_block);

    // Split up found memory, if remainder will be of usable size. Enough space
    // for new heapNode needs to be left after _size_ of requested memory is
    // subtracted. Even if exactly `sizeof(heapNode_t)` space is left over, the
    // part of node used for tree can still be allocated.
    if (new_block->tree.size >= size + sizeof(heapNode_t)) {

        /// Create block with remaining space and insert it after new_block in list \todo better explanation of this part
        remaining_block = new_block + size + sizeof(heapNode_t); /// \todo check if sizeof is correct
        remaining_block->list.used = 0;
        remaining_block->list.next = new_block->list.next;
        remaining_block->list.prev = new_block;

        // Add remaining block into tree of unused memory
        insert_node(remaining_block);
    }

    // Return address where tree starts. Tree node part is no longer needed, and
    // can be used by the caller
    return (void *) &new_block->tree;
}

int memory_free(void *valid_ptr) {
    int prev_unused, next_unused;
    heapNode_t *tmp;

    // Assignment says we can assume this is never fails, but... ¯\_(ツ)_/¯
    assert(memory_check(valid_ptr));

    // Get beginning of the memory block
    heapNode_t *block = (heapNode_t *) valid_ptr - sizeof(heapList_t);

    // Set as unused
    block->list.used = 0;

    // Check neighbours if they are unused
    prev_unused = block->list.prev->list.used;
    next_unused = block->list.next->list.used;

    // Both neighbours unused. Merge both
    if (prev_unused && next_unused) {

    }

    // Only one neighbour unused. Merge only the unused one
    else if (prev_unused) {
        // Remove from tree
        tmp = block->list.prev;
        delete_node(tmp);
        tmp->list.next = block->list.next;
        tmp->list.

    }
    else if (next_unused) {

    }
    // No neighbouring blocks are unused. Only add into tree of unused memory
    else {
        insert_node(block);
    }

    return 0;
}

int memory_check(void *ptr) {
    heapNode_t * tmp = get_list_root();

    // Traverse list
    while (tmp != NULL){
        // If exact block address found, return value of used.
        if (ptr == tmp + sizeof(heapList_t))
            return tmp->list.used;

        // Check if searched address was not already passed.
        if (ptr < tmp + sizeof(heapList_t))
            return 0;

        tmp = tmp->list.next;
    }
    // Block not found in list
    return 0;
}

heapHead_t *get_head() {
    return (heapHead_t*) Heap;
}

heapNode_t *get_tree_root() {
    return get_head()->tree_root;
}

heapNode_t *get_list_root() {
    return (heapNode_t *) (get_head() + sizeof(heapHead_t));
}

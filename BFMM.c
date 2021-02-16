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

    // Initialize list
    heap_root->list.prev = NULL;
    heap_root->list.next = NULL;
    heap_root->list.used = 0;

    // Initialize tree
    heap_root->tree.parent = NULL;
    heap_root->tree.left = NULL;
    heap_root->tree.right = NULL;
    heap_root->tree.color = BLACK;
    heap_root->tree.size = size - sizeof(heapList_t);
}

void *memory_alloc(unsigned int size) {

}

int memory_free(void *valid_ptr) {
    return 0;
}

int memory_check(void *ptr) {
    return 0;
}

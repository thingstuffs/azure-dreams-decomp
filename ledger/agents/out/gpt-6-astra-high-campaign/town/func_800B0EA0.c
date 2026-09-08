#include "common.h"

typedef struct CallbackNode {
    void (*callback)();
} CallbackNode;

#ifndef NULL
#define NULL 0
#endif

/* Invoke the node callback with the node itself when present. */
void func_800AE600(CallbackNode *node) {
    if (node->callback != NULL) {
        node->callback(node);
    }
}

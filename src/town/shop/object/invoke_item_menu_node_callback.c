#include "common.h"

/* Display payload whose leading word is the selection-delay callback. The only callback ever installed
 * is tick_item_menu_selection_delay (change_item_menu_selection); it reads only this payload. */
typedef struct CallbackNode {
    void (*callback)(struct CallbackNode *node);
} CallbackNode;

#ifndef NULL
#define NULL 0
#endif

/* Invoke the node callback with the node itself when present. */
void invoke_item_menu_node_callback(CallbackNode *node) {
    if (node->callback != NULL) {
        node->callback(node);
    }
}

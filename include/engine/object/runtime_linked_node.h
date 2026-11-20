#ifndef ENGINE_OBJECT_RUNTIME_LINKED_NODE_H
#define ENGINE_OBJECT_RUNTIME_LINKED_NODE_H

#include "common.h"

struct WindowListObject;

/* Object nodes store their enclosing window body. The controller embeds a
 * sentinel with the same two links; its object word is unused by the list. */
typedef struct RuntimeLinkedNode {
    struct WindowListObject *object;
    struct RuntimeLinkedNode *backlink;
    struct RuntimeLinkedNode *next;
} RuntimeLinkedNode;

/* prepend_embedded_object_node links this body at +0x54. The drain clears
 * the first word of its attached object before removing the body's node. */
typedef struct WindowListObject {
    s32 *clear_target;
    u8 pad04[0x50];
    RuntimeLinkedNode link;
} WindowListObject;

#endif

#include "engine/node.h"
#include "engine/object.h"
#include "engine/script.h"
#include "engine/message.h"

/* Unlink each window body from the controller, draw and active lists. */
void remove_all_controller_nodes(ScriptController *controller) {
    RuntimeLinkedNode *head = &controller->object_list;
    RuntimeLinkedNode *node = head->next;

    while (node != head) {
        WindowListObject *owner = node->object;
        ObjectNodeHeader *object;

        if (owner->clear_target != 0)
            clear_word(owner->clear_target);
        unlink_owner_list_node(node);
        object = NODE_HEADER(owner);
        unlink_node(object);
        unlink_active_node(object);
        node = head->next;
    }
}

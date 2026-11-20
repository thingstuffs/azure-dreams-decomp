#include "engine/object.h"
#include "engine/message.h"

void prepend_owner_list_node(ScriptController *controller, RuntimeLinkedNode *node) {
    node->backlink = &controller->object_list;
    node->next = controller->object_list.next;
    controller->object_list.next->backlink = node;
    controller->object_list.next = node;
}

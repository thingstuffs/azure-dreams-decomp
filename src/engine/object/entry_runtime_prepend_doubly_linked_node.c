#include "engine/object.h"
#include "engine/object/runtime_linked_node.h"

void prepend_embedded_object_node(void *context, void *object_data) {
    WindowListObject *object = object_data;
    object->link.object = object;
    prepend_owner_list_node(context, &object->link);
}

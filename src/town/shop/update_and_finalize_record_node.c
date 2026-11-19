#include "town/menu.h"
#include "shared/object_node.h"

/* Refresh the alternate storage menu on this node. */
void update_and_finalize_record_node(ObjectNodeHeader *node) {
    update_paged_menu_record(NODE_BODY(node));
}

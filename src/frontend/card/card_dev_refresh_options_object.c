#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

/* Process embedded data and set object and global flags when the object exists. */
void card_dev_refresh_options_object(ObjectNodeHeader *node) {
    if (node != 0) {
        card_dev_fade_four_values(NODE_BODY(node));
        {
            u16 *flags = &node->flags;
            *flags |= 0x8000;
        }
        card_ui_dirty_flags |= 0x8000;
    }
}

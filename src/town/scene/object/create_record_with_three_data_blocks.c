#include "common.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#include "town/devkit/old_minigame_imports.h"

extern u8 menu_entry_draw_callback_address[];

/* Allocate a text node, copy its body and register the shared draw callback. */
void create_record_with_three_data_blocks(TownCollectionTextUpdate callback, const TownCollectionText *data_blocks)
{
    ObjectNodeHeader *node = func_800374FC(1, &scene_object_factory_data);

    if (node != 0) {
        TownCollectionText *body = NODE_BODY(node);
        *body = *data_blocks;
        node->update_callback = callback;
        func_8003BC18(node, menu_entry_draw_callback_address);
    }
}

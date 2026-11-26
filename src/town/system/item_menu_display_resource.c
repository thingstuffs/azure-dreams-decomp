#include "engine/node/allocation.h"
#include "shared/menu_display.h"
/* Item menu display resource and its file-private helper. */
#include "common.h"
#include "shared/object_node.h"
#include "engine/item.h"
#include "engine/texture.h"
#include "engine/util.h"

#include "shared/object_flags.h"
#include "town/shop.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "engine/graphics.h"
#include "town/shop/item.h"
/* object in create_item_menu_child_at_position */

/* payload in create_item_menu_child_at_position */


static s32 load_item_menu_display_resource(ItemMenuTransition *payload, s32 value);
extern void register_node(void *object, void *callback);

/* Allocates menu display entries, copies the default vector, and shares it among the entries on success. */
static s32 load_item_menu_display_resource(ItemMenuTransition *object, s32 resource_id) {
    s32 success = 0;
    ItemMenuPart **parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)object->allocations, resource_id, 8);

    object->rows.as_ptr = parts;
    if (parts != 0) {
        object->part_vector.unk0 = display_vector_defaults.unk0;
        object->part_vector.unk4 = display_vector_defaults.unk4;
        object->part_vector.unk8 = display_vector_defaults.unk8;
        set_menu_part_vectors(parts, &object->part_vector, 0x1A);
        success = 1;
    }
    return success;
}

/* Creates a linked item menu display at the requested position and cleans up if resource loading fails. */
ObjectNodeHeader *create_item_menu_child_at_position(ObjectNodeHeader *parent, s32 x, s32 y, s32 resource_id,
                    s32 resource_data, u8 *entry_ids)
{
    ObjectNodeHeader *object;
    ItemMenuTransition *payload;

    object = allocate_list_node(0, &parent->next);
    if (object != 0) {
        payload = NODE_BODY(object);
        if (load_item_menu_display_resource(payload, 0x1A) != 0) {
            object->sprite = (SpriteFrameState *)&payload->position_links;
            payload->unk_D4 = link_item_menu_display_entries(payload->rows.as_ptr);
            initialize_item_menu_list_display(payload, parent, resource_id, resource_data, x, y, entry_ids);
            register_node(object, draw_tinted_node_sprites_scratch);
            object->update_callback = advance_item_menu_object_animation;
        } else {
            release_null_terminated_entries(payload->allocations);
            object->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            object = 0;
        }
    }
    return object;
}

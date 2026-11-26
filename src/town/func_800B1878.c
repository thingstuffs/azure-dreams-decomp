#include "common.h"
#include "engine/node/registration.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/graphics.h"
#include "town/shop.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "engine/item.h"
#include "town.h"
#include "town/shop/item.h"
struct ItemMenuTransition;


extern void *allocate_list_node(s32 value, ObjectNodeHeader **list_head);

/* Create and initialize a child object at (x, y), marking allocation failure for cleanup. */
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

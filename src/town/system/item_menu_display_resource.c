#include "engine/node/allocation.h"
/* Item menu display resource and its file-private helper. */
#include "common.h"
#include "shared/object_node.h"
#include "engine/item.h"
#include "engine/texture.h"
#include "engine/util.h"
extern s32 display_vector_defaults[];
#include "shared/object_flags.h"
#include "town/shop.h"
#include "engine/graphics.h"
/* object in create_item_menu_child_at_position */

typedef struct S_800AEFD8_1 {
    u8 pad_00[0xD4];
    void * unk_D4;
    void * unk_D8;
} S_800AEFD8_1;
/* payload in create_item_menu_child_at_position */


static s32 load_item_menu_display_resource(void *payload, s32 value);
extern void *link_item_menu_display_entries(void *entries);
extern void initialize_item_menu_list_display(void *payload, void *parent, s32 resource_id, s32 resource_data,
                          s32 x, s32 y, s32 context); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void register_node(void *object, void *callback);

/* Allocates menu display entries, copies the default vector, and shares it among the entries on success. */
static s32 load_item_menu_display_resource(void *object, s32 resource_id) {
    s32 success = 0;
    s32 handle = realloc_field_0_buffer((s32 *)((s8 *)object + 0xDC), resource_id, 8);

    *(s32 *)((s8 *)object + 0xD8) = handle;
    if (handle != 0) {
        *(s32 *)((s8 *)object + 0xBC) = display_vector_defaults[0];
        *(s32 *)((s8 *)object + 0xC0) = display_vector_defaults[1];
        *(s32 *)((s8 *)object + 0xC4) = display_vector_defaults[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(handle, (s8 *)object + 0xBC, 0x1A);
        success = 1;
    }
    return success;
}

/* Creates a linked item menu display at the requested position and cleans up if resource loading fails. */
void *create_item_menu_child_at_position(void *parent, s32 x, s32 y, s32 resource_id,
                    s32 resource_data, s32 context)
{
    ObjectNodeHeader *object;
    S_800AEFD8_1 *payload;

    object = allocate_list_node(0, parent);
    if (object != 0) {
        payload = NODE_BODY(object);
        if (load_item_menu_display_resource(payload, 0x1A) != 0) {
            object->sprite = (SpriteFrameState *)((u8 *)object + 0xE8);
            payload->unk_D4 = link_item_menu_display_entries(payload->unk_D8);
            initialize_item_menu_list_display(payload, parent, resource_id, resource_data, x, y, context);
            register_node(object, draw_tinted_node_sprites_scratch);
            object->update_callback = advance_item_menu_object_animation;
        } else {
            release_null_terminated_entries((u8 *)object + 0xFC);
            object->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            object = 0;
        }
    }
    return object;
}

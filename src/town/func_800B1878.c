#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800AEFD8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800AEFD8_0;   /* object in create_item_menu_child_at_position */

typedef struct S_800AEFD8_1 {
    u8 pad_00[0xD4];
    void * unk_D4;
    void * unk_D8;
} S_800AEFD8_1;   /* payload in create_item_menu_child_at_position */

extern void *allocate_list_node(s32 value, void *parent);
extern s32 load_item_menu_display_resource(void *payload, s32 value);
extern void *link_item_menu_display_entries(void *value);
extern void initialize_item_menu_list_display(void *payload, void *parent, s32 resource_id, s32 resource_data,
                          s32 x, s32 y, s32 context);
extern void register_node(void *object, void *callback);
extern void release_null_terminated_entries(void *address);
extern void draw_tinted_node_sprites_scratch(void);
extern void advance_item_menu_object_animation(void);


/* Create and initialize a child object at (x, y), marking allocation failure for cleanup. */
void *create_item_menu_child_at_position(void *parent, s32 x, s32 y, s32 resource_id,
                    s32 resource_data, s32 context)
{
    void *object;
    S_800AEFD8_1 *payload;

    object = allocate_list_node(0, parent);
    if (object != 0) {
        payload = (u8 *)object + 0x20;
        if (load_item_menu_display_resource(payload, 0x1A) != 0) {
            ((S_800AEFD8_0 *)object)->unk_0C = (u8 *)object + 0xE8;
            payload->unk_D4 = link_item_menu_display_entries(payload->unk_D8);
            initialize_item_menu_list_display(payload, parent, resource_id, resource_data, x, y, context);
            register_node(object, draw_tinted_node_sprites_scratch);
            ((S_800AEFD8_0 *)object)->unk_10 = advance_item_menu_object_animation;
        } else {
            release_null_terminated_entries((u8 *)object + 0xFC);
            ((S_800AEFD8_0 *)object)->unk_1E |= 0x8000;
            object_flag_block.flags |= 0x8000;
            object = 0;
        }
    }
    return object;
}

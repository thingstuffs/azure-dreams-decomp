#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "town/shop/monster_status_initialization_g00634.h"

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
void release_null_terminated_entries(u16 **entries);                      /* extern */
s32 link_monster_status_display_entries();                             /* extern */
s32 load_storage_display_resource();                 /* extern */
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr);
void invoke_object_first_callback(void *obj);

typedef struct S_800B6A0C_1 {
    u8 pad_00[0x94];
    s32 unk_94;
    s32 unk_98;
} S_800B6A0C_1;

/* Allocate and initialize an object, marking it for cleanup if setup fails. */
void *allocate_object_and_mark_failed_setup_for_cleanup(s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z) {
    S_800B6A0C_1 *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    state = ((void *)object) + 0x20;
    if (object != 0) {
        if (load_storage_display_resource(state, 0x18) != 0) {
            object->sprite = (void *) (((void *)object) + 0xA8);
            state->unk_94 = link_monster_status_display_entries(state->unk_98);
            initialize_entry_object(state, resource_id, slot_index, x, y, z);
            object->update_callback = &invoke_object_first_callback;
            register_node(object, &draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries(((void *)object) + 0xBC);
        object->flags = (u16) (object->flags | 0x8000);
        object = 0;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
    return object;
}

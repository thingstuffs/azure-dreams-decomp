#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

s32 register_node();           /* extern */
void release_null_terminated_entries(u16 **entries);                      /* extern */
s32 link_monster_status_display_entries();                             /* extern */
void initialize_entry_object(); /* extern */
s32 func_800B6990();                 /* extern */
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr);
void invoke_object_first_callback(void *obj);


typedef struct S_800B6A0C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800B6A0C_0;

typedef struct S_800B6A0C_1 {
    u8 pad_00[0x94];
    s32 unk_94;
    s32 unk_98;
} S_800B6A0C_1;

/* Allocate and initialize an object, marking it for cleanup if setup fails. */
void *allocate_object_and_mark_failed_setup_for_cleanup(s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z) {
    S_800B6A0C_1 *state;
    void *object;

    object = allocate_flagged_object_node(0);
    state = object + 0x20;
    if (object != 0) {
        if (func_800B6990(state, 0x18) != 0) {
            ((S_800B6A0C_0 *)object)->unk_0C = (void *) (object + 0xA8);
            state->unk_94 = link_monster_status_display_entries(state->unk_98);
            initialize_entry_object(state, resource_id, slot_index, x, y, z);
            ((S_800B6A0C_0 *)object)->unk_10 = &invoke_object_first_callback;
            register_node(object, &draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries(object + 0xBC);
        ((S_800B6A0C_0 *)object)->unk_1E = (u16) (((S_800B6A0C_0 *)object)->unk_1E | 0x8000);
        object = 0;
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
    return object;
}

#include "slus/saved_value_b98.h"

typedef struct {
    u8 pad_00[0x1E];
    u16 unk1E;
} S_80050E20_target;

typedef struct {
    u8 pad_00[0x1C];
    s32 unk1C;
    u8 pad_20[(0x28 - 0x1C) - 4];
    struct S_8004FE78_a0 *unk28;
    u8 pad_2C[(0xA0 - 0x28) - 4];
    S_80050E20_target *unkA0;
} S_80050E20_sub;

typedef struct S_80050E20 {
    u8 pad_00[0x1E];
    u16 unk1E;
    u8 pad_20[(0x20 - 0x1E) - 2];
    S_80050E20_sub unk20;
} S_80050E20;

typedef struct {
    s32 val;
    s32 pad[2];
} S_800814A0;

extern void release_null_terminated_entries(s32 *a0);
extern S_800814A0 object_flag_block;

/* Releases the attachment and effect parts, restores the saved value, and sets completion flags. */
void destroy_selection_menu_and_release_owner(S_80050E20 *object)
{
    S_80050E20_sub *object_state = &object->unk20;
    s32 global_flags;
    u16 object_flags;

    destroy_animated_selection_menu(object_state->unk28);
    object_state->unk28 = 0;
    selection_menu_saved_value = object_state->unk1C;
    release_null_terminated_entries((s32 *)(((u8 *)object) + 0x8C));
    object_state->unkA0->unk1E |= 0x8000;
    global_flags = object_flag_block.val;
    object_flags = object->unk1E;
    *(s32 *)0x800814A0 = global_flags | 0x8000;
    object->unk1E = object_flags | 0x8000;
}

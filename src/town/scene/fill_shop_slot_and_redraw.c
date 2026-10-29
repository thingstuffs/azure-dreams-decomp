#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
struct S_8046C8C4_0;

extern s32 copy_indexed_entry_value();
extern s32 func_8001796C(void);
extern void pass_entry_identifier_to_handler(struct S_8046C8C4_0 *table, s32 entry_index);
extern s32 func_800198D0(s32 flagIndex);

extern s32 D_800170B4;
extern s32 scene_update_state;
extern s32 scene_choice_index;
extern u8 *D_80019BBC;

/* Shop slot fill: take the next entry (or the default record) into slot arg1 and redraw. */
s32 fill_shop_slot_and_redraw(void *owner, s32 slot_index)
{
    s32 value;

    scene_update_state = 3;
    if (func_800198D0(F_veldil_dungeon_deatta) == 0) {
        return 1;
    }

    value = func_8001796C();
    if (value != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)owner + 0x10) + slot_index * 0x10 + 8) =
            copy_indexed_entry_value(value);
    } else {
        *(s32 *)((u8 *)*(void **)((u8 *)owner + 0x10) + slot_index * 0x10 + 8) =
            (s32)&D_800170B4;
    }

    D_80019BBC[5] = value;
    scene_choice_index = value;
    pass_entry_identifier_to_handler(owner, slot_index);
    return 0;
}

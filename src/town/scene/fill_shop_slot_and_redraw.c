#include "script_symbols.h"
#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene/choice_data.h"
#include "town/scene.h"
#include "town/scene/entry_requests.h"
#include "town/player/state.h"
struct S_8046C8C4_0;

extern s32 copy_indexed_entry_value();

extern s32 D_800170B4;
extern u8 *D_80019BBC;

/* Shop slot fill: take the next entry (or the default record) into slot arg1 and redraw. */
s32 fill_shop_slot_and_redraw(void *owner, s32 slot_index)
{
    s32 value;

    scene_update_state = 3;
    if (get_script_flag_mask(F_veldil_dungeon_deatta) == 0) {
        return 1;
    }

    value = find_first_enabled_entry_id();
    if (value != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)owner + 0x10) + slot_index * 0x10 + 8) =
            copy_indexed_entry_value(value);
    } else {
        *(s32 *)((u8 *)*(void **)((u8 *)owner + 0x10) + slot_index * 0x10 + 8) =
            (s32)&D_800170B4;
    }

    D_80019BBC[5] = value;
    scene_choice_index = value;
    set_flag_from_indexed_entry(owner, slot_index);
    return 0;
}

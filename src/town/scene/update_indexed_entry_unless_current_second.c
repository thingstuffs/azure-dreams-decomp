#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town.h"

typedef void (*TownCallback)(s32, s32);

/* Checks town event conditions and invokes the object callback when they are met. */
s32 update_indexed_entry_unless_current(void) {
    TownServiceTable *callback_owner;
    s32 status;

    set_script_flag_94c();
    if (town_table_contains_first_byte_b(0xB) != 0) {
        set_script_flag_bit(F_sbs32_pad17);
    }

    if (get_script_flag_mask(F_sbs32_pad32) == 0) {
        set_script_flag_bit(F_sbs32_pad28);
        return 1;
    }

    if (get_script_flag_mask(F_sbs32_pad28) == 0) {
        set_script_flag_bit(F_sbs32_pad24);
        callback_owner = town_scene_root->services;
        (*(TownCallback *)((u8 *)callback_owner + 0x2F8))(0xE, 0x200);
        status = 0;
    } else {
        status = 1;
    }
    return status;
}

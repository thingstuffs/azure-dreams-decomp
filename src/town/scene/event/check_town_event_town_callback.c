#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "shared/town_root.h"
#include "town/player/state.h"

extern s32 town_table_contains_first_byte_b(s32);

typedef void (*TownCallback)(s32, s32);

/* Checks town event conditions and invokes the town callback if they allow it. */
s32 check_town_event_town_callback(void) {
    s8 *callback_object;

    set_script_flag_94c();
    if (town_table_contains_first_byte_b(0xB) != 0) {
        set_script_flag_bit(F_sbs32_pad17);
    }

    if ((get_script_flag_mask(F_sbs32_pad32) == 0) ||
        ((get_script_flag_mask(F_sbs32_pad30) != 0) && (get_script_flag_mask(F_sbs32_pad17) != 0))) {
        set_script_flag_bit(F_sbs32_pad29);
        return 1;
    }

    callback_object = ((s8 *)(town_scene_root->services));
    (*(TownCallback *)(callback_object + 0x2F8))(0xF, 0x200);
    return 0;
}

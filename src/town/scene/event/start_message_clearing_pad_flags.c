#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene/event.h"
#include "town/player/state.h"

extern M2C_UNK D_8001D9D4;


/* Initialize state, process two entries, set the data pointer, and invoke the callback. */
s32 start_message_clearing_pad_flags(void) {
    set_script_flag_sbs32_pad34();
    clear_script_flag_bit(F_sbs32_pad11);
    clear_script_flag_bit(F_sbs32_pad12);
    town_scene_root->position->unk_40 = &D_8001D9D4;
    town_scene_root->services->callback_2F8(0xE, 0x200);
    return 0;
}

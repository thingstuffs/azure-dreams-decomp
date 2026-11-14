#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/event.h"
#include "town/player/state.h"

extern M2C_UNK D_80017A00;
extern s32 *D_80017A98;

/* Ask the scene object for its mode and raise the matching 0xBE9 event, then arm the next handler. */
void update_sbs48_pad15_flag(void) {
    if (town_scene_root->services->callback_334(0) != 5) {
        set_script_flag_bit(F_sbs48_pad15);
    } else {
        clear_script_flag_bit(F_sbs48_pad15);
    }
    D_80017A98 = &D_80017A00;
}

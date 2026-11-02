#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/player/state.h"

typedef s32 (*Callback)(s32);

/* Triggers 0xA7 when the state callback returns one and 0xA7 is inactive. */
s32 triggers_x_7_state_callback(void) {
    if (((Callback)(town_scene_root->services->callback_2D4))(0) != 1) {
        return 0;
    }
    if (get_script_flag_mask(F_30kinko_talk) != 0) {
        return 0;
    }
    set_script_flag_bit(F_30kinko_talk);
    return 1;
}

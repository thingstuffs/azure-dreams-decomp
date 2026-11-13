#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/player/state.h"

/* Triggers 0xA6 when the state callback returns zero and 0xA6 is inactive. */
s32 trigger_kinko_10_talk(void)
{
    if ((*(s32 (**)(s32))(((void *)(town_scene_root->services)) + 0x2D4))(0) == 0) {
        if (get_script_flag_mask(F_10kinko_talk) == 0) {
            set_script_flag_bit(F_10kinko_talk);
            return 1;
        }
    }
    return 0;
}

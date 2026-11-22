#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/script_flags.h"
#include "script_symbols.h"

s32 set_kinko_talk_flag_if_rank_two(void)
{
    if (town_scene_root->services->callback_2D4(0) == 2 &&
        !get_script_flag_mask(F_60kinko_talk)) {
        set_script_flag_bit(F_60kinko_talk);
        return 1;
    }
    return 0;
}

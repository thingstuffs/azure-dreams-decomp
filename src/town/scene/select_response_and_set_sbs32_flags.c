#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene.h"

extern s32 bar_okami_give_cape_event;


/* Processes event conditions and returns the corresponding data pointer, or null. */
void *select_response_and_set_sbs32_flags(void) {
    if (check_callback_record_bytes(0xD, 6) != 0) {
        town_scene_root->services->callback_078(0);
        set_script_flag_bit(F_sbs32_pad02);
        set_script_flag_bit(F_sbs32_pad03);
        set_script_flag_bit(F_sbs32_pad04);
        set_script_flag_bit(F_sbs32_pad05);
        set_script_flag_bit(F_sbs32_pad06);
        clear_script_flag_bit(F_sbs32_pad25);
        return &bar_okami_give_cape_event;
    }
    if (get_script_flag_mask(F_sbs32_pad06) != 0) {
        return (s32 *)((s8 *)&bar_okami_give_cape_event + 0x21A);
    }
    return 0;
}

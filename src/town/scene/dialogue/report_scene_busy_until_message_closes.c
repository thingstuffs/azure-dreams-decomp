#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/dialogue.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/service.h"

typedef s32 (*TownCallback)(s32, s32);

/* Scene step: while message 0x932 is up report busy, else close it and post event 0xE. */
s32 report_scene_busy_until_message_closes(void) {
    s32 result;

    set_script_flag_sbs32_pad34();
    if (get_script_flag_mask(F_sbs32_pad08) == 0) {
        call_scene_service_2f4_fixed();
        ((TownCallback)(town_scene_root->services->callback_2F8))(0xE, 0x200);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

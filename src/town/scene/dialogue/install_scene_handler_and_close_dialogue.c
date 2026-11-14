#include "town/scene.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/dialogue.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

typedef void (*TownCallback)(s32, s32);

extern s8 D_8001BCB4[];

/* Scene entry: install the D_8001BCB4 handler, close the dialogue and post event 0xE. */
s32 install_scene_handler_and_close_dialogue(void) {
    set_script_flag_sbs32_pad34();
    town_scene_root->position->unk_40 = D_8001BCB4;
    call_scene_service_2f4_fixed();
    ((TownCallback)(town_scene_root->services->callback_2F8))(0xE, 0x200);
    return 0;
}

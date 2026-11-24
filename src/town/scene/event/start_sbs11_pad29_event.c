#include "town/scene/service.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene.h"


/* Set F_sbs11_pad31 and F_sbs11_pad29, mirror the pad32 flag, then run services 0x340 and 0x218. */
void start_sbs11_pad29_event(void) {
    set_script_flag_bit(F_sbs11_pad31);
    set_script_flag_bit(F_sbs11_pad29);
    mirror_sbs11_pad32_flag();
    town_scene_root->services->callback_340(0);
    town_scene_root->services->callback_218(sbs11_pad29_service_record);
}

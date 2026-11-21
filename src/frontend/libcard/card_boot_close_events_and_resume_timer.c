#include "shared/runtime_dispatch.h"
#include "slus/gp_d92c_owned.h"
#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "slus/animation_tick_data.h"

#include "modules/main_server_ship_interfaces.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard.h"
#include "slus.h"

/* Set state 2, run setup, select sound behavior, and clear the high flag bit. */
void card_boot_close_events_and_resume_timer(void) {
    animation_tick_scale = 2;
    card_boot_close_events();
    open_timer_2_update_event();
    if (runtime_dispatch_state.mode == 1) {
        SD_Call(0x200);
    } else {
        scene_music_hold = 0;
    }
    runtime_dispatch_state.flags0F &= 0x7F;
}

#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"
#include "town/player/state.h"

/* Dispatches mode 2, then invokes the handler for 0x596. */
void run_service_1f4_then_event_596(void) {
    town_scene_root->services->callback_1F4(2);
    clear_script_flag_bit(F_sbs10_pad30);
}

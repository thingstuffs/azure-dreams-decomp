#include "town/scene.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/resource.h"





/* Run both setup routines and invoke the state callback with 0xE and 0x200. */
s32 run_setup_routines_state_callback(void) {
    set_script_flag_sbs32_pad34();
    init_okami_give_cape_state();
    town_scene_root->services->callback_2F8(0xE, 0x200);
    return 0;
}

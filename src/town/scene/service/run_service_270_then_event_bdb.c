#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"



s32 func_80017684(s32);
extern u8 D_80017AD0;


/* Pass D_80017AD0 to the state callback, then run operation 0xBDB. */
void run_service_270_then_event_bdb(void) {
    town_scene_root->services->callback_270(&D_80017AD0);
    func_80017684(F_sbs48_pad01);
}

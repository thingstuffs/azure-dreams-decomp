#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



s32 func_80016CC4(void);
s32 func_8001A5CC(s32);
extern M2C_UNK D_8001D9D4;


/* Initialize state, process two entries, set the data pointer, and invoke the callback. */
s32 run_events_935_936_set_data(void) {
    func_80016CC4();
    func_8001A5CC(F_sbs32_pad11);
    func_8001A5CC(F_sbs32_pad12);
    ((TownPositionState *)town_scene_root->position)->unk_40 = &D_8001D9D4;
    town_scene_root->services->callback_2F8(0xE, 0x200);
    return 0;
}

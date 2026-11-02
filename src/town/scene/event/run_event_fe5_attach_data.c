#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/event.h"
#include "town/player/state.h"

extern s32 D_80017D64;

/* Run operation 0xFE5 and attach D_80017D64 to the state object. */
s32 run_event_fe5_attach_data(void) {
    void *ptr;
    s32 *value;

    clear_script_flag_bit(F_gosh0000);
    ptr = town_scene_root;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: town/func_806F1A08). */
    do {
        value = &D_80017D64;
        ptr = ((Rec_D_80016000 *)ptr)->position;
    } while (0);
    ((TownPositionState *)ptr)->unk_40 = value;
    return 0;
}

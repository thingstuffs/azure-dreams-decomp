#include "script_symbols.h"
#include "modules/town_ovl_3fe0d0_p00.h"

/* Installs scene state and a cell handler, invokes town callback 0x3B0/0x100, and updates F_gy_mon_sw. */
void advance_floor_event_counter(void) {
    void *state_data;
    s32 call_code;
    TownServiceTable *dispatch_table;

    call_code = 0x3B0;
    state_data = &D_8001802A;
    ((TownPositionState *)((Rec_D_80016000 *)town_scene_root)->position)->unk_40 = state_data;
    dispatch_table = *(void **)((u8 *)town_scene_root + 0x20);
    *(s32 **)&D_8001794C.pointers[0] = &D_800177C8;
    ((TownCall)dispatch_table->callback_2EC)(call_code, 0x100);
    func_800175E0(F_gy_mon_sw);
    *(void **)((s8 *)((Rec_D_80016000 *)town_scene_root)->event_data
        + ((Rec_D_80016000 *)town_scene_root)->entry_index * 8) = &D_8001624C;
}

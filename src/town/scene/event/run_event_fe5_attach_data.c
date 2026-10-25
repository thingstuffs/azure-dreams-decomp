#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern void func_800177BC(s32 bit_index);
extern s32 D_80017D64;

/* Run operation 0xFE5 and attach D_80017D64 to the state object. */
s32 run_event_fe5_attach_data(void) {
    void *ptr;
    s32 *value;

    func_800177BC(F_gosh0000);
    ptr = town_scene_root;
    do {
        value = &D_80017D64;
        ptr = ((Rec_D_80016000 *)ptr)->position;
    } while (0);
    ((TownPositionState *)ptr)->unk_40 = value;
    return 0;
}

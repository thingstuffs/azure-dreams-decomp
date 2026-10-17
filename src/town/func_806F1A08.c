#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 func_800177BC();
extern s32 D_80017D64;

/* Run operation 0xFE5 and attach D_80017D64 to the state object. */
s32 func_806F1A08(void) {
    void *ptr;
    s32 *value;

    func_800177BC(0xFE5);
    ptr = D_80016000;
    do {
        value = &D_80017D64;
        ptr = ((Rec_D_80016000 *)ptr)->unk_1C;
    } while (0);
    ((TownPositionState *)ptr)->unk_40 = value;
    return 0;
}

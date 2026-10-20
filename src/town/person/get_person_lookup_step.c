#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AAE98_arg0.h"

s32 read_map_cell_at_world_position();                        /* extern */


/* Returns 0x18 for lookup codes in three special ranges, or 0x60 otherwise. */
s32 get_person_lookup_step(Rec_func_800AAE98_arg0 *coordinates) {
    s32 lookupCode;

    lookupCode = read_map_cell_at_world_position(coordinates->unk_02, coordinates->unk_06) & 0xFFFF;
    if ((u32) (lookupCode - 0xC0) < 3U) {
        return 0x18;
    }
    if ((u32) (lookupCode - 0xC7) < 3U) {
        return 0x18;
    }
    if ((u32) (lookupCode - 0xCE) < 3U) {
        return 0x18;
    }
    lookupCode = 0;
    return 0x60;
}


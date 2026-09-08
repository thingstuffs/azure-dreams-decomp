#include "common.h"

extern void *func_80017BE8(s32, s32);
extern u8 D_800170C8[];
extern u8 D_8001BA8C[];
extern u8 D_8001BA91[];

/* Selects data for the requested kind or falls back to the lookup arguments. */
void *func_80017C60(s32 lookup_id, s32 lookup_index, s32 data_kind) {
    if (data_kind == 1) {
        return D_800170C8;
    }
    if (data_kind == 5) {
        return D_8001BA91;
    }
    if (data_kind == 4) {
        return D_8001BA8C;
    }
    return func_80017BE8(lookup_id, lookup_index);
}

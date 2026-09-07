#include "common.h"

/* D_80083D08: array of 6 8-byte entries; field flags4 (offset 4) is a status/flags
 * short whose bit0 is cleared here. Layout reconciled with siblings that access the
 * same array (func_8004827C / func_800481E0 / func_80047B80 / func_80047BC0). */
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 flags4;
    s16 id6;
} S_80048224;

extern S_80048224 D_80083D08[6];
extern s32 func_80047BC0(s32 arg0);

/* Clear flag bit 0 in the slot matching slot_id and return 1 if found, else 0. */
s32 func_80048224(s16 slot_id) {
    s32 slot_index = func_80047BC0(slot_id);
    S_80048224 *slot;

    if (slot_index != -1) {
        slot = &D_80083D08[slot_index];
        slot->flags4 &= ~1;
        return 1;
    }
    return 0;
}

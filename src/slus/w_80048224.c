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

/* Look up the D_80083D08 slot whose id6 matches arg0 (via func_80047BC0); if found,
 * clear bit0 of that slot's flags4 and return 1, else return 0. */
s32 func_80048224(s16 arg0) {
    s32 idx = func_80047BC0(arg0);
    S_80048224 *p;

    if (idx != -1) {
        p = &D_80083D08[idx];
        p->flags4 &= ~1;
        return 1;
    }
    return 0;
}

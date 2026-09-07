#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 *unk4;
    u8 pad8[20];
} S_80086A40;

extern S_80086A40 D_80086A40[];

/* Looks up D_80086A40[idx]; if unk0 == -1 the slot is invalid and returns -1,
 * otherwise copies a fixed 32-byte block from *unk4 into dst and returns 0. */
s32 func_8005B470(s16 idx, u8 *dst) {
    S_80086A40 *base;
    S_80086A40 *ent;
    u8 *src;
    u32 i;

    base = D_80086A40;
    ent = &base[idx];
    if (ent->unk0 == -1) {
        return -1;
    }

    src = ent->unk4;
    i = 0;
    do {
        *dst = *src;
        src++;
        i++;
        dst++;
    } while (i < 0x20);

    return 0;
}

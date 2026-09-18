#include "common.h"

typedef union {
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
    } bytes;
    u32 word;
} TownRecord;

extern TownRecord D_80100AA0[20];

/* Inserts a record into the first free slot, discarding the first record if full. */
void func_800A0404(TownRecord *record) {
    TownRecord *dst;
    s32 slot;

    slot = 0;
    dst = D_80100AA0;
loop:
    if (dst->bytes.unk1 != 0) {
        slot++;
        dst++;
        if (slot < 20) {
            goto loop;
        }
    }

    if (slot == 20) {
        for (slot = 0; slot < 19; slot++) {
            D_80100AA0[slot] = D_80100AA0[slot + 1];
        }
    }

    D_80100AA0[slot].bytes.unk0 = record->bytes.unk0;
    D_80100AA0[slot].bytes.unk1 = record->bytes.unk1;
    D_80100AA0[slot].bytes.unk2 = record->bytes.unk2;
    D_80100AA0[slot].bytes.unk3 = record->bytes.unk3;
}

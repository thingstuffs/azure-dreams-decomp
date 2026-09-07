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
    TownRecord *src;
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
        register TownRecord *base ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        slot = 0;
        base = D_80100AA0;
        dst = base;
        src = base + 1;
        do {
            *dst = *src;
            src++;
            slot++;
            dst++;
        } while (slot < 19);
    }

    D_80100AA0[slot].bytes.unk0 = record->bytes.unk0;
    D_80100AA0[slot].bytes.unk1 = record->bytes.unk1;
    D_80100AA0[slot].bytes.unk2 = record->bytes.unk2;
    D_80100AA0[slot].bytes.unk3 = record->bytes.unk3;
}

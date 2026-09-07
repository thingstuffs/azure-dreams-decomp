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

void func_800A0404(TownRecord *arg0) {
    TownRecord *dst;
    TownRecord *src;
    s32 i;

    i = 0;
    dst = D_80100AA0;
loop:
    if (dst->bytes.unk1 != 0) {
        i++;
        dst++;
        if (i < 20) {
            goto loop;
        }
    }

    if (i == 20) {
        register TownRecord *base ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        i = 0;
        base = D_80100AA0;
        dst = base;
        src = base + 1;
        do {
            *dst = *src;
            src++;
            i++;
            dst++;
        } while (i < 19);
    }

    D_80100AA0[i].bytes.unk0 = arg0->bytes.unk0;
    D_80100AA0[i].bytes.unk1 = arg0->bytes.unk1;
    D_80100AA0[i].bytes.unk2 = arg0->bytes.unk2;
    D_80100AA0[i].bytes.unk3 = arg0->bytes.unk3;
}

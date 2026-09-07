#include "common.h"

extern s32 func_800478B8(void *arg0);

typedef struct {
    s16 value;
    s16 pad_02[4];
} DungeonActive;

extern DungeonActive D_80025B60;
extern s32 D_800814A0;

typedef struct {
    u8 pad_00[0xC];
    s8 unk_C;
    s8 unk_D;
    s8 unk_E;
    u8 pad_0F[5];
    u16 flags_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} DungeonEffect;

void func_80024C0C(void *arg0, s32 arg1, DungeonEffect *arg2) {
    register u8 *entity ASM_REG("$17") = arg0;
    register DungeonEffect *effect ASM_REG("$16") = arg2;
    register u16 state ASM_REG("$3");
#ifndef NON_MATCHING
    register u8 *activePage ASM_REG("$2") = (u8 *)0x80020000;
#endif
    u16 value;
    s32 quotient;

    ASM_KEEP(entity);
    ASM_KEEP(effect);
#ifndef NON_MATCHING
    ASM_KEEP(activePage);
#endif
    do { state = *(u16 *)(entity + 0x5A); } while (0);
#ifdef NON_MATCHING
    do { D_80025B60.value = 1; } while (0);
#else
    do { *(s16 *)(activePage + 0x5B60) = 1; } while (0);
#endif
    if (!(state & 3)) {
        func_800478B8(effect);
    }

    value = effect->unk_1C + 0x32;
    effect->unk_1C = value;
    if (value >= 0x2001) {
        effect->unk_1C = 0x2000;
    }

    value = effect->unk_1E + 0x32;
    effect->unk_1E = value;
    if (value >= 0x2001) {
        effect->unk_1E = 0x2000;
    }

    value = *(u16 *)(entity + 0x5A) - 1;
    quotient = ((s32)(value << 16) >> 9) / *(s16 *)(entity + 0x5C);
    *(u16 *)(entity + 0x5A) = value;
    effect->unk_E = quotient;
    effect->unk_D = quotient;
    effect->unk_C = quotient;

    if (*(s16 *)(entity + 0x5A) <= 0) {
        *(u16 *)(entity - 2) |= 0x8000;
#ifdef NON_MATCHING
        D_800814A0 |= 0x8000;
#else
        {
            register u8 *page ASM_REG("$3") = (u8 *)0x80080000;
            ASM_KEEP(page);
            *(s32 *)(page + 0x14A0) |= 0x8000;
        }
#endif
    }
    if (effect->flags_14 & 0x8000) {
        *(u16 *)(entity - 2) |= 0x8000;
#ifdef NON_MATCHING
        D_800814A0 |= 0x8000;
#else
        {
            register u8 *page ASM_REG("$3") = (u8 *)0x80080000;
            ASM_KEEP(page);
            *(s32 *)(page + 0x14A0) |= 0x8000;
        }
#endif
    }
}

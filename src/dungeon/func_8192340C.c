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

/* Advance the effect, fade it as its timer runs down, and flag it for removal when finished. */
void func_80024C0C(void *entity_data, s32 unused, DungeonEffect *effect_data) {
    u8 *entity = entity_data;
    DungeonEffect *effect = effect_data;
    register u16 ticks_left ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
    u8 *active_page = (u8 *)0x80020000;
#endif
    u16 updated_value;
    s32 fade_level;

    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
#endif
    do { ticks_left = *(u16 *)(entity + 0x5A); } while (0);
#ifdef NON_MATCHING
    do { D_80025B60.value = 1; } while (0);
#else
    do { *(s16 *)(active_page + 0x5B60) = 1; } while (0);
#endif
    if (!(ticks_left & 3)) {
        func_800478B8(effect);
    }

    updated_value = effect->unk_1C + 0x32;
    effect->unk_1C = updated_value;
    if (updated_value >= 0x2001) {
        effect->unk_1C = 0x2000;
    }

    updated_value = effect->unk_1E + 0x32;
    effect->unk_1E = updated_value;
    if (updated_value >= 0x2001) {
        effect->unk_1E = 0x2000;
    }

    updated_value = *(u16 *)(entity + 0x5A) - 1;
    fade_level = ((s32)(updated_value << 16) >> 9) / *(s16 *)(entity + 0x5C);
    *(u16 *)(entity + 0x5A) = updated_value;
    effect->unk_E = fade_level;
    effect->unk_D = fade_level;
    effect->unk_C = fade_level;

    if (*(s16 *)(entity + 0x5A) <= 0) {
        *(u16 *)(entity - 2) |= 0x8000;
#ifdef NON_MATCHING
        D_800814A0 |= 0x8000;
#else
        {
            u8 *flags_page = (u8 *)0x80080000;
            *(s32 *)(flags_page + 0x14A0) |= 0x8000;
        }
#endif
    }
    if (effect->flags_14 & 0x8000) {
        *(u16 *)(entity - 2) |= 0x8000;
#ifdef NON_MATCHING
        D_800814A0 |= 0x8000;
#else
        {
            u8 *flags_page = (u8 *)0x80080000;
            *(s32 *)(flags_page + 0x14A0) |= 0x8000;
        }
#endif
    }
}

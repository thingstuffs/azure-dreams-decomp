#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80171498_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80171498_0;   /* effect in func_80171498 */

typedef struct S_80171498_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80171498_1;   /* arg0 in func_80171498 */

typedef struct S_80171498_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80171498_2;   /* source in func_80171498 */

typedef struct S_80171498_3 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x1E];
    s16 unk_5A;
    u8 pad_5C[0x2];
    s16 unk_5E;
    u8 pad_60[0x2];
    s16 unk_62;
} S_80171498_3;   /* base in func_80171498 */

typedef struct S_80171498_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80171498_4;   /* ((S_80171498_0 *)effect)->unk_08 in func_80171498 */

typedef struct S_80171498_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171498_5;   /* ((S_80171498_1 *)arg0)->unk_08 in func_80171498 */



void *func_8003FD64();
s32 func_8003DE58();
s32 func_8004491C();
s32 rand();
s32 func_801710B8();

extern u8 D_80170ED8[];
extern u8 D_801712C4[];

/* Creates an offset effect, advances it ten steps, and assigns a random color. */
void func_80171498(
    void *parent, s16 initial_14, s32 unused, s16 initial_32,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    s32 held_offset_x = offset_x;   /* MATCH pin: load-bearing for the whole function shape */
    s32 held_offset_y = offset_y;
    s32 held_offset_z = offset_z;
    volatile u16 source_offset_x;
    volatile u16 source_offset_y;
    volatile u16 source_offset_z;
    s16 step;
    s32 color_high;
    s32 color_mid;
    void *source_data;
    void *effect;
    void *effect_data;

    effect = func_8003FD64(0x211, parent);
    if (effect != NULL) {
        ((S_80171498_0 *)effect)->unk_10 = D_801712C4;

        ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_02 =
            ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_02 + held_offset_x;
        ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_06 =
            ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_06 + held_offset_y;
        ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_0A =
            ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_0A + held_offset_z;
        ASM_KEEP(held_offset_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(held_offset_y);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(held_offset_z);   /* MATCH pin: retail callee-saved set / frame layout depends on it */

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (func_8003DE58(((S_80171498_2 *)source_data)->unk_08, source_data, &source_offset_x, 0) != 0) {
            ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_02 += source_offset_x;
            ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_06 += source_offset_y;
            ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_0A += source_offset_z;
        }

        effect_data = (u8 *)effect + 0x20;
        ((S_80171498_3 *)effect_data)->unk_5A = ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_02;
        ((S_80171498_3 *)effect_data)->unk_5E = ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_06;
        ((S_80171498_3 *)effect_data)->unk_62 = ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_0A;

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (func_8003DE58(((S_80171498_2 *)source_data)->unk_08, source_data, &source_offset_x, 0) != 0) {
            (*(s16 *)((u8 *)effect_data + 0x5A)) += source_offset_x;
            (*(s16 *)((u8 *)effect_data + 0x5E)) += source_offset_y;
            ((S_80171498_3 *)effect_data)->unk_62 += source_offset_z;
        }

        ((S_80171498_3 *)effect_data)->unk_36 = ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_02;
        ((S_80171498_3 *)effect_data)->unk_38 = ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_06;
        ((S_80171498_3 *)effect_data)->unk_3A = ((S_80171498_5 *)(((S_80171498_1 *)parent)->unk_08))->unk_0A;

        step = 0;
        do {
            func_801710B8(effect_data, ((S_80171498_0 *)effect)->unk_08, ((S_80171498_0 *)effect)->unk_0C);
            step++;
        } while (step < 10);

        ((S_80171498_3 *)effect_data)->unk_14 = initial_14;
        ((S_80171498_3 *)effect_data)->unk_32 = initial_32;
        func_8004491C(effect, D_80170ED8);

        color_high = rand();
        color_mid = rand();
        ((S_80171498_3 *)effect_data)->unk_00 =
            ((color_high & 0xFF) << 16) |
            ((color_mid & 0xFF) << 8) |
            (rand() & 0xFF);
        ((S_80171498_3 *)effect_data)->unk_08 = ((S_80171498_3 *)effect_data)->unk_00;
    }
}

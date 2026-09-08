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

void func_80171498(
    void *arg0, s16 arg1, s32 arg2, s16 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    s32 held_arg4 = arg4;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 held_arg5 = arg5;
    s32 held_arg6 = arg6;
    volatile u16 sp10;
    volatile u16 sp12;
    volatile u16 sp14;
    s16 counter;
    s32 color0;
    s32 color1;
    void *source;
    void *effect;
    void *base;

    effect = func_8003FD64(0x211, arg0);
    if (effect != NULL) {
        ((S_80171498_0 *)effect)->unk_10 = D_801712C4;

        ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_02 =
            ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_02 + held_arg4;
        ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_06 =
            ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_06 + held_arg5;
        ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_0A =
            ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_0A + held_arg6;
        ASM_KEEP(held_arg4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg5);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg6);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        source = ((S_80171498_1 *)arg0)->unk_0C;
        if (func_8003DE58(((S_80171498_2 *)source)->unk_08, source, &sp10, 0) != 0) {
            ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_02 += sp10;
            ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_06 += sp12;
            ((S_80171498_4 *)(((S_80171498_0 *)effect)->unk_08))->unk_0A += sp14;
        }

        base = (u8 *)effect + 0x20;
        ((S_80171498_3 *)base)->unk_5A = ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_02;
        ((S_80171498_3 *)base)->unk_5E = ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_06;
        ((S_80171498_3 *)base)->unk_62 = ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_0A;

        source = ((S_80171498_1 *)arg0)->unk_0C;
        if (func_8003DE58(((S_80171498_2 *)source)->unk_08, source, &sp10, 0) != 0) {
            (*(s16 *)((u8 *)base + 0x5A)) += sp10;
            (*(s16 *)((u8 *)base + 0x5E)) += sp12;
            ((S_80171498_3 *)base)->unk_62 += sp14;
        }

        ((S_80171498_3 *)base)->unk_36 = ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_02;
        ((S_80171498_3 *)base)->unk_38 = ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_06;
        ((S_80171498_3 *)base)->unk_3A = ((S_80171498_5 *)(((S_80171498_1 *)arg0)->unk_08))->unk_0A;

        counter = 0;
        do {
            func_801710B8(base, ((S_80171498_0 *)effect)->unk_08, ((S_80171498_0 *)effect)->unk_0C);
            counter++;
        } while (counter < 10);

        ((S_80171498_3 *)base)->unk_14 = arg1;
        ((S_80171498_3 *)base)->unk_32 = arg3;
        func_8004491C(effect, D_80170ED8);

        color0 = rand();
        color1 = rand();
        ((S_80171498_3 *)base)->unk_00 =
            ((color0 & 0xFF) << 16) |
            ((color1 & 0xFF) << 8) |
            (rand() & 0xFF);
        ((S_80171498_3 *)base)->unk_08 = ((S_80171498_3 *)base)->unk_00;
    }
}

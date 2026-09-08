#include "common.h"

typedef struct S_80098CF8_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x6];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_80098CF8_0;   /* s0 in func_80098CF8 */

typedef struct S_80098CF8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
} S_80098CF8_1;   /* s2 in func_80098CF8 */

typedef struct S_80098CF8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098CF8_2;   /* primitive in func_80098CF8 */

typedef struct S_80098CF8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80098CF8_3;   /* s5 in func_80098CF8 */

typedef struct S_80098CF8_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80098CF8_4;   /* s4 in func_80098CF8 */

typedef struct S_80098CF8_5 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x4];
    s32 unk_98;
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    u8 pad_AA[0x2];
    s16 unk_AC;
} S_80098CF8_5;   /* state in func_80098CF8 */

typedef struct S_80098CF8_6 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x20];
    void * unk_BC;
    u8 pad_C0[0x64];
    s32 unk_124;
} S_80098CF8_6;   /* s3 in func_80098CF8 */

typedef struct S_80098CF8_7 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_80098CF8_7;   /* (void *)a1 in func_80098CF8 */



extern void func_80048A44();
extern void func_800982A8();
extern void func_80098614();
extern void func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_8009929C();
extern s32 func_80099368();
extern void func_800A56E0();
extern void func_800A5720();
extern void *func_800A8608();

extern u8 D_80081484[];
extern s16 D_80083228;
extern u8 D_8008D470[];
extern u8 D_800DD0B8[8];
extern u8 D_800E08CC[];
extern u8 D_800E08E5[];
extern u8 D_800E08F1[];
extern u8 D_800E0919[];

void *func_80098CF8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *s3 = arg0;
    s32 s6 = arg1;
    void *s5 = arg2;
    register void *s2 ASM_REG("$18") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *s4 = arg0;
    register void *s0;
    s32 s1;
    void *object;
    void *primitive;
    void *state;
    register void *message ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 value;

    s0 = D_80081484;
    if ((s2 != s0) && (((S_80098CF8_0 *)s0)->unk_01 != 0)) {
        s1 = func_800990FC();
        value = func_8009929C(8, s1);
        value = func_80099368(s2, value);
        value = func_80099194(D_800E08CC, value);
        value = func_80099368(s0, value);
        message = D_800E08E5;
print_message:
        value = func_80099194(message, value);
        func_80099290(value);
        func_800A5720(s1);
        ASM_KEEP(s3);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(s6);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(s5);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(s2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(s4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        goto return_zero;
    }

    if (((S_80098CF8_1 *)s2)->unk_00.at03.v & 0x20) {
        s1 = func_800990FC();
        s0 = (void *)func_8009929C(8, s1);
        if (((S_80098CF8_1 *)s2)->unk_00.at03.v & 0x40) {
            func_800A56E0(0x70A);
            value = func_80099368(s2, s0);
            message = D_800E08F1;
            goto print_message;
        }

        value = func_80099368(s2, s0);
        value = func_80099194(D_800E0919, value);
        func_80099290(value);
        func_800A5720(s1);
        if (((S_80098CF8_1 *)s2)->unk_00.at01.v == 0x11) {
            func_80098614(s4, s2);
            goto allocate;
        }
        func_800982A8(s4, s2);
        goto allocate;
    }
    goto allocate;

allocate:
    object = func_800A8608((u8 *)s3 - 0x20, s2, 0, 0, 0);
    s0 = object;
    if (s0 == 0) {
        goto return_zero;
    }

    {
    s32 coord;

    ((S_80098CF8_0 *)s0)->unk_10 = D_8008D470;
    primitive = ((S_80098CF8_0 *)s0)->unk_08;
    ((S_80098CF8_2 *)primitive)->unk_02 = (((S_80098CF8_3 *)s5)->unk_24 << 6) + 0x20;
    ((S_80098CF8_2 *)primitive)->unk_06 = (((S_80098CF8_3 *)s5)->unk_25 << 6) + 0x20;
    coord = ((S_80098CF8_4 *)s4)->unk_88;
    message = s5;
    ((S_80098CF8_2 *)primitive)->unk_0A = coord - 0x30;

    state = (u8 *)s0 + 0x20;
    {
    register s32 a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 a2;

    a1 = ((S_80098CF8_1 *)s2)->unk_00.at00.v;
    ((S_80098CF8_5 *)state)->unk_AC = 1;
    ((S_80098CF8_5 *)state)->unk_90 = message;
    ((S_80098CF8_5 *)state)->unk_8C = s6;
    ((S_80098CF8_5 *)state)->unk_A8 = 6;
    ((S_80098CF8_5 *)state)->unk_98 = a1;
    a1 = 0x80080000;
    ASM_KEEP(a1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_80098CF8_6 *)s3)->unk_BC = s2;
    a2 = ((S_80098CF8_1 *)s2)->unk_00.at00.v;
    ((S_80098CF8_5 *)state)->unk_9C = (u8 *)a1 + 0x1484;
    ((S_80098CF8_6 *)s3)->unk_8C = 0;
    ((S_80098CF8_6 *)s3)->unk_124 = 0;
    ((S_80098CF8_7 *)((void *)a1))->unk_1484 = a2;
    a1 = (s32)D_800DD0B8;
    ((S_80098CF8_6 *)s3)->unk_9A = 0x1B;
    ((S_80098CF8_6 *)s3)->unk_9B = 0;
    (*(void * *)((u8 *)message + 0x2C)) = (void *)a1;

    func_80048A44(
        message,
        ((u8 *)a1)[((D_80083228 + ((S_80098CF8_4 *)s4)->unk_2A + 0x100) >> 9) & 7],
        0,
        1);
    func_800A56E0(0x511);
    ((S_80098CF8_4 *)s4)->unk_1C |= 0x100000;
    func_80098B38(s2);
    }
    }
    return s0;

return_zero:
    return 0;
}

/* MECHANISM: The true-space CFG places the shared message tail above its backward caller.
   Scoped guarded pins reproduce the s3/s6/s5/s2/s4 and a0/a1/a2 live ranges.
   A held 0x80080000 page base plus named fences preserves the retail tail order. */

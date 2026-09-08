#include "common.h"

typedef struct S_818FEF80_0_pre {
    u16 unk_00;
} S_818FEF80_0_pre;   /* the 0x2 bytes before arg0 in func_818FEF80, addressed as arg0[-1] */

typedef struct S_818FEF80_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    union { s16 s; volatile s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x24];
    void * unk_30;
} S_818FEF80_0;   /* arg0 in func_818FEF80 */

typedef struct S_818FEF80_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818FEF80_1_pre;   /* the 0x14 bytes before object in func_818FEF80, addressed as object[-1] */

typedef struct S_818FEF80_1 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FEF80_1;   /* object in func_818FEF80 */

typedef struct S_818FEF80_2 {
    u8 pad_00[0x8];
    union { volatile s32 s; s32 u; } unk_08;   /* accessed as both */
} S_818FEF80_2;   /* arg1 in func_818FEF80 */

typedef struct S_818FEF80_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_818FEF80_3;   /* arg2 in func_818FEF80 */

typedef struct S_818FEF80_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818FEF80_4;   /* linked in func_818FEF80 */



extern void func_80024800() __attribute__((noreturn));
extern void func_80024954() __attribute__((noreturn));
extern void func_80024994() __attribute__((noreturn));
extern s16 D_80025E80;
extern s32 D_800814A0;

/* Advance a timed visual effect, updating position, shading, and linked display flags. */
void func_818FEF80(void *state, void *position, void *visual) {
    void *object;
    register void *linked_visual ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 ticks_left;

    object = ((S_818FEF80_0 *)state)->unk_30;
    D_80025E80 = 1;
    if ((u32)(((S_818FEF80_1 *)object)->unk_13 - 0x33) < 4U) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_80024994();
        return;
    }

    ((S_818FEF80_0 *)state)->unk_02.s--;
    if (((S_818FEF80_0 *)state)->unk_0A.s == 0) {
        ((S_818FEF80_0 *)state)->unk_0A.u = 1;
        (void)((S_818FEF80_2 *)position)->unk_08.s;
        object = (void *)0xfffe0000;
        ASM_TAILSLOT_PIN(object);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024800();
        return;
    }

    ((S_818FEF80_0 *)state)->unk_0A.s = 0;
    ((S_818FEF80_2 *)position)->unk_08.u += 0x20000;
    object = ((S_818FEF80_0 *)state)->unk_30;
    linked_visual = ((S_818FEF80_1_pre *)object)[-1].unk_00;
    ((S_818FEF80_3 *)visual)->unk_14 &= 0xFF7F;
    ((S_818FEF80_4 *)linked_visual)->unk_14 |= 0x80;

    ticks_left = ((S_818FEF80_0 *)state)->unk_02.u;
    if (ticks_left < 0x3C) {
        s32 shade_delta;

        ((S_818FEF80_3 *)visual)->unk_0E = (((0x3C - ticks_left) << 6) / 60) + 0x40;
        ((S_818FEF80_3 *)visual)->unk_0D = (((0x3C - ((S_818FEF80_0 *)state)->unk_02.u) << 6) / 60) + 0x40;
        shade_delta = ((0x3C - ((S_818FEF80_0 *)state)->unk_02.u) << 6) / 60;
        ASM_TAILSLOT_PIN(shade_delta);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_80024954();
        return;
    }

    __asm__ __volatile__("" ::: "memory");
    ((S_818FEF80_3 *)visual)->unk_0E = (((ticks_left - 0x3C) << 6) / 60) + 0x40;
    ((S_818FEF80_3 *)visual)->unk_0D = (((((S_818FEF80_0 *)state)->unk_02.u - 0x3C) << 6) / 60) + 0x40;
    ((S_818FEF80_3 *)visual)->unk_0C = (((((S_818FEF80_0 *)state)->unk_02.u - 0x3C) << 6) / 60) + 0x40;

    if (((S_818FEF80_0 *)state)->unk_02.u <= 0) {
        u16 linked_flags;

        ((S_818FEF80_0_pre *)state)[-1].unk_00 |= 0x8000;
        linked_flags = ((S_818FEF80_4 *)linked_visual)->unk_14;
        D_800814A0 |= 0x8000;
        ((S_818FEF80_4 *)linked_visual)->unk_14 = linked_flags & 0xFF7F;
    }
}

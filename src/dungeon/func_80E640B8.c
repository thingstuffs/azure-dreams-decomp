#include "common.h"

typedef struct S_801738B8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
} S_801738B8_0;   /* object in func_801738B8 */

typedef struct S_801738B8_1 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_801738B8_1;   /* room in func_801738B8 */

typedef struct S_801738B8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801738B8_2;   /* actor in func_801738B8 */

typedef struct S_801738B8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801738B8_3;   /* motion in func_801738B8 */



extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801716F4[];
extern u8 D_80175554[];
extern u8 D_80175564[];
extern u8 D_8017558C[];

void func_801738B8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *object ASM_REG("$16") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *motion ASM_REG("$17") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$18") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *room ASM_REG("$19") = arg3;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 timer;
    u16 old_timer;
    s32 value;
    s32 *state;

    switch (((S_801738B8_0 *)object)->unk_9B) {
    case 0:
        func_800AD4D0(room);
        ((S_801738B8_0 *)object)->unk_96.s = 4;
        ((S_801738B8_0 *)object)->unk_9B++;
        if (((S_801738B8_1 *)room)->unk_28 == 0) {
            goto start_action;
        }
        if (!(((S_801738B8_2 *)actor)->unk_14 & 0x8000)) {
            return;
        }
        ((S_801738B8_0 *)object)->unk_96.s = 0;
        ((S_801738B8_0 *)object)->unk_9B = 3;
        return;

    case 1:
        timer = ((S_801738B8_0 *)object)->unk_96.u - 1;
        ((S_801738B8_0 *)object)->unk_96.s = timer;
        if (timer > 0) {
            ((S_801738B8_3 *)motion)->unk_0C =
                *(s16 *)((u8 *)&D_8006CCD8 +
                    ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 19;
            ((S_801738B8_3 *)motion)->unk_10 =
                *(s16 *)((u8 *)&D_8006CCE8 +
                    ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        ((S_801738B8_3 *)motion)->unk_0C =
            *(s16 *)((u8 *)&D_8006CCD8 +
                ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 18;
        ((S_801738B8_3 *)motion)->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 +
                ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 18;
        ((S_801738B8_0 *)object)->unk_96.s = 6;
        ((S_801738B8_0 *)object)->unk_9B++;
        return;

    case 2:
        if (((S_801738B8_1 *)room)->unk_28 == 0) {
start_action:
            ((S_801738B8_3 *)motion)->unk_14 = 0;
            ((S_801738B8_3 *)motion)->unk_10 = 0;
            ((S_801738B8_3 *)motion)->unk_0C = 0;
            func_800AAA54(object, motion, actor, D_8017558C);
            return;
        }

        timer = ((S_801738B8_0 *)object)->unk_96.s;
        if (timer != 0) {
            {
                s32 coord = ((S_801738B8_2 *)actor)->unk_24 << 6;
                s32 current = ((S_801738B8_3 *)motion)->unk_02 - 0x20;

                ((S_801738B8_3 *)motion)->unk_0C =
                    ((coord - current) << 16) / timer;
            }
            {
                s32 coord = ((S_801738B8_2 *)actor)->unk_25 << 6;
                s32 current = ((S_801738B8_3 *)motion)->unk_06 - 0x20;

                ((S_801738B8_3 *)motion)->unk_10 =
                    ((coord - current) << 16) /
                    ((S_801738B8_0 *)object)->unk_96.s;
            }
        }
        old_timer = ((S_801738B8_0 *)object)->unk_96.u;
        ((S_801738B8_0 *)object)->unk_96.s = old_timer - 1;
        if ((s32)(old_timer << 16) > 0) {
            return;
        }
        ((S_801738B8_3 *)motion)->unk_14 = 0;
        ((S_801738B8_3 *)motion)->unk_10 = 0;
        ((S_801738B8_3 *)motion)->unk_0C = 0;
        ((S_801738B8_0 *)object)->unk_9B++;
        return;

    case 3:
        ((S_801738B8_3 *)motion)->unk_14 = 0;
        ((S_801738B8_3 *)motion)->unk_10 = 0;
        ((S_801738B8_3 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((S_801738B8_2 *)actor)->unk_24, ((S_801738B8_2 *)actor)->unk_25);
        if (((S_801738B8_2 *)actor)->unk_2C == D_80175564) {
            (*(void * *)((u8 *)actor + 0x2C)) = D_80175554;
            func_80047784(actor,
                D_80175554[((D_80083228 + ((S_801738B8_1 *)room)->unk_2A + 0x100)
                    >> 9) & 7], 0);
        }
        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)room - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        ((S_801738B8_0 *)object)->unk_8C = D_801716F4;
        ((S_801738B8_0 *)object)->unk_9A = 0xE;
        ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(room);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return;

    default:
        return;
    }
}

/* MECHANISM: Ordered $s0-$s3 argument locals reproduce the retail save/move prologue.
   Duplicated state increments keep the predecessor-local lbu alive, while scoped
   coord/current temporaries expose the second lh to fill the mflo hazard slot.
   The paired +1/-1 shapes cancel the displacement cascade at 2.8.1-G0. */

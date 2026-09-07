#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register void *object ASM_REG("$16") = arg0;
    register void *motion ASM_REG("$17") = arg1;
    register void *actor ASM_REG("$18") = arg2;
    register void *room ASM_REG("$19") = arg3;
    s16 timer;
    u16 old_timer;
    s32 value;
    s32 *state;

    switch (FIELD(object, u8, 0x9B)) {
    case 0:
        func_800AD4D0(room);
        FIELD(object, s16, 0x96) = 4;
        FIELD(object, u8, 0x9B)++;
        if (FIELD(room, u8, 0x28) == 0) {
            goto start_action;
        }
        if (!(FIELD(actor, u16, 0x14) & 0x8000)) {
            return;
        }
        FIELD(object, s16, 0x96) = 0;
        FIELD(object, u8, 0x9B) = 3;
        return;

    case 1:
        timer = FIELD(object, u16, 0x96) - 1;
        FIELD(object, s16, 0x96) = timer;
        if (timer > 0) {
            FIELD(motion, s32, 0x0C) =
                *(s16 *)((u8 *)&D_8006CCD8 +
                    ((FIELD(room, u16, 0x6A) >> 8) & 0xE)) << 19;
            FIELD(motion, s32, 0x10) =
                *(s16 *)((u8 *)&D_8006CCE8 +
                    ((FIELD(room, u16, 0x6A) >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        FIELD(motion, s32, 0x0C) =
            *(s16 *)((u8 *)&D_8006CCD8 +
                ((FIELD(room, u16, 0x6A) >> 8) & 0xE)) << 18;
        FIELD(motion, s32, 0x10) =
            *(s16 *)((u8 *)&D_8006CCE8 +
                ((FIELD(room, u16, 0x6A) >> 8) & 0xE)) << 18;
        FIELD(object, s16, 0x96) = 6;
        FIELD(object, u8, 0x9B)++;
        return;

    case 2:
        if (FIELD(room, u8, 0x28) == 0) {
start_action:
            FIELD(motion, s32, 0x14) = 0;
            FIELD(motion, s32, 0x10) = 0;
            FIELD(motion, s32, 0x0C) = 0;
            func_800AAA54(object, motion, actor, D_8017558C);
            return;
        }

        timer = FIELD(object, s16, 0x96);
        if (timer != 0) {
            {
                s32 coord = FIELD(actor, u8, 0x24) << 6;
                s32 current = FIELD(motion, s16, 2) - 0x20;

                FIELD(motion, s32, 0x0C) =
                    ((coord - current) << 16) / timer;
            }
            {
                s32 coord = FIELD(actor, u8, 0x25) << 6;
                s32 current = FIELD(motion, s16, 6) - 0x20;

                FIELD(motion, s32, 0x10) =
                    ((coord - current) << 16) /
                    FIELD(object, s16, 0x96);
            }
        }
        old_timer = FIELD(object, u16, 0x96);
        FIELD(object, s16, 0x96) = old_timer - 1;
        if ((s32)(old_timer << 16) > 0) {
            return;
        }
        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        FIELD(object, u8, 0x9B)++;
        return;

    case 3:
        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        func_800A2B04(motion, FIELD(actor, u8, 0x24), FIELD(actor, u8, 0x25));
        if (FIELD(actor, void *, 0x2C) == D_80175564) {
            FIELD(actor, void *, 0x2C) = D_80175554;
            func_80047784(actor,
                D_80175554[((D_80083228 + FIELD(room, s16, 0x2A) + 0x100)
                    >> 9) & 7], 0);
        }
        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)room - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        FIELD(object, void *, 0x8C) = D_801716F4;
        FIELD(object, u8, 0x9A) = 0xE;
        ASM_KEEP(object);
        ASM_KEEP(motion);
        ASM_KEEP(actor);
        ASM_KEEP(room);
        return;

    default:
        return;
    }
}

/* MECHANISM: Ordered $s0-$s3 argument locals reproduce the retail save/move prologue.
   Duplicated state increments keep the predecessor-local lbu alive, while scoped
   coord/current temporaries expose the second lh to fill the mflo hazard slot.
   The paired +1/-1 shapes cancel the displacement cascade at 2.8.1-G0. */

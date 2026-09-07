#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

/* Input-only liveness extension (no "+r" rewrite): keeps `var` live to this
 * point WITHOUT redefining it. ASM_KEEP's "+r" adds a second def, which flips
 * gcc 2.8.1 sched2's prologue entry-group ordering (the s3 save/copy pair
 * hoists to the front) — proven on this function (v10 vs v11). Candidate for
 * promotion into common.h as ASM_USE. */
#ifdef NON_MATCHING
#else
#endif

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801714B8;
extern u8 D_801760D4;

void func_80173730(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *p0 ASM_REG("$16");
    register void *p1 ASM_REG("$17");
    register void *p2 ASM_REG("$18");
    register void *p3 ASM_REG("$19");
    u8 state;
    s16 timer;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3


    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        func_800AD4D0(arg3);
        FIELD(arg0, u16, 0x96) = 4;
        FIELD(arg0, u8, 0x9B)++;
        if (FIELD(arg3, u8, 0x28) == 0) {
            goto reset_motion;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 3;
        return;

    case 1:
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer > 0) {
            FIELD(arg1, s32, 0x0C) =
                *(s16 *)(&D_8006CCD8 +
                    ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
            FIELD(arg1, s32, 0x10) =
                *(s16 *)(&D_8006CCE8 +
                    ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        FIELD(arg1, s32, 0x0C) =
            *(s16 *)(&D_8006CCD8 +
                ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)(&D_8006CCE8 +
                ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
        FIELD(arg0, u16, 0x96) = 12;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        if (FIELD(arg3, u8, 0x28) != 0) {
            goto update_motion;
        }
reset_motion:
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800AAA54(arg0, arg1, arg2, &D_801760D4);
        return;

update_motion:
        {
            s16 motion_timer = FIELD(arg0, s16, 0x96);

            if (motion_timer != 0) {
                {
                    s32 coord = FIELD(arg2, u8, 0x24) << 6;
                    s32 current = FIELD(arg1, s16, 2) - 0x20;

                    FIELD(arg1, s32, 0x0C) =
                        ((coord - current) << 16) / motion_timer;
                }
                {
                    s32 coord = FIELD(arg2, u8, 0x25) << 6;
                    s32 current = FIELD(arg1, s16, 6) - 0x20;

                    FIELD(arg1, s32, 0x10) = ((coord - current) << 16)
                        / FIELD(arg0, s16, 0x96);
                }
            }
        }
        {
            u16 countdown = FIELD(arg0, u16, 0x96);

            FIELD(arg0, u16, 0x96) = countdown - 1;
            if ((countdown << 16) > 0) {
                return;
            }
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 3:
        {
            s32 *global;
            s32 value;

            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                FIELD(arg2, u8, 0x25));
            global = &D_80083460;
            value = *(s32 *)((u8 *)global + 0x10);
            if (value == (s32)((u8 *)arg3 - 0x20)) {
                *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
            }
            FIELD(arg0, void *, 0x8C) = &D_801714B8;
            ASM_USE(p3);
        }
        return;
    }
}

#include "common.h"


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


typedef struct S_80173730_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173730_0;   /* arg0 in func_80173730 */

typedef struct S_80173730_1 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x41];
    u16 unk_6A;
} S_80173730_1;   /* arg3 in func_80173730 */

typedef struct S_80173730_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173730_2;   /* arg2 in func_80173730 */

typedef struct S_80173730_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173730_3;   /* arg1 in func_80173730 */

void func_80173730(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *p0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *p1 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *p2 ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *p3;
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


    state = ((S_80173730_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(arg3);
        ((S_80173730_0 *)arg0)->unk_96.u = 4;
        ((S_80173730_0 *)arg0)->unk_9B++;
        if (((S_80173730_1 *)arg3)->unk_28 == 0) {
            goto reset_motion;
        }
        if (!(((S_80173730_2 *)arg2)->unk_14 & 0x8000)) {
            return;
        }
        ((S_80173730_0 *)arg0)->unk_96.u = 0;
        ((S_80173730_0 *)arg0)->unk_9B = 3;
        return;

    case 1:
        timer = ((S_80173730_0 *)arg0)->unk_96.u - 1;
        ((S_80173730_0 *)arg0)->unk_96.u = timer;
        if (timer > 0) {
            ((S_80173730_3 *)arg1)->unk_0C =
                *(s16 *)(&D_8006CCD8 +
                    ((((S_80173730_1 *)arg3)->unk_6A >> 8) & 0xE)) << 19;
            ((S_80173730_3 *)arg1)->unk_10 =
                *(s16 *)(&D_8006CCE8 +
                    ((((S_80173730_1 *)arg3)->unk_6A >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        ((S_80173730_3 *)arg1)->unk_0C =
            *(s16 *)(&D_8006CCD8 +
                ((((S_80173730_1 *)arg3)->unk_6A >> 8) & 0xE)) << 18;
        ((S_80173730_3 *)arg1)->unk_10 =
            *(s16 *)(&D_8006CCE8 +
                ((((S_80173730_1 *)arg3)->unk_6A >> 8) & 0xE)) << 18;
        ((S_80173730_0 *)arg0)->unk_96.u = 12;
        ((S_80173730_0 *)arg0)->unk_9B++;
        return;

    case 2:
        if (((S_80173730_1 *)arg3)->unk_28 != 0) {
            goto update_motion;
        }
reset_motion:
        ((S_80173730_3 *)arg1)->unk_14 = 0;
        ((S_80173730_3 *)arg1)->unk_10 = 0;
        ((S_80173730_3 *)arg1)->unk_0C = 0;
        func_800AAA54(arg0, arg1, arg2, &D_801760D4);
        return;

update_motion:
        {
            s16 motion_timer = ((S_80173730_0 *)arg0)->unk_96.s;

            if (motion_timer != 0) {
                {
                    s32 coord = ((S_80173730_2 *)arg2)->unk_24 << 6;
                    s32 current = ((S_80173730_3 *)arg1)->unk_02 - 0x20;

                    ((S_80173730_3 *)arg1)->unk_0C =
                        ((coord - current) << 16) / motion_timer;
                }
                {
                    s32 coord = ((S_80173730_2 *)arg2)->unk_25 << 6;
                    s32 current = ((S_80173730_3 *)arg1)->unk_06 - 0x20;

                    ((S_80173730_3 *)arg1)->unk_10 = ((coord - current) << 16)
                        / ((S_80173730_0 *)arg0)->unk_96.s;
                }
            }
        }
        {
            u16 countdown = ((S_80173730_0 *)arg0)->unk_96.u;

            ((S_80173730_0 *)arg0)->unk_96.u = countdown - 1;
            if ((countdown << 16) > 0) {
                return;
            }
        }
        ((S_80173730_3 *)arg1)->unk_14 = 0;
        ((S_80173730_3 *)arg1)->unk_10 = 0;
        ((S_80173730_3 *)arg1)->unk_0C = 0;
        ((S_80173730_0 *)arg0)->unk_9B++;
        return;

    case 3:
        {
            s32 *global;
            s32 value;

            ((S_80173730_3 *)arg1)->unk_14 = 0;
            ((S_80173730_3 *)arg1)->unk_10 = 0;
            ((S_80173730_3 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1, ((S_80173730_2 *)arg2)->unk_24,
                ((S_80173730_2 *)arg2)->unk_25);
            global = &D_80083460;
            value = *(s32 *)((u8 *)global + 0x10);
            if (value == (s32)((u8 *)arg3 - 0x20)) {
                *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
            }
            ((S_80173730_0 *)arg0)->unk_8C = &D_801714B8;
            ASM_USE(p3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        }
        return;
    }
}

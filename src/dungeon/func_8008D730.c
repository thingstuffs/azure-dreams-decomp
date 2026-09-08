#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_800419EC();
extern s32 func_80042900();
extern s32 func_80042B68();
extern s32 func_80048A44();
extern s32 func_80092F30();
extern s32 func_8009307C();
extern s32 func_800997FC();
extern s32 func_800A2B04();

extern u16 D_80013714;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80083460_count __asm__("D_80083460");
extern s32 D_8008ACDC;
extern u8 D_800DCFF8[];
extern u8 D_800E0597;
extern u8 D_800E05C3;


typedef struct S_80092E90_0 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_80092E90_0;   /* global in func_80092E90 */

typedef struct S_80092E90_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80092E90_1;   /* arg2 in func_80092E90 */


typedef struct S_80092E90_3 {
    u8 pad_00[0x4];
    union { s16 n; volatile u16 v; u16 n2; } unk_04;   /* accessed as both */
} S_80092E90_3;   /* countBase in func_80092E90 */

typedef struct S_80092E90_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80092E90_4;   /* arg0 in func_80092E90 */

typedef struct S_80092E90_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    void * unk_5C;
} S_80092E90_5;   /* savedArg3 in func_80092E90 */

typedef struct S_80092E90_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80092E90_6;   /* actorBase in func_80092E90 */

typedef struct S_80092E90_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80092E90_7_pre;   /* the 0x14 bytes before node in func_80092E90, addressed as node[-1] */

typedef struct S_80092E90_7 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80092E90_7;   /* node in func_80092E90 */

typedef struct S_80092E90_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80092E90_8;   /* endBase in func_80092E90 */

typedef struct S_80092E90_9 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80092E90_9;   /* ((S_80092E90_7_pre *)node)[-1].unk_00 in func_80092E90 */

void func_80092E90(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *savedArg3 ASM_REG("$21") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *actorBase;
    s32 found;
    s32 adjusted;
    s32 pixel;
    register s32 initArg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register s32 loopResult ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 count;
    s16 divisor;
    s16 *global;
    u16 rawCount;
    u8 state;
    void *countBase;
    void *endBase;
    void *node;

    global = (s16 *)&D_80083460;
    divisor = ((S_80092E90_0 *)global)->unk_04;
    if (divisor != 0) {
        pixel = ((S_80092E90_1 *)arg2)->unk_24 << 6;
        adjusted = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 =
            ((pixel - adjusted) << 16) / divisor;
        adjusted = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
        adjusted -= 0x20;
        pixel = ((S_80092E90_1 *)arg2)->unk_25 << 6;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            ((pixel - adjusted) << 16) / ((S_80092E90_0 *)global)->unk_04;
        func_80092F30(divisor, global);
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    countBase = &D_80083460_count;
    count = ((S_80092E90_3 *)countBase)->unk_04.n;
    rawCount = ((S_80092E90_3 *)countBase)->unk_04.v;
    if (count != 0) {
        ((S_80092E90_3 *)countBase)->unk_04.n2 = rawCount - 1;
    }

    state = ((S_80092E90_4 *)arg0)->unk_9B;
    if (state == 0) {
        goto state0;
    }
    if (state == 1) {
        goto state1;
    }
    return;

state0:
        initArg = 0x10;
        if (!(((S_80092E90_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
        func_800419EC(initArg, 8);
        (*(void * *)((u8 *)arg2 + (0x2C))) = D_800DCFF8;
        func_80048A44(
            arg2,
            D_800DCFF8[((D_80083228 + ((S_80092E90_5 *)savedArg3)->unk_2A + 0x100) >> 9) & 7],
            0,
            1);
        ((S_80092E90_4 *)arg0)->unk_9B++;
        return;

state1:
        if (!(((S_80092E90_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        found = 0;
        if (!(D_80013714 & 8)) {
            node = (u8 *)((S_80092E90_5 *)savedArg3)->unk_5C + 0x20;
            actorBase = D_80082E80;
            do {
                if ((((S_80092E90_6 *)actorBase)->unk_26 ==
                     ((S_80092E90_9 *)(((S_80092E90_7_pre *)node)[-1].unk_00))->unk_26) &&
                    ((func_80042900(node, 1) << 16) != 0)) {
                    func_80042B68(node, 1);
                    found = 1;
                }
                node = (u8 *)((S_80092E90_7 *)node)->unk_5C + 0x20;
            } while (node != savedArg3);

            loopResult = found;
            if (loopResult != 0) {
#ifndef NON_MATCHING
                register u32 page ASM_REG("$2") = 0x800E0000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                func_8009307C((void *)(page + 0x597));
#else
                func_8009307C(&D_800E0597);
#endif
                return;
            }
#ifndef NON_MATCHING
            ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            {
                register u32 page ASM_REG("$2") = 0x800E0000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register void *message ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                message = (void *)(page + 0x5C3);
                ASM_KEEP(message);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                func_800997FC(message);
            }
#else
            func_800997FC(&D_800E05C3);
#endif
        }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80092E90_1 *)arg2)->unk_24, ((S_80092E90_1 *)arg2)->unk_25);
    ((S_80092E90_4 *)arg0)->unk_8C = &D_8008ACDC;
    endBase = &D_80083460;
    ((S_80092E90_8 *)endBase)->unk_0A--;
}

/* MECHANISM: A reload barrier plus a same-address alias/fence rematerializes the count base after the zero stores.
   Explicit state labels remove the late default block; held a0 arguments fill the case-0 slot and preserve the func_800997FC nop. */

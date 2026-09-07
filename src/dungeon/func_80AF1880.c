#include "common.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80173198() __attribute__((noreturn));
extern void func_80173268(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_801717F4[];
extern u8 D_801759C0[];


typedef struct S_80173080_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173080_0;   /* arg0 in func_80173080 */

typedef struct S_80173080_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80173080_1;   /* arg2 in func_80173080 */

typedef struct S_80173080_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80173080_2;   /* arg3 in func_80173080 */

typedef struct S_80173080_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173080_3;   /* arg1 in func_80173080 */

void func_80173080(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 under_two;
    u16 timer;
    s32 state;

    state = ((S_80173080_0 *)arg0)->unk_9B;
    if (state != 1) {
        under_two = (s32)state < 2;
        if (under_two) {
            ASM_KEEP(under_two);   /* MATCH pin: retail delay-slot fill depends on it */
            if (state == 0) {
                goto state_0;
            }
            func_80173268();
            return;
        }
        if (state == 2) {
            goto state_2;
        }
        if (state == 3) {
            goto state_3;
        }
        func_80173268();
        return;
    }

    goto state_1;

state_0:
    if (((S_80173080_1 *)arg2)->unk_14 & 0x8000) {
        ((S_80173080_0 *)arg0)->unk_9B = 3;
        ((S_80173080_1 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80173080_2 *)arg3)->unk_2A, 1);
        func_80173268();
        return;
    }
    ((S_80173080_3 *)arg1)->unk_14 = 0;
    ((S_80173080_3 *)arg1)->unk_10 = 0;
    ((S_80173080_3 *)arg1)->unk_0C = 0;
    func_80173198(arg3);
    return;

state_1:
    timer = ((S_80173080_0 *)arg0)->unk_96.u + 1;
    ((S_80173080_0 *)arg0)->unk_96.u = timer;
    if (((s16)timer == 4) || (((S_80173080_1 *)arg2)->unk_14 & 0x8000)) {
        u8 *table = D_801759C0;

        (*(u8 * *)((u8 *)arg2 + (0x2C))) = table;
        func_80047784(arg2,
                     table[((D_80083228 + ((S_80173080_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                     0);
        ((S_80173080_0 *)arg0)->unk_96.u = 0;
        ((S_80173080_0 *)arg0)->unk_9B++;
        func_80173268();
        return;
    }
    goto done;

state_2:
    timer = ((S_80173080_0 *)arg0)->unk_96.u + 1;
    ((S_80173080_0 *)arg0)->unk_96.u = timer;
    if (((s16)timer == 7) || (((S_80173080_1 *)arg2)->unk_14 & 0x8000)) {
        func_8009C12C(arg3, arg2, ((S_80173080_2 *)arg3)->unk_2A, 1);
        ((S_80173080_0 *)arg0)->unk_96.u = 0;
        ((S_80173080_0 *)arg0)->unk_9B++;
    }
    if (((S_80173080_0 *)arg0)->unk_96.s == 5) {
        func_800A56E0(0x808);
        func_80173268();
        return;
    }
    goto done;

state_3:
    if (((S_80173080_1 *)arg2)->unk_14 & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_80173080_0 *)arg0)->unk_8C = D_801717F4;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((S_80173080_2 *)arg3)->unk_46 &= 0x7FFF;
    }

done:
    return;
}

#include "common.h"

typedef struct S_800CD474_0_pre {
    u16 unk_00;
} S_800CD474_0_pre;   /* the 0x2 bytes before arg0 in func_800CD474, addressed as arg0[-1] */

typedef struct S_800CD474_0 {
    s32 unk_00;
    s16 unk_04;
    u16 unk_06;
    s16 unk_08;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
} S_800CD474_0;   /* arg0 in func_800CD474 */

typedef struct S_800CD474_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CD474_1;   /* arg1 in func_800CD474 */

typedef struct S_800CD474_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_800CD474_2;   /* arg2 in func_800CD474 */

typedef struct S_800CD474_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD474_3;   /* global_base in func_800CD474 */



extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s32 func_800CD66C();
extern s32 func_800CD6AC();
extern s32 D_800814A0;
extern s32 D_80083460;

void func_800CD474(void *arg0, S_800CD474_1 *arg1, S_800CD474_2 *arg2) {
    s16 state;
    s32 color;
    u16 timer;
    u16 timer2;
    u16 timer3;
    u16 value;
    s32 *global_base;

    state = ((S_800CD474_0 *)arg0)->unk_04;
    if (state == 0) {
        arg1->unk_14 += 0x20000;
        timer = ((S_800CD474_0 *)arg0)->unk_06 - 1;
        ((S_800CD474_0 *)arg0)->unk_06 = timer;
        if ((timer << 16) == 0) {
            func_800A56E0(0x701);
        }
        if ((arg1->unk_08.at02.v + 0x10) >= ((S_800CD474_0 *)arg0)->unk_0A.s) {
            func_800419EC(8, 8);
            value = ((S_800CD474_0 *)arg0)->unk_0A.u;
            arg1->unk_14 = 0;
            arg1->unk_08.at02.v = value;
            ((S_800CD474_0 *)arg0)->unk_06 = 8;
            ((S_800CD474_0 *)arg0)->unk_04 = (u16)((S_800CD474_0 *)arg0)->unk_04 + 1;
            func_800A56E0(0x612);
        }
        color = 0x404040;
        if (((S_800CD474_0 *)arg0)->unk_0C & 1) {
            color = 0x808080;
        }
        arg2->unk_0C.at00.v = color;
        func_800CD66C();
        return;
    }
    if (state == 1) {
        color = 0x404040;
        if (((S_800CD474_0 *)arg0)->unk_0C & 1) {
            color = 0x808080;
        }
        arg2->unk_0C.at00.v = color;
        timer2 = ((S_800CD474_0 *)arg0)->unk_06 - 1;
        ((S_800CD474_0 *)arg0)->unk_06 = timer2;
        if ((timer2 << 16) <= 0) {
            ((S_800CD474_0 *)arg0)->unk_06 = 0x10;
            arg2->unk_0C.at00.v = 0x808080;
            ((S_800CD474_0 *)arg0)->unk_04 = (u16)((S_800CD474_0 *)arg0)->unk_04 + 1;
            if (((S_800CD474_0 *)arg0)->unk_08 == 0) {
                func_800CD6AC(((S_800CD474_0 *)arg0)->unk_00, 0x10);
                func_800CD66C();
                return;
            }
        }
        arg1->unk_08.at00.v += arg1->unk_14;
        ((S_800CD474_0 *)arg0)->unk_0C += 1;
        return;
    }
    arg2->unk_0C.at00u.v = arg2->unk_0C.at00u.v -
                           (arg2->unk_0C.at00u.v / (s16)((S_800CD474_0 *)arg0)->unk_06);
    arg2->unk_0C.at01.v = arg2->unk_0C.at01.v -
                           (arg2->unk_0C.at01.v / (s16)((S_800CD474_0 *)arg0)->unk_06);
    arg2->unk_0C.at02.v = arg2->unk_0C.at02.v -
                           (arg2->unk_0C.at02.v / (s16)((S_800CD474_0 *)arg0)->unk_06);
    timer3 = ((S_800CD474_0 *)arg0)->unk_06 - 1;
    ((S_800CD474_0 *)arg0)->unk_06 = timer3;
    if ((timer3 << 16) <= 0) {
        ((S_800CD474_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0 |= 0x8000;
        global_base = &D_80083460;
        ((S_800CD474_3 *)global_base)->unk_0A -= 1;
    }
    arg1->unk_08.at00.v += arg1->unk_14;
    ((S_800CD474_0 *)arg0)->unk_0C += 1;
}

#include "common.h"


extern void func_80024C90(void) __attribute__((noreturn));
extern void func_80024D74(void) __attribute__((noreturn));
extern void func_80024FD8();
extern void func_800254C4();
extern void func_800478B8();
extern s32 func_800644B8();
extern s16 D_800257CC;
extern s16 D_800257CE;
extern s32 D_800814A0;


typedef struct S_80024B98_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024B98_0;   /* arg0 in func_80024B98 */

typedef struct S_80024B98_1 {
    u8 pad_00[0xC];
    union { s32 s32; u8 u8; } unk_0C;   /* accessed as both */
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80024B98_1;   /* arg2 in func_80024B98 */

typedef struct S_80024B98_2 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80024B98_2;   /* arg1 in func_80024B98 */

void func_80024B98(void *arg0, void *arg1, void *arg2) {
    s16 state;
    s32 damage;
    u16 v;

    D_800257CE++;
    state = ((S_80024B98_0 *)arg0)->unk_0A.s;
    if (state != 2) {
        if (state == 0) {
            v = ((S_80024B98_0 *)arg0)->unk_1E - 1;
            ((S_80024B98_0 *)arg0)->unk_1E = v;
            if ((s16)v <= 0) {
                ((S_80024B98_0 *)arg0)->unk_0A.u++;
                goto advance;
            }
        } else {
advance:
            v = ((S_80024B98_0 *)arg0)->unk_1C + 1;
            ((S_80024B98_0 *)arg0)->unk_1C = v;
            if ((s16)v >= 0x41) {
                ((S_80024B98_0 *)arg0)->unk_0A.u = 2;
                func_80024C90();
                return;
            }
            goto common;
        }
    } else {
        ((S_80024B98_1 *)arg2)->unk_0C.s32 += 0xFFFBFBFC;
        if (((S_80024B98_1 *)arg2)->unk_0C.u8 < 4) {
            D_800257CC--;
            (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_80024D74();
            return;
        }
common:
        ((S_80024B98_2 *)arg1)->unk_08.at00.v += ((S_80024B98_2 *)arg1)->unk_14;
        ((S_80024B98_2 *)arg1)->unk_14 += 0x10000;
        if (((S_80024B98_2 *)arg1)->unk_08.at02.v > ((S_80024B98_0 *)arg0)->unk_14)
            ((S_80024B98_2 *)arg1)->unk_08.at02.v = ((S_80024B98_0 *)arg0)->unk_14;
        damage = func_800644B8((s16)((S_80024B98_0 *)arg0)->unk_1C << 6);
        ((S_80024B98_1 *)arg2)->unk_0C.s32 += 0x20202;
        ((S_80024B98_1 *)arg2)->unk_1E -= damage >> 5;
        if (((S_80024B98_1 *)arg2)->unk_0C.u8 >= 0x41)
            ((S_80024B98_1 *)arg2)->unk_0C.s32 = 0x404040;
        func_800478B8(arg2);
        if (!(((S_80024B98_0 *)arg0)->unk_1C & 0x1F))
            func_80024FD8(arg1, ((S_80024B98_0 *)arg0)->unk_14, ((S_80024B98_0 *)arg0)->unk_24);
        if (!(((S_80024B98_0 *)arg0)->unk_1C & 3))
            func_800254C4(arg1, (((S_80024B98_0 *)arg0)->unk_24 << 24) >> 16, 0x10, 0);
    }
}

/* MECHANISM: The 0x20 frame follows from holding the three argument bases in s0/s2/s1.
   Restored state=2 and D_800814A0 RMW stores close both tail paths and the four-word cascade.
   Split call-result liveness, reversed compare operands, and a signed shift pair fix scheduling/lh. */

#include "common.h"

typedef struct S_8182D544_0_pre {
    u16 unk_00;
} S_8182D544_0_pre;   /* the 0x2 bytes before arg0 in func_8182D544, addressed as arg0[-1] */

typedef struct S_8182D544_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_8182D544_0;   /* arg0 in func_8182D544 */

typedef struct S_8182D544_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8182D544_1;   /* object in func_8182D544 */

typedef struct S_8182D544_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182D544_2;   /* arg1 in func_8182D544 */

typedef struct S_8182D544_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
} S_8182D544_3;   /* arg2 in func_8182D544 */



extern void func_80024E80(void) __attribute__((noreturn));
extern void func_8004491C();
extern void func_800478B8(void *);
extern s32 rand(void);
extern u8 D_80045340[0x10];
extern s32 D_800814A0[3];

void func_8182D544(void *arg0, S_8182D544_2 *arg1, S_8182D544_3 *arg2)
{
    s16 state;
    s32 delta_y;
    s32 delta_z;
    s32 amount;
    u16 timer;
    u8 value;
    S_8182D544_1 *object;

    object = ((S_8182D544_0 *)arg0)->unk_00;
    object->unk_0C |= 0x8000;

    delta_y = arg1->unk_10;
    delta_z = arg1->unk_14;
    arg1->unk_00 += arg1->unk_0C;
    arg1->unk_04 += delta_y;
    arg1->unk_08 += delta_z;

    state = ((S_8182D544_0 *)arg0)->unk_4C.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    func_80024E80();

state_zero:
    timer = ((S_8182D544_0 *)arg0)->unk_48 - 1;
    ((S_8182D544_0 *)arg0)->unk_48 = timer;
    if ((timer << 16) <= 0) {
        func_8004491C((u8 *)arg0 - 0x20, D_80045340, delta_z);
        ((S_8182D544_0 *)arg0)->unk_4C.u++;
        func_80024E80();
    }
    return;

state_one:
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        arg2->unk_04 = 0;
        arg2->unk_05 = 0;
    }

    amount = (rand() & 0xF) + 9;
    if (amount >= arg2->unk_0C.at00.v) {
        arg2->unk_0C.at00u.v = 0;
        ((S_8182D544_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80024E80();
        return;
    }

    value = arg2->unk_0C.at02.v - amount;
    arg2->unk_0C.at02.v = value;
    arg2->unk_0C.at01.v = value;
    arg2->unk_0C.at00.v = value;
}

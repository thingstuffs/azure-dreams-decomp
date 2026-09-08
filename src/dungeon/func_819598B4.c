#include "common.h"

typedef struct S_819598B4_0_pre {
    u16 unk_00;
} S_819598B4_0_pre;   /* the 0x2 bytes before arg0 in func_819598B4, addressed as arg0[-1] */

typedef struct S_819598B4_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xA];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
    u8 pad_3A[0x2];
    s16 unk_3C;
} S_819598B4_0;   /* arg0 in func_819598B4 */

typedef struct S_819598B4_1 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { u32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xE];
    u16 unk_1E;
} S_819598B4_1;   /* arg2 in func_819598B4 */

typedef struct S_819598B4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 n; volatile u16 v; } unk_0A;   /* accessed as both */
} S_819598B4_2;   /* arg1 in func_819598B4 */

typedef struct S_819598B4_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_819598B4_3;   /* D_800E3D7C[0] in func_819598B4 */



extern void func_8002527C(void) __attribute__((noreturn));
extern void func_800252E8(void) __attribute__((noreturn));
extern s32 func_80025604();
extern s32 func_80026384();

extern u16 D_800281F8[];
extern u8 D_80028220[];
extern s32 D_800814A0[];
extern void *D_800E3D7C[];

void func_819598B4(void *arg0, S_819598B4_2 *arg1, S_819598B4_1 *arg2) {
    s16 temp_a0_3;
    s16 temp_a1;
    s32 temp_x;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    u16 temp_v1_2;
    s32 temp_a0;
    s32 temp_a0_2;
    u8 temp_v0_3;
    u8 temp_v1_3;

    D_800281F8[0]++;
    temp_v1 = ((S_819598B4_0 *)arg0)->unk_2C.s;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 >= 2) {
        goto state_ge_2;
    }
    if (temp_v1 == 0) {
        goto state_0;
    }
    func_800252E8();
    return;

state_ge_2:
    if (temp_v1 == 2) {
        goto state_2;
    }
    func_800252E8();
    return;

state_0:
    temp_v1_2 = arg2->unk_1E;
    temp_a0 = arg2->unk_0C.at00.v;
    arg2->unk_1E = (u16)(temp_v1_2 + ((s32)(0x1000 - temp_v1_2) / ((S_819598B4_0 *)arg0)->unk_30));
    temp_x = 0x80 - temp_a0;
    temp_a1 = ((S_819598B4_0 *)arg0)->unk_3C;
    temp_a0_2 = temp_a0 + ((temp_x - temp_a1) / ((S_819598B4_0 *)arg0)->unk_30);
    arg2->unk_0C.at00.v = temp_a0_2;
    arg2->unk_0C.at01.v = temp_a0_2;
    arg2->unk_0C.at02.v = temp_a0_2;
    arg1->unk_02 = (s16)((u16)arg1->unk_02 + ((s32)(((S_819598B4_0 *)arg0)->unk_14 - arg1->unk_02) / ((S_819598B4_0 *)arg0)->unk_30));
    arg1->unk_06 = (s16)((u16)arg1->unk_06 + ((s32)(((S_819598B4_0 *)arg0)->unk_16 - arg1->unk_06) / ((S_819598B4_0 *)arg0)->unk_30));
    temp_a0_3 = arg1->unk_0A.n;
    arg1->unk_0A.n = (s16)(arg1->unk_0A.v + ((s32)(((S_819598B4_0 *)arg0)->unk_18 - temp_a0_3) / ((S_819598B4_0 *)arg0)->unk_30));
    temp_v0 = (u16)((S_819598B4_0 *)arg0)->unk_30 - 1;
    ((S_819598B4_0 *)arg0)->unk_30 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto common;
    }
    ((S_819598B4_0 *)arg0)->unk_30 = 0x10;
    arg2->unk_1E = 0x1000;
    arg2->unk_0C.at00u.v = 0x00808080;
    if (((S_819598B4_0 *)arg0)->unk_3C != 0) {
        ((S_819598B4_0 *)arg0)->unk_2C.s = 2;
        func_800252E8();
    }
    {
        u32 tailslot;

        tailslot = ((S_819598B4_0 *)arg0)->unk_2C.u + 1;
        ASM_TAILSLOT_PIN(tailslot);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        func_8002527C();
    }

state_1:
    if (((S_819598B4_0 *)arg0)->unk_38 != 0) {
        goto finish_state_1;
    }
    if (func_80026384(((S_819598B4_0 *)arg0)->unk_1C, ((S_819598B4_0 *)arg0)->unk_1E, ((S_819598B4_0 *)arg0)->unk_20, ((S_819598B4_3 *)(D_800E3D7C[0]))->unk_2A) == 0) {
        goto common;
    }
    func_80025604(((S_819598B4_0 *)arg0)->unk_1C, ((S_819598B4_0 *)arg0)->unk_1E, ((S_819598B4_0 *)arg0)->unk_20);
finish_state_1:
    ((S_819598B4_0 *)arg0)->unk_30 = 0x10;
    ((S_819598B4_0 *)arg0)->unk_2C.s++;
    func_800252E8();
    return;

state_2:
    temp_v1_3 = arg2->unk_0C.at00.v;
    temp_v1_3 -= (s32)temp_v1_3 / ((S_819598B4_0 *)arg0)->unk_30;
    arg2->unk_0C.at00.v = temp_v1_3;
    arg2->unk_0C.at01.v = temp_v1_3;
    arg2->unk_0C.at02.v = temp_v1_3;
    temp_v0_2 = (u16)((S_819598B4_0 *)arg0)->unk_30 - 1;
    ((S_819598B4_0 *)arg0)->unk_30 = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto common;
    }
    ((S_819598B4_0_pre *)arg0)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;

common:
    if (((S_819598B4_0 *)arg0)->unk_38 != 0) {
        return;
    }
    if (((S_819598B4_0 *)arg0)->unk_3C != 0) {
        return;
    }
    temp_v0_3 = D_80028220[9] + 1;
    D_80028220[9] = temp_v0_3;
    if ((u32)(temp_v0_3 & 0xFF) >= 0x20U) {
        D_80028220[9] = 0;
    }
}

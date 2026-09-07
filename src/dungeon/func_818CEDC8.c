#include "common.h"
#include "m2c_compat.h"

typedef struct S_818CEDC8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_818CEDC8_0;   /* arg1 in func_818CEDC8 */

typedef struct S_818CEDC8_1_pre {
    u16 unk_00;
} S_818CEDC8_1_pre;   /* the 0x2 bytes before arg0 in func_818CEDC8, addressed as arg0[-1] */

typedef struct S_818CEDC8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x42];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818CEDC8_1;   /* arg0 in func_818CEDC8 */

typedef struct S_818CEDC8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818CEDC8_2;   /* arg2 in func_818CEDC8 */


extern s16 D_80025924[5];
extern s32 D_800814A0[3];
s32 rand();
s32 func_800A45D8();
s16 func_800BCB04();

void func_818CEDC8(void *arg0, S_818CEDC8_0 *arg1, S_818CEDC8_2 *arg2) {
    s32 temp_s0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    s32 call_a2;

    arg1->unk_00.at00.v = (s32) (arg1->unk_00.at00.v + ((S_818CEDC8_1 *)arg0)->unk_4C);
    ((S_818CEDC8_1 *)arg0)->unk_4C = (s32) (((S_818CEDC8_1 *)arg0)->unk_4C + ((S_818CEDC8_1 *)arg0)->unk_58);
    if ((func_800A45D8(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                       (call_a2 = arg1->unk_08.at02.v, *D_80025924 = 1, call_a2)) << 0x10) != 0) {
        arg1->unk_00.at00.v = (s32) (arg1->unk_00.at00.v - ((S_818CEDC8_1 *)arg0)->unk_4C);
        ((S_818CEDC8_1 *)arg0)->unk_4C = 0;
        ((S_818CEDC8_1 *)arg0)->unk_58 = 0;
    }
    arg1->unk_04.at00.v = (s32) (arg1->unk_04.at00.v + ((S_818CEDC8_1 *)arg0)->unk_50);
    ((S_818CEDC8_1 *)arg0)->unk_50 = (s32) (((S_818CEDC8_1 *)arg0)->unk_50 + ((S_818CEDC8_1 *)arg0)->unk_5C);
    if ((func_800A45D8(arg1->unk_00.at02.v, arg1->unk_04.at02.v, arg1->unk_08.at02.v) << 0x10) != 0) {
        arg1->unk_04.at00.v = (s32) (arg1->unk_04.at00.v - ((S_818CEDC8_1 *)arg0)->unk_50);
        ((S_818CEDC8_1 *)arg0)->unk_50 = 0;
        ((S_818CEDC8_1 *)arg0)->unk_5C = 0;
    }
    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + ((S_818CEDC8_1 *)arg0)->unk_54);
    {
        s32 temp_az = ((S_818CEDC8_1 *)arg0)->unk_60;
        ((S_818CEDC8_1 *)arg0)->unk_54 += temp_az;
    }
    ((S_818CEDC8_1 *)arg0)->unk_4C = (s32) ((((S_818CEDC8_1 *)arg0)->unk_4C * 0x60) / 100);
    ((S_818CEDC8_1 *)arg0)->unk_50 = (s32) ((((S_818CEDC8_1 *)arg0)->unk_50 * 0x60) / 100);
    temp_s0 = arg1->unk_08.at02.v;
    if ((func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v, (s16) ((u16) arg1->unk_08.at02u.v - 4)) - 0x10) < temp_s0) {
        ((S_818CEDC8_1 *)arg0)->unk_54 = 0;
        arg1->unk_08.at02.v = (s16) (func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v, (s16) ((u16) arg1->unk_08.at02.v - 4)) - 0x11);
        arg1->unk_08.at00u.v = 0;
        if (((S_818CEDC8_1 *)arg0)->unk_08 == 0) {
            ((S_818CEDC8_1 *)arg0)->unk_08 = 1;
            ((S_818CEDC8_1 *)arg0)->unk_4C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
            ((S_818CEDC8_1 *)arg0)->unk_50 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
        }
    }
    temp_v0 = ((S_818CEDC8_1 *)arg0)->unk_04 + 1;
    ((S_818CEDC8_1 *)arg0)->unk_04 = temp_v0;
    if (!(temp_v0 & 3)) {
        func_800478B8(arg2);
    }
    temp_v0_2 = arg2->unk_1C + 0x64;
    arg2->unk_1C = temp_v0_2;
    if ((u32) (temp_v0_2 & 0xFFFF) >= 0x1001U) {
        arg2->unk_1C = 0x1000U;
    }
    temp_v0_3 = arg2->unk_1E + 0x64;
    arg2->unk_1E = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) >= 0x1001U) {
        arg2->unk_1E = 0x1000U;
    }
    temp_v0_4 = ((S_818CEDC8_1 *)arg0)->unk_02 - 1;
    ((S_818CEDC8_1 *)arg0)->unk_02 = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        ((S_818CEDC8_1_pre *)arg0)[-1].unk_00 = (u16) (((S_818CEDC8_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
    if (arg2->unk_14 & 0x8000) {
        ((S_818CEDC8_1_pre *)arg0)[-1].unk_00 = (u16) (((S_818CEDC8_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}

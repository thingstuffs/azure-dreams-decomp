#include "common.h"
#include "m2c_compat.h"

typedef struct S_8196ACE4_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8196ACE4_0;   /* arg1 in func_8196ACE4 */

typedef struct S_8196ACE4_1_pre {
    u16 unk_00;
} S_8196ACE4_1_pre;   /* the 0x2 bytes before arg0 in func_8196ACE4, addressed as arg0[-1] */

typedef struct S_8196ACE4_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x4];
    u16 unk_34;
    u8 pad_36[0x56];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196ACE4_1;   /* arg0 in func_8196ACE4 */

typedef struct S_8196ACE4_2 {
    u8 pad_00[0x69B4];
    s16 unk_69B4;
} S_8196ACE4_2;   /* page_8002 in func_8196ACE4 */

typedef struct S_8196ACE4_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8196ACE4_3;   /* arg2 in func_8196ACE4 */

typedef struct S_8196ACE4_4 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8196ACE4_4;   /* page_8008 in func_8196ACE4 */


M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
s32 func_800A45D8();                   /* extern */
s16 func_800BCB04();                   /* extern */
extern s16 D_800269B4[];
extern M2C_UNK D_800814A0;

void func_8196ACE4(void *arg0, S_8196ACE4_0 *arg1, S_8196ACE4_3 *arg2) {
    s32 temp_s0;
    s16 temp_v0_4;
    s32 temp_lo;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 collide_x;
    u16 collide_y;
    s32 collide_z;

    arg1->unk_00.at00.v = (s32) (arg1->unk_00.at00.v + ((S_8196ACE4_1 *)arg0)->unk_8C);
    ((S_8196ACE4_1 *)arg0)->unk_8C = (s32) (((S_8196ACE4_1 *)arg0)->unk_8C + ((S_8196ACE4_1 *)arg0)->unk_98);
    collide_x = arg1->unk_00.at02.v;
    collide_y = arg1->unk_04.at02.v;
    collide_z = arg1->unk_08.at02.v;
    {
        u8 *page_8002 = (u8 *)&D_800269B4 - 0x69B4;
        ((S_8196ACE4_2 *)page_8002)->unk_69B4 = 1;
    }
    if ((func_800BCB04(collide_x, collide_y, collide_z) < 0x200) && ((func_800A45D8(arg1->unk_00.at02.v, arg1->unk_04.at02.v, arg1->unk_08.at02.v) << 0x10) != 0)) {
        arg1->unk_00.at00.v = (s32) (arg1->unk_00.at00.v - ((S_8196ACE4_1 *)arg0)->unk_8C);
        ((S_8196ACE4_1 *)arg0)->unk_8C = 0;
        ((S_8196ACE4_1 *)arg0)->unk_98 = 0;
    }
    arg1->unk_04.at00.v = (s32) (arg1->unk_04.at00.v + ((S_8196ACE4_1 *)arg0)->unk_90);
    ((S_8196ACE4_1 *)arg0)->unk_90 = (s32) (((S_8196ACE4_1 *)arg0)->unk_90 + ((S_8196ACE4_1 *)arg0)->unk_9C);
    if ((func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v, arg1->unk_08.at02.v) < 0x200) && ((func_800A45D8(arg1->unk_00.at02.v, arg1->unk_04.at02.v, arg1->unk_08.at02.v) << 0x10) != 0)) {
        arg1->unk_04.at00.v = (s32) (arg1->unk_04.at00.v - ((S_8196ACE4_1 *)arg0)->unk_90);
        ((S_8196ACE4_1 *)arg0)->unk_90 = 0;
        ((S_8196ACE4_1 *)arg0)->unk_9C = 0;
    }
    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + ((S_8196ACE4_1 *)arg0)->unk_94);
    {
        s32 temp_az = ((S_8196ACE4_1 *)arg0)->unk_A0;
        ((S_8196ACE4_1 *)arg0)->unk_94 += temp_az;
    }
    ((S_8196ACE4_1 *)arg0)->unk_8C = (s32) ((((S_8196ACE4_1 *)arg0)->unk_8C * 0x60) / 100);
    ((S_8196ACE4_1 *)arg0)->unk_90 = (s32) ((((S_8196ACE4_1 *)arg0)->unk_90 * 0x60) / 100);
    temp_s0 = arg1->unk_08.at02.v;
    if ((func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v, (s16) (arg1->unk_08.at02u.v - 4)) - 0x10) < temp_s0) {
        ((S_8196ACE4_1 *)arg0)->unk_94 = 0;
        arg1->unk_08.at02.v = (s16) (func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v, (s16) ((u16) arg1->unk_08.at02.v - 4)) - 0x11);
        arg1->unk_08.at00u.v = 0;
        if (((S_8196ACE4_1 *)arg0)->unk_2A == 0) {
            ((S_8196ACE4_1 *)arg0)->unk_2A = 1;
            ((S_8196ACE4_1 *)arg0)->unk_8C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
            ((S_8196ACE4_1 *)arg0)->unk_90 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
        }
    }
    temp_lo = (s32) (((S_8196ACE4_1 *)arg0)->unk_2C << 7) / (s16) ((S_8196ACE4_1 *)arg0)->unk_2E;
    arg2->unk_0E = (s8) temp_lo;
    arg2->unk_0D = (s8) temp_lo;
    arg2->unk_0C = (s8) temp_lo;
    temp_v0 = ((S_8196ACE4_1 *)arg0)->unk_34 + 1;
    ((S_8196ACE4_1 *)arg0)->unk_34 = temp_v0;
    if ((s16) temp_v0 == 3) {
        func_800478B8(arg2);
        ((S_8196ACE4_1 *)arg0)->unk_34 = 0U;
    }
    temp_v0_2 = arg2->unk_1C + 0xC8;
    arg2->unk_1C = temp_v0_2;
    if ((u32) (temp_v0_2 & 0xFFFF) >= 0x1001U) {
        arg2->unk_1C = 0x1000U;
    }
    temp_v0_3 = arg2->unk_1E + 0xC8;
    arg2->unk_1E = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) >= 0x1001U) {
        arg2->unk_1E = 0x1000U;
    }
    temp_v0_4 = (u16) ((S_8196ACE4_1 *)arg0)->unk_2C - 1;
    ((S_8196ACE4_1 *)arg0)->unk_2C = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        ((S_8196ACE4_1_pre *)arg0)[-1].unk_00 = (u16) (((S_8196ACE4_1_pre *)arg0)[-1].unk_00 | 0x8000);
        {
            u8 *page_8008 = (u8 *)0x80080000;
            ((S_8196ACE4_4 *)page_8008)->unk_14A0 |= 0x8000;
        }
    }
    if (arg2->unk_14 & 0x8000) {
        ((S_8196ACE4_1_pre *)arg0)[-1].unk_00 = (u16) (((S_8196ACE4_1_pre *)arg0)[-1].unk_00 | 0x8000);
        {
            u8 *page_8008 = (u8 *)0x80080000;
            ((S_8196ACE4_4 *)page_8008)->unk_14A0 |= 0x8000;
        }
    }
}

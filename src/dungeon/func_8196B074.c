#include "common.h"

typedef struct S_8196B074_0 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x5E];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196B074_0;   /* arg0 in func_8196B074 */

typedef struct S_8196B074_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8196B074_1;   /* arg1 in func_8196B074 */



extern s32 func_800478B8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s16 D_800269B4;
extern s32 D_800814A0;

void func_8196B074(void *arg0, void *arg1, s32 arg2) {
    s32 temp_s0;
    u16 value;

    value = ((S_8196B074_0 *)arg0)->unk_2C;
    D_800269B4 = 1;
    ((S_8196B074_0 *)arg0)->unk_2C = value - 1;
    func_800478B8(arg2);
    ((S_8196B074_1 *)arg1)->unk_00.at00.v += ((S_8196B074_0 *)arg0)->unk_8C;
    ((S_8196B074_0 *)arg0)->unk_8C += ((S_8196B074_0 *)arg0)->unk_98;
    if ((func_800A45D8(((S_8196B074_1 *)arg1)->unk_00.at02.v, ((S_8196B074_1 *)arg1)->unk_04.at02.v, ((S_8196B074_1 *)arg1)->unk_08.at02.v) << 16) != 0) {
        ((S_8196B074_1 *)arg1)->unk_00.at00.v -= ((S_8196B074_0 *)arg0)->unk_8C;
        ((S_8196B074_0 *)arg0)->unk_8C = 0;
        ((S_8196B074_0 *)arg0)->unk_98 = 0;
    }
    ((S_8196B074_1 *)arg1)->unk_04.at00.v += ((S_8196B074_0 *)arg0)->unk_90;
    ((S_8196B074_0 *)arg0)->unk_90 += ((S_8196B074_0 *)arg0)->unk_9C;
    if ((func_800A45D8(((S_8196B074_1 *)arg1)->unk_00.at02.v, ((S_8196B074_1 *)arg1)->unk_04.at02.v, ((S_8196B074_1 *)arg1)->unk_08.at02.v) << 16) != 0) {
        ((S_8196B074_1 *)arg1)->unk_04.at00.v -= ((S_8196B074_0 *)arg0)->unk_90;
        ((S_8196B074_0 *)arg0)->unk_90 = 0;
        ((S_8196B074_0 *)arg0)->unk_9C = 0;
    }
    ((S_8196B074_1 *)arg1)->unk_08.at00.v += ((S_8196B074_0 *)arg0)->unk_94;
    ((S_8196B074_0 *)arg0)->unk_94 += ((S_8196B074_0 *)arg0)->unk_A0;
    temp_s0 = ((S_8196B074_1 *)arg1)->unk_08.at02.v;
    if ((func_800BCB04(((S_8196B074_1 *)arg1)->unk_00.at02.v, ((S_8196B074_1 *)arg1)->unk_04.at02.v,
                       (s16)((u16)((S_8196B074_1 *)arg1)->unk_08.at02u.v - 4)) - 0x10) < temp_s0) {
        ((S_8196B074_0 *)arg0)->unk_94 = 0;
        ((S_8196B074_0 *)arg0)->unk_90 = 0;
        ((S_8196B074_0 *)arg0)->unk_8C = 0;
        ((S_8196B074_1 *)arg1)->unk_08.at02.v = func_800BCB04(((S_8196B074_1 *)arg1)->unk_00.at02.v, ((S_8196B074_1 *)arg1)->unk_04.at02.v,
                                               (s16)((u16)((S_8196B074_1 *)arg1)->unk_08.at02.v - 4)) - 0x11;
        ((S_8196B074_1 *)arg1)->unk_08.at00u.v = 0;
        ((S_8196B074_0 *)arg0)->unk_2C = 0;
    }
    if ((s16)((S_8196B074_0 *)arg0)->unk_2C <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

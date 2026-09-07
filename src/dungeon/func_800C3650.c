#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C8DB0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u8 unk_0E;
    u8 pad_0F[0x4];
    u8 unk_13;
    s32 unk_14;
} S_800C8DB0_0;   /* arg0 in func_800C8DB0 */


M2C_UNK func_80099844();
s32 func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800DC1B8();
extern s32 D_800DCF20;
extern M2C_UNK D_800E1937;
extern M2C_UNK D_800E1A6D;

s32 func_800C8DB0(S_800C8DB0_0 *arg0, s16 arg1, s8 arg2) {
    s16 temp_v1;
    s32 temp_a0;
    u8 temp_a0_2;

    if ((arg0->unk_13 != 0) && ((arg0->unk_08.at00.v & 0xFF0000FF) || (arg0->unk_0E != 0))) {
        temp_a0_2 = arg0->unk_0E;
        if (((u8) arg0->unk_08.at00.v + arg0->unk_08.at03.v + temp_a0_2) != 0) {
            temp_a0 = func_800A6D30(temp_a0_2) & 0xFFFF;
            if (arg0->unk_03 != 0) {
                temp_v1 = temp_a0 % arg0->unk_03;
            } else {
                temp_v1 = 0;
            }
            if ((temp_v1 < arg1 || arg1 == 0xFF) && (s16)func_800A48F0(arg0, 6, arg2) >= 0) {
                func_80099844(arg0, &D_800E1937);
                if (arg0->unk_13 == 0) {
                    func_800DC1B8(D_800DCF20);
                }
                return 1;
            }
        }
    }
    if (arg0->unk_14 & 0x4000) {
        func_80099844(arg0, &D_800E1A6D);
    }
    return 0;
}

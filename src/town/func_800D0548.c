#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
s32 func_800C30E0();         /* extern */
M2C_UNK func_800CDD7C();                            /* extern */
M2C_UNK func_800CDE9C();     /* extern */
M2C_UNK func_800CDFF8();     
typedef struct S_800CDCA8_0 {
    u8 pad_00[0x6E];
    u16 unk_6E;
    u8 pad_70[0x2];
    u16 unk_72;
    u8 pad_74[0x1C];
    u16 unk_90;
} S_800CDCA8_0;   /* arg0 in func_800CDCA8 */

typedef struct S_800CDCA8_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CDCA8_1;   /* arg1 in func_800CDCA8 */

/* extern */

void func_800CDCA8(S_800CDCA8_0 *arg0, S_800CDCA8_1 *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg0->unk_72 = (u16) (arg0->unk_72 + 0x400);
    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + arg1->unk_14);
    if (func_800C2AE8(arg1) < arg1->unk_08.at02.v) {
        arg1->unk_08.at02.v = func_800C2AE8(arg1);
        temp_v0 = arg0->unk_90 - 1;
        arg0->unk_90 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            arg1->unk_14 = 0;
            arg0->unk_72 = (u16) arg0->unk_6E;
            func_800CDE9C(arg0, arg1, arg2);
            func_800CDD7C();
            return;
        }
        if (func_800C30E0(arg0, arg1, arg2) == 0) {
            func_800CDFF8(arg0, arg1, arg2);
            func_800CDD7C();
        }
    } else {
        func_80095388(arg1);
    }
}

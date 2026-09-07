#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
M2C_UNK func_800C9BF0();                            /* extern */
M2C_UNK func_800C9C94();     /* extern */
M2C_UNK func_800C9DB8();     
typedef struct S_800C9B44_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C9B44_0;   /* arg1 in func_800C9B44 */

typedef struct S_800C9B44_1 {
    u8 pad_00[0x90];
    u16 unk_90;
} S_800C9B44_1;   /* arg0 in func_800C9B44 */

/* extern */

void func_800C9B44(S_800C9B44_1 *arg0, S_800C9B44_0 *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + arg1->unk_14);
    if (func_800C2AE8(arg1) < arg1->unk_08.at02.v) {
        arg1->unk_08.at02.v = func_800C2AE8(arg1);
        temp_v0 = arg0->unk_90 - 1;
        arg0->unk_90 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            arg1->unk_14 = 0;
            func_800C9DB8(arg0, arg1, arg2);
            func_800C9BF0();
            return;
        }
        func_800C9C94(arg0, arg1, arg2);
        func_800C9BF0();
        return;
    }
    func_80095388(arg1);
}

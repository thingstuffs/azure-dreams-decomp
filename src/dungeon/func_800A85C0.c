#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)


typedef struct S_800ADD20_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x80];
    u16 unk_98;
} S_800ADD20_0;   /* arg0 in func_800ADD20 */


extern s32 func_800A6D30(S_800ADD20_0 *, s32, s32, s32);
void func_800ADD20(S_800ADD20_0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    u16 temp_v0;

    temp_v1 = arg0->unk_14;
    if (!(temp_v1 & 0x8000)) {
        arg0->unk_14 = (s32) (temp_v1 | 0x8000);
        if (((s32) (func_800A6D30(arg0, arg1, arg2, arg3) & 0xFFFF) % arg1) != 0) {
            temp_v0 = arg0->unk_98;
            temp_v0 = (u16) (temp_v0 & 0xFEFF);
        } else {
            temp_v0 = arg0->unk_98;
            temp_v0 = (u16) (temp_v0 | 0x100);
        }
        arg0->unk_98 = temp_v0;
    }
}

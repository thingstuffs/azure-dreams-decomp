#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B5264_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B5264_1;   /* arg0 in func_800B5264 */

typedef struct S_800B5264_2 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x2];
    s8 unk_0E;
} S_800B5264_2;   /* ((S_800B5264_1 *)arg0)->unk_04 in func_800B5264 */




s32 func_8004DC14();                /* extern */
M2C_UNK func_8004E99C();                         /* extern */

typedef struct S_800B5264_0 {
    s32 unk_00;
} S_800B5264_0;   /* arg0 in func_800B5264 */

void func_800B5264(S_800B5264_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, s16 arg3, s32 arg4) {
    s32 temp_a0;

    temp_a0 = arg0->unk_00;
    if (temp_a0 != 0) {
        func_8004E99C(temp_a0);
        arg0->unk_00 = 0;
    }
    ((S_800B5264_2 *)(((S_800B5264_1 *)arg0)->unk_04))->unk_08 = arg3;
    ((S_800B5264_2 *)(((S_800B5264_1 *)arg0)->unk_04))->unk_0A = (s16) arg4;
    arg0->unk_00 = func_8004DC14(arg1, arg2);
    ((S_800B5264_2 *)(((S_800B5264_1 *)arg0)->unk_04))->unk_0E = 2;
}

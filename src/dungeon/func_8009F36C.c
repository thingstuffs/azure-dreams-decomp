#include "common.h"

typedef struct S_800A4ACC_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    s8 unk_2D;
} S_800A4ACC_0;   /* var_s0 in func_800A4ACC */

typedef struct S_800A4ACC_1 {
    s32 unk_00;
} S_800A4ACC_1;   /* arg0 in func_800A4ACC; pointer addresses record offset 0x18 */


extern void func_80042BDC();
extern void func_800A5DFC();

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A4ACC(void *arg0) {
    s32 var_s1;
    s8 temp_v1;
    s8 temp_v1_2;
    u8 temp_a1;
    void *var_s0;

    var_s1 = 3;
    var_s0 = arg0 + 6;
loop_1:
    temp_v1 = ((S_800A4ACC_0 *)var_s0)->unk_2C;
    if (temp_v1 != 0) {
        if (temp_v1 == 5) {
            func_800A5DFC(arg0, ((S_800A4ACC_1 *)((u8 *)arg0 - 0x18))->unk_00);
        }
        temp_v1_2 = ((S_800A4ACC_0 *)var_s0)->unk_2D;
        if (temp_v1_2 != 0) {
            if (temp_v1_2 > 0) {
                ((S_800A4ACC_0 *)var_s0)->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)var_s0)->unk_2D - 1);
            } else if (temp_v1_2 < 0) {
                ((S_800A4ACC_0 *)var_s0)->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)var_s0)->unk_2D + 1);
            }
            if (((S_800A4ACC_0 *)var_s0)->unk_2D == 0) {
                temp_a1 = (u8)((S_800A4ACC_0 *)var_s0)->unk_2C;
                ((S_800A4ACC_0 *)var_s0)->unk_2C = 0;
                func_80042BDC(arg0, (s8)temp_a1);
            }
        }
    }
    var_s1 -= 1;
    var_s0 -= 2;
    if (var_s1 >= 0) {
        goto loop_1;
    }
}

#include "common.h"





#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001A3D0(void);
extern s32 func_8001E578();
extern s32 func_8001E670();
extern u8 D_8001791C[96];

typedef struct S_8001A360_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_8001A360_0;   /* var_s0 in func_8001A360 */

s32 func_8001A360(void) {
    s32 var_s1;
    u8 *var_s0;
    u8 *temp_v0;

    var_s1 = 1;
    temp_v0 = D_8001791C;
    var_s0 = temp_v0 + 0xC;
loop_1:
    if ((func_8001E670(((S_8001A360_0 *)var_s0)->unk_04) != 0) && (func_8001E670(((S_8001A360_0 *)var_s0)->unk_06) == 0)) {
        func_8001E578(((S_8001A360_0 *)var_s0)->unk_06);
        return var_s1;
    }
    var_s1 += 1;
    if (var_s1 < 8) {
        var_s0 += 0xC;
        goto loop_1;
    }
    return 0;
}

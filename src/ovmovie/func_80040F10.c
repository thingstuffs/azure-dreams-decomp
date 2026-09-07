#include "common.h"
#include "m2c_compat.h"

extern u8 D_80178240;
extern s32 D_80178280;
extern s32 D_801782C4;

typedef struct S_80040F10_0 {
    s32 unk_00;
} S_80040F10_0;   /* var_a1 in func_80040F10 */

typedef struct S_80040F10_1 {
    s32 unk_00;
} S_80040F10_1;   /* var_a2 in func_80040F10 */

typedef struct S_80040F10_2 {
    s32 unk_00;
} S_80040F10_2;   /* var_a1_2 in func_80040F10 */

typedef struct S_80040F10_3 {
    s32 unk_00;
} S_80040F10_3;   /* var_a2_2 in func_80040F10 */

typedef struct S_80040F10_4 {
    s32 unk_00;
} S_80040F10_4;   /* var_a1_3 in func_80040F10 */

typedef struct S_80040F10_5 {
    s32 unk_00;
} S_80040F10_5;   /* var_a2_3 in func_80040F10 */

s32 *func_80040F10(s8 *arg0) {
    s8 *var_a1;
    s8 *var_a1_2;
    s8 *var_a1_3;
    s8 *var_a2;
    s8 *var_a2_2;
    s8 *var_a2_3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    var_a2 = arg0;
    var_a1 = &D_80178240;
    var_v1 = 0xF;
    do {
        temp_v0 = ((S_80040F10_0 *)var_a1)->unk_00;
        var_a1 += 4;
        var_v1 -= 1;
        ((S_80040F10_1 *)var_a2)->unk_00 = temp_v0;
        var_a2 += 4;
    } while (var_v1 != -1);
    var_a2_2 = arg0 + 0x40;
    var_a1_2 = &D_80178280;
    var_v1_2 = 0xF;
    do {
        temp_v0_2 = ((S_80040F10_2 *)var_a1_2)->unk_00;
        var_a1_2 += 4;
        var_v1_2 -= 1;
        ((S_80040F10_3 *)var_a2_2)->unk_00 = temp_v0_2;
        var_a2_2 += 4;
    } while (var_v1_2 != -1);
    var_a2_3 = arg0 + 0x80;
    var_a1_3 = &D_801782C4;
    var_v1_3 = 0x1F;
    do {
        temp_v0_3 = ((S_80040F10_4 *)var_a1_3)->unk_00;
        var_a1_3 += 4;
        var_v1_3 -= 1;
        ((S_80040F10_5 *)var_a2_3)->unk_00 = temp_v0_3;
        var_a2_3 += 4;
    } while (var_v1_3 != -1);
    return arg0;
}

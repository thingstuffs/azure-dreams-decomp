#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Func8180F0F4_Obj {
    u8 pad00[0x11];
    u8 field11;
    u8 pad12[2];
    u16 field14;
    u8 pad16[2];
    u32 field18;
    u8 pad1c[0x38];
    s32 field54;
} Func8180F0F4_Obj;

extern s16 D_8008347E;

void *func_800280F4(Func8180F0F4_Obj *arg0, Func8180F0F4_Obj *arg1, s16 *arg2) {
    s16 temp_v0;
    u16 var_v1_2;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_v0_3;
    u16 temp_a0;
    u16 temp_a1;
    u32 var_v0_2;
    u32 var_v1;
    Func8180F0F4_Obj *var_a3;
    void *ret;

    temp_a3 = arg0->field54;
    temp_v1 = arg1->field54;
    if (!(temp_a3 & temp_v1 & 0x800000)) {
        if (!(temp_a3 & 0x800000) && !(temp_v1 & 0x400000)) {
            if ((temp_v1 & 0x800000) || (temp_a3 & 0x400000)) {
                var_a3 = arg1;
            } else {
                var_v1 = arg0->field11;
                var_v0_2 = arg1->field11;
                var_a3 = arg1;
                if ((var_v1 == var_v0_2) &&
                    (var_v1 = arg0->field18,
                     var_v0_2 = arg1->field18,
                     (var_v1 == var_v0_2))) {
                    var_v0_3 = D_8008347E & 1;
                } else {
                    var_v0_3 = var_v0_2 < var_v1;
                }
                if (var_v0_3 != 0) {
                    goto block_11;
                }
            }
        } else {
    block_11:
            var_a3 = arg0;
        }
        ret = var_a3;
        temp_a0 = arg0->field14;
        do {
            temp_a1 = arg1->field14;
        } while (0);
        temp_v0 = temp_a0 & 7;
        var_v1_2 = temp_a1 & 7;
        if (temp_v0 == var_v1_2) {
            var_v1_2 = temp_v0;
        } else if (temp_a0 & 1) {
            var_v1_2 = 1;
            if (temp_a1 & 2) {
                var_v1_2 = 2;
            }
        } else if (temp_a0 & 2) {
            var_v1_2 = 2;
            if (temp_a1 & 4) {
                var_v1_2 = 4;
            }
        } else if (temp_a0 & 4) {
            var_v1_2 = 4;
            if (temp_a1 & 1) {
                var_v1_2 = 1;
            }
        }
        *arg2 = var_v1_2;
        return ret;
    }
    return NULL;
}

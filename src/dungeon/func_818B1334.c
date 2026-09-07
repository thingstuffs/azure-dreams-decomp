#include "common.h"
#include "m2c_compat.h"

extern void func_80024610(void *, void *, void *, s32, s32, M2C_UNK *, s32, s32);
extern s32 func_800644B8();
extern s32 func_80064584();

typedef struct S_818B1334_0 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} S_818B1334_0;   /* var_s2 in func_818B1334 */

typedef struct S_818B1334_1 {
    u8 pad_00[0x10];
    s16 unk_10;
} S_818B1334_1;   /* arg0 in func_818B1334 */

typedef struct S_818B1334_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818B1334_2;   /* var_s2_2 in func_818B1334 */

typedef struct S_818B1334_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818B1334_3;   /* arg1 in func_818B1334 */

s32 func_818B1334(S_818B1334_1 *arg0, S_818B1334_3 *arg1, void *arg2) {
    M2C_UNK sp20[34];
    M2C_UNK *var_s2;
    register M2C_UNK *var_s5;
    s16 temp_s0_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    u16 temp_a2;
    void *var_s2_2;
    void *call_a0;

    var_s5 = sp20;
    var_s1 = 0x10;
    var_s2 = var_s5 + 16;
    do {
        var_s0 = var_s1;
        if (var_s1 < 0) {
            var_s0 = var_s1 + 0xF;
        }
        temp_s0 = (var_s1 - ((var_s0 >> 4) * 0x10)) << 8;
        ((S_818B1334_0 *)var_s2)->unk_00 = (s32) (func_800644B8(temp_s0) >> 4);
        ((S_818B1334_0 *)var_s2)->unk_44 = (s32) (func_80064584(temp_s0) >> 4);
        var_s2 -= 1;
    } while (--var_s1 >= 0);
    var_s1_2 = 0;
    var_s2_2 = arg0;
    do {
        temp_v0 = arg0->unk_10 - var_s1_2;
        var_a0 = temp_v0;
        if (temp_v0 < 0) {
            var_a0 = temp_v0 + 0xF;
        }
        temp_s0_2 = (func_800644B8((temp_v0 - ((var_a0 >> 4) * 0x10)) << 9) >> 9) + 0x20;
        func_80064584(var_s1_2 << 0xA);
        call_a0 = arg0;
        ASM_KEEP(call_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_a2 = ((S_818B1334_2 *)var_s2_2)->unk_1A;
        var_s2_2 += 2;
        temp_a1 = var_s1_2 << 0x11;
        var_s1_2 += 1;
        func_80024610(call_a0, arg1, arg2, temp_s0_2, (s32) (s16) (arg1->unk_0A - temp_a2), var_s5, 0xFF, temp_a1 >> 0x10);
    } while (var_s1_2 < 8);
    return 0;
}

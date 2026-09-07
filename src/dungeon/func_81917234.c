#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A0[3];
extern s32 D_800DEDB0[3];
M2C_UNK func_80024600();
s32 func_8003DB94();
s32 func_800644B8();
s32 func_80064584();
s32 rand();

typedef struct S_80024A34_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80024A34_0;   /* temp_a0 in func_80024A34 */

typedef struct S_80024A34_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024A34_1;   /* arg2 in func_80024A34 */

typedef struct S_80024A34_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024A34_2;   /* arg1 in func_80024A34 */

void func_80024A34(void *arg0, S_80024A34_2 *arg1, S_80024A34_1 *arg2) {
    s16 temp_s1;
    s16 temp_s2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s32 *flags_base;
    void **var_a1;
    S_80024A34_0 *temp_a0;

    var_a2 = 0;
    flags_base = (s32 *)(u32)0x80080000;
    var_a1 = (void **)arg0;
    do {
        if ((temp_a0 = var_a1[5]) != NULL) {
            u16 node_flags;
            s32 global_flags;
            node_flags = temp_a0->unk_1E;
            global_flags = flags_base[0x528];
            node_flags = (u16)(node_flags | 0x8000);
            global_flags = global_flags | 0x8000;
            temp_a0->unk_1E = node_flags;
            flags_base[0x528] = global_flags;
        }
        var_a2 += 1;
        var_a1 += 1;
    } while (var_a2 < 3);
    func_8003DB94(arg2, D_800DEDB0, 0, flags_base);
    arg2->unk_0E = 0xC0;
    arg2->unk_0D = 0xC0;
    arg2->unk_0C = 0xC0;
    arg2->unk_1E = 0x800;
    arg2->unk_1C = 0x800;
    arg2->unk_14 = (u16) (arg2->unk_14 | 0xC);
    arg2->unk_10 = (u16) (arg2->unk_10 | 0x20);
    var_v0 = rand();
    temp_v0 = var_v0;
    if (temp_v0 < 0) {
        var_v0 = (s32) (temp_v0 + 0xFFF);
    }
    var_v0 >>= 0xC;
    arg2->unk_1A = (s16) (temp_v0 - (var_v0 << 0xC));
    temp_v0_2 = rand();
    var_v0_2 = temp_v0_2;
    if (temp_v0_2 < 0) {
        var_v0_2 = temp_v0_2 + 0xFFF;
    }
    var_v0_2 >>= 0xC;
    temp_s2 = temp_v0_2 - (var_v0_2 << 0xC);
    temp_v0_3 = rand();
    var_s1 = temp_v0_3;
    if (temp_v0_3 < 0) {
        var_s1 = temp_v0_3 + 0xFFF;
    }
    temp_s1 = temp_v0_3 - ((var_s1 >> 0xC) << 0xC);
    temp_s0 = func_800644B8(temp_s2);
    arg1->unk_00 = (s32) (arg1->unk_00 + ((temp_s0 >> 4) * (func_800644B8(temp_s1) >> 4) * 0x10));
    temp_s0_2 = func_800644B8(temp_s2);
    arg1->unk_04 = (s32) (arg1->unk_04 + ((temp_s0_2 >> 4) * (func_80064584(temp_s1) >> 4) * 0x10));
    arg1->unk_08 = (s32) (arg1->unk_08 + ((func_80064584(temp_s2) >> 4) << 0xC));
    func_80024600(arg0, arg1);
}

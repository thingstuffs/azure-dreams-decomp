#include "common.h"
#include "m2c_compat.h"

void func_804053A0(s32 arg0) {
    s32 sp10;
    s8 sp14;
    M2C_UNK sp50;
    s32 *var_a1;
    s32 temp_ret;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;
    s32 var_v1;
    void *temp_v1;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    temp_ret = (s32 (*)())0x80402268();
    temp_v0 = temp_ret;
    if (temp_v0 >= 3) {
        goto block_2;
    }
    (M2C_UNK (*)(s32, M2C_UNK, M2C_UNK))0x80051B50(arg0 + 0x80, 0x804006C4, 1);
    var_a1 = (s32 *)0x804006EC;
    var_a0 = arg0 + 0x188;
    goto block_3;
block_2:
    sp10 = *(s32 *)0x80400714;
    sp14 = *(s8 *)0x80400718;
    (M2C_UNK (*)(s32, M2C_UNK *))0x8003830C(temp_ret / 3, &sp50);
    (M2C_UNK (*)(s32 *, M2C_UNK *))0x8007BF50(&sp10, &sp50);
    (M2C_UNK (*)(s32 *, M2C_UNK))0x8007BF50(&sp10, 0x8040071C);
    var_a0 = arg0 + 0x80;
    var_a1 = &sp10;
block_3:
    (M2C_UNK (*)(s32, s32 *, M2C_UNK))0x80051B50(var_a0, var_a1, 1);
    var_a2 = 0;
    if (temp_v0 < 3) {
        goto block_5;
    }
block_4:
    if (var_a2 > 0) {
        goto block_8;
    }
block_5:
    var_v1 = var_a2 * 4;
loop_6:
    temp_v1 = M2C_FIELD((arg0 + var_v1), void **, 0xB18);
    M2C_FIELD(temp_v1, s32 *, 0) = (s32) (arg0 + ((var_a2 * 0x108) + 0x80));
    M2C_FIELD(M2C_FIELD(temp_v1, void **, 4), s16 *, 8) = 0xA9;
    M2C_FIELD(M2C_FIELD(temp_v1, void **, 4), s16 *, 0xA) = (s16) ((var_a2 * 0x10) + 0x110);
    var_a2 += 1;
    if (temp_v0 >= 3) {
        goto block_4;
    }
    var_v1 = var_a2 * 4;
    if (var_a2 < 2) {
        goto loop_6;
    }
block_8:
    return;
}

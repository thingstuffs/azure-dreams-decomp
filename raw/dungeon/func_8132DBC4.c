#include "common.h"
#include "m2c_compat.h"

u32 func_80065420(void **, s32, M2C_UNK, M2C_UNK);  /* extern */
s32 func_80066460(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_80067F20(void *, M2C_UNK, M2C_UNK, s32, s32); /* extern */

s32 func_80164BC4(void *arg0, void *arg1) {
    s32 *temp_a3;
    s32 *temp_v1;
    u32 temp_v0_2;
    void *temp_a1;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *var_s3;
    void *var_t0;

    var_s3 = arg0;
    var_t0 = arg1;
    temp_v0 = *(void **)0x80083160;
    *(void **)0x1F800024 = temp_v0 + 0xB0;
    *(void **)0x1F80001C = M2C_FIELD(temp_v0, void **, 0x8D0);
loop_1:
    temp_s0 = *(void **)0x1F80001C;
    *(void **)0x1F800004 = (u16) M2C_FIELD(var_t0, u16 *, 2);
    *(void **)0x1F800006 = (u16) M2C_FIELD(var_t0, u16 *, 6);
    *(void **)0x1F80001C = temp_s0 + 0xC;
    *(void **)0x1F800008 = (u16) M2C_FIELD(var_t0, u16 *, 0xA);
    temp_v0_2 = func_80065420((void **)0x1F800000, temp_s0 + 8, 0x1F800000, 0x1F800000);
    *(void **)0x1F800100 = temp_v0_2;
    if (temp_v0_2 < 0x1E0U) {
        M2C_FIELD(temp_s0, s8 *, 3) = 2;
        M2C_FIELD(temp_s0, s32 *, 4) = (s32) M2C_FIELD(var_s3, s32 *, 8);
        M2C_FIELD(temp_s0, s8 *, 7) = 0x6A;
        M2C_FIELD(temp_s0, s32 *, 0) = (s32) ((M2C_FIELD(temp_s0, s32 *, 0) & 0xFF000000) | (*((*(void **)0x1F800100 * 4) + *(void **)0x1F800024) & 0xFFFFFF));
        temp_a3 = (*(void **)0x1F800100 * 4) + *(void **)0x1F800024;
        *temp_a3 = (*temp_a3 & 0xFF000000) | ((s32) temp_s0 & 0xFFFFFF);
        temp_s0_2 = *(void **)0x1F80001C;
        *(void **)0x1F80001C = temp_s0_2 + 0xC;
        func_80067F20(temp_s0_2, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
        M2C_FIELD(temp_s0_2, s32 *, 0) = (s32) ((M2C_FIELD(temp_s0_2, s32 *, 0) & 0xFF000000) | (*((*(void **)0x1F800100 * 4) + *(void **)0x1F800024) & 0xFFFFFF));
        temp_v1 = (*(void **)0x1F800100 * 4) + *(void **)0x1F800024;
        *temp_v1 = (*temp_v1 & 0xFF000000) | ((s32) temp_s0_2 & 0xFFFFFF);
    }
    temp_a1 = M2C_FIELD(var_s3, void **, -8);
    var_s3 = temp_a1 + 0x20;
    if (temp_a1 != NULL) {
        var_t0 = M2C_FIELD(temp_a1, void **, 8);
        goto loop_1;
    }
    M2C_FIELD(*(void **)0x80080000, void **, 0x8D0) = (void *) *(void **)0x1F80001C;
    return 0;
}

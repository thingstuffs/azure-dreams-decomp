#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s16 D_8008346A[];
extern u8 D_80083780[12];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
s32 func_800644B8(s32);
s32 func_80064584(s32);
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
s32 func_80042900();
s32 func_800AD44C();
s32 func_800AD4AC();
M2C_UNK func_800B8228();

s32 func_800AD058(u8 *arg0, s32 *arg1, u8 *arg2, u8 *arg3) {
    M2C_UNK var_a0;
    M2C_UNK var_a1;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_flags;
    s32 temp_v1_8;
    s32 temp_value;
    s32 var_v0;
    register s32 dispatch_zero ASM_REG("$2");
    u16 temp_a0;
    u16 temp_v1_4;
    u8 temp_v0_2;
    register s32 temp_v1 ASM_REG("$3");
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    void *arg3_local = arg3;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto block_11;
    }
    ASM_KEEP_NV(temp_v1);
    if ((s32) temp_v1 < 2) {
        dispatch_zero = 0;
        if (temp_v1 == 0) {
            goto phase_0;
        }
        return func_800AD4AC(1);
    }
    if (temp_v1 == 2) {
        goto block_15;
    }
    dispatch_zero = 3;
    ASM_KEEP_NV(dispatch_zero);
    if (temp_v1 == 3) {
        dispatch_zero = 0;
        goto phase_3;
    }
    return func_800AD4AC();

phase_0:
    ASM_KEEP(dispatch_zero);
    ASM_CLOBBER("$3");
    if (*D_8008346A != 0) {
        return 0;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = 1U;
block_11:
    M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
    M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
    M2C_FIELD(arg3_local, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3_local, s32 *, 0x1C) | 0x10000000);
    temp_v1_5 = M2C_FIELD(arg3_local, u8 *, 0x13);
    if ((temp_v1_5 == 5) || (var_a0 = 0x805, (temp_v1_5 == 0x1E))) {
        var_a0 = 0x806;
    }
    func_800A56E0(var_a0);
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
    M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_15:
    temp_v1_6 = (u8) M2C_FIELD(arg2, s32 *, 0xC);
    M2C_FIELD(arg2, u8 *, 0xC) = (s8) (temp_v1_6 + ((s32) (0x20 - temp_v1_6) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    temp_v1_7 = M2C_FIELD(arg2, u8 *, 0xD);
    temp_v0_2 = M2C_FIELD(arg2, u8 *, 0xE);
    M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_v1_7 + ((s32) (0x20 - temp_v1_7) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_v0_2 + ((s32) (0x20 - temp_v0_2) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_3;
    if (((temp_v0_3 << 0x10) <= 0) || (var_v0 = 0, ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) != 0))) {
        if (!(M2C_FIELD(arg3_local, s32 *, 0x14) & 0x20000000)) {
            s32 *base = D_80083460;
            if (base[4] == (s32) (arg3_local - 0x20)) {
                base[4] = (s32) (base[4] & 0x7FFFFFFF);
            }
        }
        temp_v1_8 = M2C_FIELD(arg3_local, s32 *, 0x14);
        if (!(temp_v1_8 & 0x4000)) {
            func_800A2FE0(arg3_local);
            func_800A32A4(arg3_local);
            if (M2C_FIELD(arg3_local, u8 *, 0x49) == 0) {
                goto block_35;
            }
            {
                register void *cleanup_arg ASM_REG("$4") = arg3_local;

                ASM_KEEP_NV(cleanup_arg);
                if (M2C_FIELD(arg3_local, u8 *, 0x4B) & 0x20) {
                    goto block_35;
                }
                func_800B8228(M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg3_local, s16 *, 0x88), arg3_local + 0x48);
                {
                    register void *tail_reload ASM_REG("$4") = arg3_local;

                    ASM_TAILSLOT_PIN(tail_reload);
                }
                return func_800AD44C(cleanup_arg);
            }
        }
        if (!(temp_v1_8 & 0x20000000)) {
            func_800ACF88(arg3_local);
        }
        func_800A2FE0(arg3_local);
        func_800A32A4(arg3_local);
        if ((func_80042900(arg3_local, 0x1B) << 0x10) == 0) {
            temp_flags = M2C_FIELD(arg3_local, s32 *, 0x1C);
            var_a0 = M2C_FIELD(arg2, u8 *, 0x24);
            var_a1 = M2C_FIELD(arg2, u8 *, 0x25);
            var_a2_2 = 0x3000;
            if (temp_flags & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A3D0(var_a0, var_a1, var_a2_2);
        }
        func_8009A028(arg3_local);
        M2C_FIELD(arg3_local, u16 *, -2) = (u16) (M2C_FIELD(arg3_local, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
        func_800A56E0(0x609);
        func_800AD4AC();
        return 1;
    }
    return var_v0;

phase_3:
    ASM_KEEP(dispatch_zero);
    temp_value = (M2C_FIELD(arg0, s16 *, 0x96) * func_80064584(M2C_FIELD(arg2, u8 *, 0x27) << 7)) << 5;
    M2C_FIELD(arg1, s32 *, 0) += (s32) ((M2C_FIELD(D_80083780, s32 *, 0) + temp_value - M2C_FIELD(arg1, s32 *, 0)) >> 2);
    temp_value = (M2C_FIELD(arg0, s16 *, 0x96) * func_800644B8(M2C_FIELD(arg2, u8 *, 0x27) << 7)) << 5;
    M2C_FIELD(arg1, s32 *, 4) += (s32) ((M2C_FIELD(D_80083780, s32 *, 4) + temp_value - M2C_FIELD(arg1, s32 *, 4)) >> 2);
    {
        s32 vertical_step;

        vertical_step = func_800644B8(M2C_FIELD(arg0, s16 *, 0x96) * 8) >> 6;
        M2C_FIELD(arg3_local, s16 *, 0x88) = (s16) ((u16) M2C_FIELD(arg3_local, s16 *, 0x88) +
            ((M2C_FIELD(D_80083780, s16 *, 0xA) - vertical_step - M2C_FIELD(arg3_local, s16 *, 0x88)) >> 4));
    }
    temp_v1_4 = M2C_FIELD(arg2, u16 *, 0x1C);
    temp_a0 = M2C_FIELD(arg2, u16 *, 0x1E);
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (temp_v1_4 - ((s32) temp_v1_4 / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (temp_a0 - ((s32) temp_a0 / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    M2C_FIELD(arg2, u8 *, 0x27) = (u8) (M2C_FIELD(arg2, u8 *, 0x27) + 1);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    var_v0 = 0;
    if ((temp_v0 << 0x10) <= 0) {
        register s32 *base ASM_REG("$2") = D_80083460;

        ASM_KEEP_NV(base);
        M2C_FIELD(base, u16 *, 0xA) = (u16) (M2C_FIELD(base, u16 *, 0xA) - 1);
        func_800A2FE0(arg3_local);
        func_800A32A4(arg3_local);
        goto block_35;
    }
    return var_v0;

block_35:
    if ((func_80042900(arg3_local, 0x1B) << 0x10) == 0) {
        temp_flags = M2C_FIELD(arg3_local, s32 *, 0x1C);
        var_a0 = M2C_FIELD(arg2, u8 *, 0x24);
        var_a1 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (temp_flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(var_a0, var_a1, var_a2);
    }
    func_8009A028(arg3_local);
    M2C_FIELD(arg3_local, u16 *, -2) = (u16) (M2C_FIELD(arg3_local, u16 *, -2) | 0x8000);
    var_v0 = 1;
    D_800814A0[0] |= 0x8000;
    return var_v0;
}

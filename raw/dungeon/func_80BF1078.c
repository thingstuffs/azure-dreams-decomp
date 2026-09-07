#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern u8 D_80083498[];
extern u8 D_8016AA58[];
extern u8 D_80045340[];
extern s32 D_8016B014;
extern s32 D_8016E20C;
extern s32 D_8016E25C;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

void *func_8016A878(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 temp_v1;
    s32 state_flags0;
    s32 state_flags1;
    void *temp_s2;
    void *temp_s4;
    void *temp_v0;
    void *temp_s5;
    void *var_s0;
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");

    var_s0 = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 == 0) {
        goto done;
    }
    var_s0 = temp_v0 + 0x20;
    FIELD(temp_v0, u8 *, 0x10) = D_8016AA58;
    FIELD(var_s0, s8, 0x13) = 0x10;
    func_8004491C(temp_v0, D_80045340);
    temp_s4 = FIELD(temp_v0, void *, 8);
    FIELD(temp_s4, s16, 0xA) = saved_arg3;
    temp_s2 = FIELD(temp_v0, void *, 0xC);
    temp_v1 = arg0 & 3;
    FIELD(temp_s2, s8, 0x25) = saved_arg2;
    temp_s5 = var_s0;
    FIELD(temp_s2, s32 *, 0x2C) = &D_8016E20C;
    FIELD(temp_s2, s8, 0x24) = saved_arg1;
    if (temp_v1 == 1) {
        state_flags0 = FIELD(var_s0, s32, 0x14) | 0x6000;
        state_flags1 = FIELD(var_s0, s32, 0x1C) | 0x6000;
        FIELD(var_s0, s32, 0x14) = state_flags0;
        FIELD(var_s0, s32, 0x1C) = state_flags1;
    } else if (temp_v1 >= 2) {
        state_flags0 = FIELD(var_s0, s32, 0x14) | 0x2000;
        state_flags1 = FIELD(var_s0, s32, 0x1C) | 0x2000;
        FIELD(var_s0, s32, 0x14) = state_flags0;
        FIELD(var_s0, s32, 0x1C) = state_flags1;
    } else if (((arg0 & ~3) << 0x10) == 0) {
        register void *call_a0 ASM_REG("$4") = temp_v0;
        if (!(FIELD(var_s0, s32, 0x14) & 0x200)) {
            if (func_800A6D30(call_a0) & 1) {
                func_800A48F0(var_s0, 1, (func_800A6D30(call_a0) & 0x3F) | 0x20);
                FIELD(temp_s2, s32 *, 0x2C) = &D_8016E25C;
            }
        }
    }
    func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
    FIELD(temp_s5, u8, 0x9A) = 0xFF;
    FIELD(temp_s5, s8, 0x9C) = -1;
    FIELD(temp_s5, s32 *, 0x8C) = &D_8016B014;
    FIELD(var_s0, s32, 0x1C) = (s32)(FIELD(var_s0, s32, 0x1C) | 0x40000);
    FIELD(temp_s5, s16, 0x92) = -0x20;
    func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
done:
    return var_s0;
}

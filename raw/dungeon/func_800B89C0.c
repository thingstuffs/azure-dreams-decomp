#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
s32 func_800990FC(void);
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099368();
s32 func_80099734();
M2C_UNK func_80099844();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
s32 func_800BE340();
M2C_UNK func_800D5460();

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern M2C_UNK D_80082E80;
extern D_80083460_t D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_8008935C[];
extern u16 D_800DDE84[];
extern u8 D_800E0FF4[];
extern u8 D_800E100F[];
extern s32 D_800E3D7C[];

s32 func_800BE120(void *arg0, void *arg1, s16 arg2) {
    s32 state;
    register s32 state_test ASM_REG("$2");
    register void *call_arg ASM_REG("$4");
    register s32 pass_result ASM_REG("$5");
    register s32 hard_zero ASM_REG("$0");
    s32 raw_result;
    s32 result;

    state = 0;
#ifdef NON_MATCHING
    hard_zero = 0;
#endif
    if (arg0 == D_800E3D7C[0]) {
        M2C_FIELD(arg0, s32 *, 0x110) = (s32)arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        func_800BE340();
        return hard_zero;
    }

    if ((u32)arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (M2C_FIELD(arg0, u8 *, 0x13) >= 2) {
            if (!(M2C_FIELD(arg0, u32 *, 0x54) & 0x800000)) {
                if (M2C_FIELD(arg0, u8 *, 0x49) == 0) {
                    if (func_800AD6FC(arg0,
                            (D_800DDE84[M2C_FIELD(arg0, u8 *, 0x13)] >> 6) & 3,
                            0) == 0) {
                        goto block_finalize;
                    }
                    M2C_FIELD(arg0, s32 *, 0x48) = *(s32 *)arg1;
                    M2C_FIELD(arg0, u8 *, 0x48) = M2C_FIELD(arg1, u8 *, 0);
                    M2C_FIELD(arg0, u8 *, 0x49) = M2C_FIELD(arg1, u8 *, 1);
                    M2C_FIELD(arg0, u8 *, 0x4A) = M2C_FIELD(arg1, u8 *, 2);
                    M2C_FIELD(arg0, u8 *, 0x4B) = M2C_FIELD(arg1, u8 *, 3);
                    M2C_FIELD(arg0, u32 *, 0x54) |= 0x800000;
                    func_800D5460((s8 *)arg0 - 0x20, 0x20A0A0, 0x702);
                    state = 1;
                    if (M2C_FIELD(arg0, u32 *, 0x14) & 0x4000) {
                        func_80099844(arg0, D_800E0FF4);
                    }
                }
            }
        }
    }

    state_test = state;
    ASM_KEEP(state_test);
    if (state_test != 0) {
        goto block_end;
    }
    if ((M2C_FIELD(arg0, u8 *, 0x13) < 2) ||
        (M2C_FIELD(arg0, u32 *, 0x54) & 0x800000) ||
        (M2C_FIELD(arg0, u8 *, 0x49) != 0)) {
        raw_result = func_800990FC();
        call_arg = arg0;
        ASM_KEEP(call_arg);
        pass_result = raw_result;
        ASM_KEEP(pass_result);
        result = pass_result;
        func_80099290(func_80099194(D_8008935C,
            func_80099368(arg1, func_80099194(D_800E100F,
                func_80099734((s32)call_arg, pass_result)))));
        func_800A5720(result);
        goto block_finalize;
    }
    goto block_end;

block_finalize:
    func_800A5F38(arg0, arg1);
    func_800BE340();
    return 1;

block_end:
    func_80098B38(arg1);
    D_80083460.fieldA = (u16)(D_80083460.fieldA - 1);
    return 1;
}

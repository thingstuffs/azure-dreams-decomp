#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800BE120_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x30];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_48;   /* overlapping accesses */
    u8 pad_4C[0x8];
    u32 unk_54;
    u8 pad_58[0xB8];
    s32 unk_110;
} S_800BE120_0;   /* arg0 in func_800BE120 */

typedef struct S_800BE120_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800BE120_1;   /* arg1 in func_800BE120 */


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

s32 func_800BE120(void *arg0, S_800BE120_1 *arg1, s16 arg2) {
    s32 state;
    s32 state_test;
    void *call_arg;
    register s32 pass_result ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: retail register colouring depends on it */
    s32 raw_result;
    s32 result;

    state = 0;
#ifdef NON_MATCHING
    hard_zero = 0;
#endif
    if (arg0 == D_800E3D7C[0]) {
        ((S_800BE120_0 *)arg0)->unk_110 = (s32)arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        return hard_zero;
    }

    if ((u32)arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (((S_800BE120_0 *)arg0)->unk_13 >= 2) {
            if (!(((S_800BE120_0 *)arg0)->unk_54 & 0x800000)) {
                if (((S_800BE120_0 *)arg0)->unk_48.at01.v == 0) {
                    if (func_800AD6FC(arg0,
                            (D_800DDE84[((S_800BE120_0 *)arg0)->unk_13] >> 6) & 3,
                            0) == 0) {
                        goto block_finalize;
                    }
                    ((S_800BE120_0 *)arg0)->unk_48.at00.v = *(s32 *)arg1;
                    ((S_800BE120_0 *)arg0)->unk_48.at00u.v = arg1->unk_00;
                    ((S_800BE120_0 *)arg0)->unk_48.at01.v = arg1->unk_01;
                    ((S_800BE120_0 *)arg0)->unk_48.at02.v = arg1->unk_02;
                    ((S_800BE120_0 *)arg0)->unk_48.at03.v = arg1->unk_03;
                    ((S_800BE120_0 *)arg0)->unk_54 |= 0x800000;
                    func_800D5460((s8 *)arg0 - 0x20, 0x20A0A0, 0x702);
                    state = 1;
                    if (((S_800BE120_0 *)arg0)->unk_14 & 0x4000) {
                        func_80099844(arg0, D_800E0FF4);
                    }
                }
            }
        }
    }

    state_test = state;
    ASM_KEEP(state_test);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (state_test != 0) {
        goto block_end;
    }
    if ((((S_800BE120_0 *)arg0)->unk_13 < 2) ||
        (((S_800BE120_0 *)arg0)->unk_54 & 0x800000) ||
        (((S_800BE120_0 *)arg0)->unk_48.at01.v != 0)) {
        raw_result = func_800990FC();
        call_arg = arg0;
        ASM_KEEP(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
        pass_result = raw_result;
        ASM_KEEP(pass_result);   /* MATCH pin: keeps a statement from moving across a call/branch */
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
    return 1;

block_end:
    func_80098B38(arg1);
    D_80083460.fieldA = (u16)(D_80083460.fieldA - 1);
    return 1;
}

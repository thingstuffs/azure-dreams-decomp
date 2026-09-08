#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A0[3];
M2C_UNK func_80024FD4();
M2C_UNK func_80025360() __attribute__((noreturn));
M2C_UNK func_80025368() __attribute__((noreturn));
M2C_UNK func_800253B0() __attribute__((noreturn));

typedef struct {
    u8 pad[0x14];
    u16 field14;
} S818B78E8_Child;

typedef struct {
    S818B78E8_Child *child;
    u8 pad04[0xA];
    s16 state;
    s16 field10;
    u16 field12;
    s16 field14;
} S818B78E8_Obj;

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
} S818B78E8_Vec;

typedef struct {
    u8 pad[0xC];
    s8 fieldC;
    s8 fieldD;
    s8 fieldE;
    u8 pad0F[3];
    s16 field12;
    u16 flags;
    u8 pad16[4];
    u16 field1A;
    s16 field1C;
    s16 field1E;
} S818B78E8_State;

void func_818B78E8(S818B78E8_Obj *arg0, S818B78E8_Vec *arg1, S818B78E8_State *arg2) {
    S818B78E8_Obj *base;
    S818B78E8_Vec *vec;
    S818B78E8_State *state;
    s32 temp_s2;
    s16 inc_field10;
    s16 temp_v0;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 tail_v0;
    s16 tail_v1;
    s32 var_v0;
    s32 var_v1;
    s32 tail_cond;
    s32 field_offset;
    s32 field_value;
    s32 temp_a1_s16;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a1;
    s32 vec_x10;
    s32 vec_x14;
    s32 temp_a2;
    s32 temp_v1_2;
    u16 case2_state;
    S818B78E8_Child *temp_v1;

    base = arg0;
    vec = arg1;
    state = arg2;
    temp_v1 = base->child;
    temp_v1->field14 = (u16) (temp_v1->field14 + 1);
    temp_v1_2 = base->field12;
    temp_v1_3 = temp_v1_2 + 1;
    inc_field10 = base->field10 + 1;
    ASM_KEEP_NV(inc_field10);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    base->field10 = (u16) inc_field10;
    base->field12 = (u16) temp_v1_3;
    temp_a1 = temp_v1_3 << 0x10;
    temp_a2 = temp_a1 >> 0x10;
    temp_a2 %= 7;
    temp_s2 = temp_a2 + 1;
    func_800478B8(state, temp_a1 >> 0x1F, temp_a2);
    state->field1A = (u16) (state->field1A + 0x300);
    temp_v1_4 = base->state;
    if (temp_v1_4 == 1) {
        goto state1;
    }
    if (temp_v1_4 < 2) {
        if (temp_v1_4 != 0) {
            func_800253B0();
            return;
        }
        goto state0;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (temp_v1_4 == 2) {
        goto state2;
    }
    if (temp_v1_4 != 3) {
        func_800253B0();
        return;
    }
    goto state3;

state0:
    vec_x10 = vec->x10;
    vec_x14 = vec->x14;
    vec->x0 = (s32) (vec->x0 + vec->xC);
    vec->x4 = (s32) (vec->x4 + vec_x10);
    vec->x8 = (s32) (vec->x8 + vec_x14);
    tail_v0 = (s16) base->field10;
    tail_v1 = base->field14;
    tail_cond = tail_v0 < tail_v1;
    ASM_TAILSLOT_PIN(tail_cond);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80025360();
    return;

state1:
    temp_a1_s16 = (s16) temp_s2;
    var_v1 = temp_a1_s16;
    state->field12 = 0;
    state->flags = (u16) (state->flags & 0xFEFF);
    if (temp_a1_s16 < 0) {
        var_v1 = temp_a1_s16 + 3;
    }
    temp_a0_4 = temp_a1_s16 / 2;
    var_v1 >>= 2;
    var_v1 <<= 7;
    field_offset = ((s16) base->field10 * 8) - 0x80;
    
    var_v1 -= field_offset;
    state->fieldC = (s8) var_v1;
    state->fieldD = (s8) (((s32) (((s16) temp_a0_4 - (((s32) ((s16) temp_a0_4 + ((u32) (temp_a0_4 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) - (s16) (((s16) base->field10 * 8) - 0x80));
    state->fieldE = (s8) (((s32) ((temp_a1_s16 - (temp_a0_4 * 2)) << 0x10) >> 9) - (s16) (((s16) base->field10 * 8) - 0x80));
    field_value = base->field10;
    
    temp_v0 = (0x19 - field_value) << 8;
    state->field1E = temp_v0;
    state->field1C = temp_v0;
    if ((s16) base->field10 >= 0x10) {
        func_80024FD4((void *)base, (void *)vec);
        func_80025368();
        return;
    }
    goto done;

state2:
    temp_a1_s16 = (s16) temp_s2;
    var_v0 = temp_a1_s16;
    if (temp_a1_s16 < 0) {
        var_v0 = temp_a1_s16 + 3;
    }
    temp_a0_2 = temp_a1_s16 / 2;
    state->fieldC = (s8) ((var_v0 >> 2) << 7);
    temp_a0_3 = (s32) ((temp_a1_s16 - (temp_a0_2 * 2)) << 0x10) >> 9;
    state->fieldD = (s8) ((s32) (((s16) temp_a0_2 - (((s32) ((s16) temp_a0_2 + ((u32) (temp_a0_2 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    state->fieldE = (s8) temp_a0_3;
    if ((s16) base->field10 >= 0x20) {
        case2_state = (u16) base->state;
        base->field10 = 0U;
        base->state = (s16) (case2_state + 1);
        func_800253B0();
        return;
    }
    goto done;

state3:
    if (state->flags & 0x6000) {
        *((u16 *)base - 1) = (u16) (*((u16 *)base - 1) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

done:
    ;
}

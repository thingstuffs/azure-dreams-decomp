#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A0[3];
extern void func_800478B8(void *);
M2C_UNK func_80024FD4();

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

void func_800250E8(S818B78E8_Obj *arg0, S818B78E8_Vec *arg1, S818B78E8_State *arg2) {
    s32 temp_s2;
    s16 temp_v0;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 tail_v0;
    s16 tail_v1;
    s32 var_v0;
    s32 var_v1;
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

    temp_v1 = arg0->child;
    temp_v1->field14 = (u16) (temp_v1->field14 + 1);
    temp_v1_2 = arg0->field12;
    temp_v1_3 = temp_v1_2 + 1;
    arg0->field10 = (u16) (arg0->field10 + 1);
    arg0->field12 = (u16) temp_v1_3;
    temp_a1 = temp_v1_3 << 0x10;
    temp_a2 = temp_a1 >> 0x10;
    temp_a2 %= 7;
    temp_s2 = temp_a2 + 1;
    func_800478B8(arg2);
    arg2->field1A = (u16) (arg2->field1A + 0x300);
    temp_v1_4 = arg0->state;
    if (temp_v1_4 == 1) {
        goto state1;
    }
    if (temp_v1_4 < 2) {
        if (temp_v1_4 == 0) {
            goto state0;
        }
        goto done;
    }
    if (temp_v1_4 == 2) {
        goto state2;
    }
    if (temp_v1_4 != 3) {
        goto done;
    }
    goto state3;

state0:
    vec_x10 = arg1->x10;
    vec_x14 = arg1->x14;
    arg1->x0 = (s32) (arg1->x0 + arg1->xC);
    arg1->x4 = (s32) (arg1->x4 + vec_x10);
    arg1->x8 = (s32) (arg1->x8 + vec_x14);
    tail_v0 = (s16) arg0->field10;
    tail_v1 = arg0->field14;
    if (tail_v0 >= tail_v1) {
        case2_state = (u16) arg0->state;
        arg0->field10 = 0U;
        arg0->state = (s16) (case2_state + 1);
    }
    goto done;

state1:
    temp_a1_s16 = (s16) temp_s2;
    var_v1 = temp_a1_s16;
    arg2->field12 = 0;
    arg2->flags = (u16) (arg2->flags & 0xFEFF);
    if (temp_a1_s16 < 0) {
        var_v1 = temp_a1_s16 + 3;
    }
    temp_a0_4 = temp_a1_s16 / 2;
    var_v1 >>= 2;
    var_v1 <<= 7;
    field_offset = ((s16) arg0->field10 * 8) - 0x80;

    var_v1 -= field_offset;
    arg2->fieldC = (s8) var_v1;
    arg2->fieldD = (s8) (((s32) (((s16) temp_a0_4 - (((s32) ((s16) temp_a0_4 + ((u32) (temp_a0_4 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) - (s16) (((s16) arg0->field10 * 8) - 0x80));
    arg2->fieldE = (s8) (((s32) ((temp_a1_s16 - (temp_a0_4 * 2)) << 0x10) >> 9) - (s16) (((s16) arg0->field10 * 8) - 0x80));
    field_value = arg0->field10;

    temp_v0 = (0x19 - field_value) << 8;
    arg2->field1E = temp_v0;
    arg2->field1C = temp_v0;
    if ((s16) arg0->field10 >= 0x10) {
        func_80024FD4((void *)arg0, (void *)arg1);
        case2_state = (u16) arg0->state;
        arg0->field10 = 0U;
        arg0->state = (s16) (case2_state + 1);
    }
    goto done;

state2:
    temp_a1_s16 = (s16) temp_s2;
    var_v0 = temp_a1_s16;
    if (temp_a1_s16 < 0) {
        var_v0 = temp_a1_s16 + 3;
    }
    temp_a0_2 = temp_a1_s16 / 2;
    arg2->fieldC = (s8) ((var_v0 >> 2) << 7);
    temp_a0_3 = (s32) ((temp_a1_s16 - (temp_a0_2 * 2)) << 0x10) >> 9;
    arg2->fieldD = (s8) ((s32) (((s16) temp_a0_2 - (((s32) ((s16) temp_a0_2 + ((u32) (temp_a0_2 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    arg2->fieldE = (s8) temp_a0_3;
    if ((s16) arg0->field10 >= 0x20) {
        case2_state = (u16) arg0->state;
        arg0->field10 = 0U;
        arg0->state = (s16) (case2_state + 1);
    }
    goto done;

state3:
    if (arg2->flags & 0x6000) {
        *((u16 *)arg0 - 1) = (u16) (*((u16 *)arg0 - 1) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

done:
    ;
}

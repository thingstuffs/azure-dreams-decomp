#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    void *field_B8;
    s32 unkBC;
    char padC0[4];
    s32 unkC4;
    char padC8[4];
    s32 unkCC;
    s32 unkD0;
    char padD4[4];
    void *ptr;
    s16 unkDC;
    s16 unkDE;
    s32 unkE0;
} S_8191696C_state;

extern void D_80024024(void);
extern volatile s8 D_800E3D20[];

s32 func_8002416C(s32 unused, s32 arg1, s32 arg2, s16 arg3) {
    struct S_80083178 *state = &D_80083178;
    S_8191696C_state *p = (S_8191696C_state *)&state->field_B8;
    void *next = (void *)((u8 *)&state->field_B8 + 4);
    register s32 saved_arg2 ASM_REG("$9");
    s32 temp_v1;
    s32 var_a1;

    temp_v1 = p->unkC4;
    p->unkC4 = arg1;
    p->unkE0 = 0;
    p->field_B8 = next;
    saved_arg2 = arg2;
    var_a1 = temp_v1 != arg1;
    if (p->unkCC != 9) {
        var_a1 |= 2;
    }
    p->unkCC = 0xC;
    p->unkD0 = 0;
    p->unkDE = arg3;
    state->callback = D_80024024;
    if (var_a1 & 1) {
        D_800E3D20[0] = saved_arg2;
    }
    p->unkDC = arg2;
    return var_a1;
}

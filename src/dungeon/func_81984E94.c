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

extern void D_8002654C(void);
extern volatile s8 D_800E3D20[];


/* Reset shared state to mode 13 and report changes to its key and prior mode. */
s32 func_81984E94(s32 unused, s32 state_key, s32 value, s16 secondary_value) {
    struct S_80083178 *state = &D_80083178;
    S_8191696C_state *substate = (S_8191696C_state *)&state->field_B8;
    void *next_field = (void *)((u8 *)&state->field_B8 + 4);
    register s32 saved_value ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 previous_key;
    s32 change_flags;

    previous_key = substate->unkC4;
    substate->unkC4 = state_key;
    substate->unkE0 = 0;
    substate->field_B8 = next_field;
    saved_value = value;
    change_flags = previous_key != state_key;
    if (substate->unkCC != 9) {
        change_flags |= 2;
    }
    substate->unkCC = 0xD;
    substate->unkD0 = 0;
    substate->unkDE = secondary_value;
    state->callback = D_8002654C;
    if (change_flags & 1) {
        D_800E3D20[0] = saved_value;
    }
    substate->unkDC = value;
    return change_flags;
}

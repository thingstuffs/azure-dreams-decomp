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


/* Initializes a dispatch request and reports changes to its identifier and prior mode. */
s32 func_8002416C(s32 unused, s32 request_id, s32 request_value, s16 request_param) {
    struct S_80083178 *state = &D_80083178;
    S_8191696C_state *dispatch = (S_8191696C_state *)&state->field_B8;
    void *payload_start = (void *)((u8 *)&state->field_B8 + 4);
    s16 saved_value;
    s32 prev_request_id;
    s32 change_flags;

    prev_request_id = dispatch->unkC4;
    dispatch->unkC4 = request_id;
    dispatch->unkE0 = 0;
    dispatch->field_B8 = payload_start;
    saved_value = request_value;
    change_flags = prev_request_id != request_id;
    if (dispatch->unkCC != 9) {
        change_flags |= 2;
    }
    dispatch->unkCC = 0xC;
    dispatch->unkD0 = 0;
    dispatch->unkDE = request_param;
    state->callback = D_80024024;
    if (change_flags & 1) {
        D_800E3D20[0] = saved_value;
    }
    dispatch->unkDC = request_value;
    return change_flags;
}

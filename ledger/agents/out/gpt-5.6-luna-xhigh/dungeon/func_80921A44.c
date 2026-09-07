#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0;
extern void func_800478B8(void *, void *, s32, s32);
/* Advances the state values, scales the two timing fields, and marks the owner when flags are set. */
void func_80921A44(void *owner, void *state, void *result) {
    s32 timing_field_0C;
    s32 timing_field_10;
    s32 updated_state_value;
    s32 saved_state_value_8;

    timing_field_0C = M2C_FIELD(state, s32 *, 0xC);
    timing_field_10 = M2C_FIELD(state, s32 *, 0x10);
    updated_state_value = M2C_FIELD(state, s32 *, 0) + M2C_FIELD(state, volatile s32 *, 0xC);
    saved_state_value_8 = M2C_FIELD(state, volatile s32 *, 8);
    M2C_FIELD(state, volatile s32 *, 0) = updated_state_value;
    M2C_FIELD(state, s32 *, 8) = saved_state_value_8 + 0xFFFE8000;
    M2C_FIELD(state, volatile s32 *, 4) = (s32) (M2C_FIELD(state, s32 *, 4) + M2C_FIELD(state, s32 *, 0x10));
    M2C_FIELD(state, volatile s32 *, 0xC) = (s32) ((timing_field_0C * 4) / 5);
    M2C_FIELD(state, s32 *, 0x10) = (s32) ((timing_field_10 * 4) / 5);
    func_800478B8(result, state, (s32) (timing_field_10 * 4) >> 0x1F, (s32) (timing_field_0C * 4) >> 0x1F);
    if (M2C_FIELD(result, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(owner, u16 *, -2) = (u16) (M2C_FIELD(owner, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

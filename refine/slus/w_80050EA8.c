#include "common.h"

typedef struct {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
} S_80050EA8_sub;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x0C];
    S_80050EA8_sub unk20;
} S_80050EA8;

extern void func_80044A50(S_80050EA8 *a0);
extern void func_8004FE78(void *a0);

/* Transfer a pending value to its slot, run both update helpers, and clear the second helper's input. */
void func_80050EA8(S_80050EA8 *state)
{
    s32 pending_value = state->unk10;
    S_80050EA8_sub *slot = &state->unk20;

    if (pending_value != 0) {
        slot->unk24 = pending_value;
        state->unk10 = 0;
    }
    func_80044A50(state);
    func_8004FE78((void *)slot->unk28);
    slot->unk28 = 0;
}

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

/* Saves the pending value, unlinks the object, and releases and clears its attachment. */
void func_80050EA8(S_80050EA8 *object)
{
    s32 pending_value = object->unk10;
    S_80050EA8_sub *object_state = &object->unk20;

    if (pending_value != 0) {
        object_state->unk24 = pending_value;
        object->unk10 = 0;
    }
    func_80044A50(object);
    func_8004FE78((void *)object_state->unk28);
    object_state->unk28 = 0;
}

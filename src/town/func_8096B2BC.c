#include "common.h"

extern s32 D_80126A88[];
extern u8 D_80129728[];

/* Initialize fourteen entries from the value table and clear their linked counters. */
void func_80123754(void) {
    void **entry_slot;
    s32 *entry;
    s32 initial_value;
    s32 *value_pair;
    s32 entry_index;
    u8 *state_base;

    entry_index = 0;
    state_base = D_80129728;
    entry_slot = (void **)(state_base + 0x38);
    value_pair = D_80126A88;
    do {
        entry = *entry_slot;
        initial_value = *value_pair;
        value_pair += 2;
        *entry = initial_value;
        entry_index += 1;
        *(s16 *)((u8 *)*(void **)((u8 *)*entry_slot + 8) + 2) = 0;
        entry_slot += 1;
    } while (entry_index < 0xE);
}

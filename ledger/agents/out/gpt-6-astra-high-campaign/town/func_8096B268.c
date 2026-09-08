#include "common.h"

extern s32 D_80126A88[];
extern u8 D_80129728[];

/* Initialize 14 entries from alternating source values and set their linked halfwords to 0x800. */
void func_80123700(void) {
    s32 entry_index;
    s32 *source_values;
    void **entry_slot;
    u8 *entry_table;
    s16 initial_value;

    entry_index = 0;
    initial_value = 0x800;
    entry_table = D_80129728;
    entry_slot = (void **)(entry_table + 0x38);
    source_values = D_80126A88;
    do {
        *(s32 *)*entry_slot = *source_values;
        source_values += 2;
        entry_index++;
        *((s16 *)*(void **)((u8 *)*entry_slot + 8) + 1) = initial_value;
        entry_slot++;
    } while (entry_index < 14);
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_80123700_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123700_0;   /* *var_a0 in func_80123700 */

typedef struct S_80123700_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80123700_1;   /* ((S_80123700_0 *)(*var_a0))->unk_08 in func_80123700 */




extern s32 D_80126A88;
extern M2C_UNK D_80129728;


/* Initialize 14 entries from the value table and set each linked field to 0x800. */
void func_80123700(void) {
    s8 *entry_table;
    s8 *source_record;
    s32 source_value;
    s32 *entry_value;
    s32 entry_index;
    s32 initial_value;
    void **entry_slot;

    entry_index = 0;
    initial_value = 0x800;
    entry_table = (s8 *)&D_80129728;
    entry_slot = (void **)(entry_table + 0x38);
    source_record = (s8 *)&D_80126A88;
    do {
        entry_value = *(s32 **)entry_slot;
        source_value = *(s32 *)source_record;
        source_record += 8;
        *entry_value = source_value;
        entry_index += 1;
        ((S_80123700_1 *)(((S_80123700_0 *)(*entry_slot))->unk_08))->unk_02 = initial_value;
        entry_slot = (void **)((s8 *)((void **)((s8 *)entry_slot + 4)));
    } while (entry_index < 0xE);
}

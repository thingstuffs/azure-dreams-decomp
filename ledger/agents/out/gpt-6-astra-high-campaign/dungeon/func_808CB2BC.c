#include "common.h"
#include "m2c_compat.h"

typedef struct S_80123754_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123754_0;   /* *var_a0 in func_80123754 */

typedef struct S_80123754_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80123754_1;   /* ((S_80123754_0 *)(*var_a0))->unk_08 in func_80123754 */

extern s32 D_80126A88;
extern M2C_UNK D_80129728;

/* Copy 14 initial values into the referenced records and clear their linked counters. */
void func_80123754(void) {
    s8 *initial_values;
    s32 initial_value;
    s32 *record_value;
    s32 record_index;
    s8 *table_base;
    void **record_slot;

    record_index = 0;
    table_base = (s8 *)&D_80129728;
    record_slot = (void **)(table_base + 0x38);
    initial_values = (s8 *)&D_80126A88;
    do {
        record_value = *(s32 **)record_slot;
        initial_value = *(s32 *)initial_values;
        initial_values += 8;
        *record_value = initial_value;
        record_index += 1;
        ((S_80123754_1 *)(((S_80123754_0 *)(*record_slot))->unk_08))->unk_02 = 0;
        record_slot = (void **)((s8 *)((void **)((s8 *)record_slot + 4)));
    } while (record_index < 0xE);
}

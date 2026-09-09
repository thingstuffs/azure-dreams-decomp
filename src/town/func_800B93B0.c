#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_2;   /* temp_a0 in func_800B6B10 */

typedef struct S_800B6B10_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_3;   /* *var_s0 in func_800B6B10 */

typedef struct S_800B6B10_4 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_800B6B10_4;   /* ((S_800B6B10_2 *)temp_a0)->unk_04 in func_800B6B10 */

typedef struct S_800B6B10_5 {
    u8 pad_00[0xE];
    s8 unk_0E;
} S_800B6B10_5;   /* ((S_800B6B10_3 *)(*var_s0))->unk_04 in func_800B6B10 */

M2C_UNK func_8004B1A4();
M2C_UNK func_8004E99C();

typedef struct S_800B6B10_0 {
    s32 unk_00;
} S_800B6B10_0;   /* temp_a0 in func_800B6B10 */

typedef struct S_800B6B10_1 {
    s32 unk_00;
} S_800B6B10_1;   /* *var_s0 in func_800B6B10 */

/* Processes 24 entries by type and clears the handle and type of handled entries. */
void func_800B6B10(void **entries) {
    s32 entry_index;
    s32 type_two;
    u8 entry_type;
    void **entry_slot;
    S_800B6B10_0 *entry;

    entry_index = 0;
    type_two = 2;
    entry_slot = entries;
process_entry:
    entry = *entry_slot;
    entry_type = ((S_800B6B10_4 *)(((S_800B6B10_2 *)entry)->unk_04))->unk_0E;
    if (entry_type == type_two) {
        func_8004E99C(entry->unk_00);
    } else if (entry_type == 1) {
        func_8004B1A4(entry->unk_00);
    } else {
        goto next_entry;
    }
    ((S_800B6B10_1 *)(*entry_slot))->unk_00 = 0;
    ((S_800B6B10_5 *)(((S_800B6B10_3 *)(*entry_slot))->unk_04))->unk_0E = 0;
next_entry:
    entry_index += 1;
    entry_slot = (void **)((s8 *)((void **)((s8 *)entry_slot + 4)));
    if (entry_index >= 0x18) {
        return;
    }
    goto process_entry;
}

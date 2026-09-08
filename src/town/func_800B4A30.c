#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B2164();                 /* extern */

typedef struct S_800B2190_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2190_0;   /* temp_a0 in func_800B2190 */

typedef struct S_800B2190_1 {
    s32 unk_00;
} S_800B2190_1;   /* *var_s0 in func_800B2190 */

typedef struct S_800B2190_2 {
    void * unk_00;
    void * unk_04;
} S_800B2190_2;   /* var_s0 in func_800B2190 */

/* Clear the selected entry and remove its pointer from the null-terminated list. */
void func_800B2190(s32 list_addr, s32 index) {
    s32 slot_offset;
    void **slot;
    S_800B2190_0 *entry;

    slot_offset = index * 4;
    slot = list_addr + slot_offset;
    entry = *slot;
    if (entry->unk_01 == 0x13) {
        func_800B2164(entry, slot_offset);
    }
    ((S_800B2190_1 *)(*slot))->unk_00 = 0;
    if (*slot != NULL) {
        do {
            ((S_800B2190_2 *)slot)->unk_00 = ((S_800B2190_2 *)slot)->unk_04;
            slot = (void **)((s8 *)((void **)((s8 *)slot + 4)));
        } while (*slot != NULL);
    }
}

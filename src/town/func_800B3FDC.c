#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B173C_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xB8];
    s32 unk_CC;
} S_800B173C_0;   /* arg0 in func_800B173C */

typedef struct S_800B173C_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800B173C_1;   /* *var_v0 in func_800B173C */

/* Set the decrease or increase indicator color when the current and target values differ. */
void func_800B173C(S_800B173C_0 *record, s32 target_value) {
    s32 indicators_address;
    s32 current_value;
    void **indicator_entry;

    current_value = record->unk_10;
    if (current_value != target_value) {
        indicators_address = record->unk_CC;
        if (current_value >= target_value) {
            indicator_entry = indicators_address + 0x74;
        } else {
            indicator_entry = indicators_address + 0x78;
        }
        *((S_800B173C_1 *)(*indicator_entry))->unk_04 = 0xE0E0E0;
    }
}

#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009D7D0();                         /* extern */

typedef struct S_8009D73C_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_8009D73C_0;   /* *var_s1 in func_8009D73C */

/* Process each zero-terminated value list in the null-terminated entry array. */
void func_8009D73C(void **entries) {
    s32 *value_ptr;
    s32 value;
    void **entry_ptr;

    entry_ptr = entries;
    if (*entry_ptr != NULL) {
        do {
            value_ptr = ((S_8009D73C_0 *)(*entry_ptr))->unk_0C;
            if ((value_ptr != NULL) && (*value_ptr != 0)) {
                do {
                    value = *value_ptr;
                    value_ptr += 1;
                    func_8009D7D0(value);
                } while (*value_ptr != 0);
            }
            entry_ptr = (void **)((s8 *)((void **)((s8 *)entry_ptr + 4)));
        } while (*entry_ptr != NULL);
    }
}

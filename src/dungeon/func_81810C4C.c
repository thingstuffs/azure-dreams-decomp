#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025C4C_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_80025C4C_0;   /* arg0 in func_80025C4C */

/* Clears the value referenced by the entry. */
void func_80025C4C(S_80025C4C_0 *entry) {
    *entry->unk_04 = 0;
}

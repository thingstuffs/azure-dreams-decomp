#include "common.h"
#include "m2c_compat.h"

typedef struct S_80098CEC_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80098CEC_0;   /* arg0 in func_80098CEC */

/* Returns the masked 0x20 flag from the entry. */
s32 func_80098CEC(S_80098CEC_0 *entry) {
    return entry->unk_03 & 0x20;
}

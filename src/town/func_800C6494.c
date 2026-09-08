#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C3BF4_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C3BF4_0;   /* arg2 in func_800C3BF4 */


M2C_UNK func_800C4174(M2C_UNK, M2C_UNK, S_800C3BF4_0 *);
/* Calls the handler when either monitored status flag is set. */
void func_800C3BF4(M2C_UNK handler_arg, M2C_UNK context, S_800C3BF4_0 *status) {
    if (status->unk_14 & 0x6000) {
        func_800C4174(handler_arg, context, status);
    }
}

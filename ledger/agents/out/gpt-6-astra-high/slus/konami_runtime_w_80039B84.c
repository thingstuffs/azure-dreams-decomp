#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039B84_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80039B84_0;   /* arg0 in func_80039B84 */


extern M2C_UNK func_80038A08;

/* Set the event-script context's callback to func_80038A08. */
void func_80039B84(S_80039B84_0 *script) {
    script->unk_10 = &func_80038A08;
}

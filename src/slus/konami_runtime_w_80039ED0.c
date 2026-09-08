#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039ED0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80039ED0_0;   /* arg0 in func_80039ED0 */


/* Event-script handler 48: clear the script context field at offset 0x10. */
void func_80039ED0(S_80039ED0_0 *script) {
    script->unk_10 = 0;
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_80039ED0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80039ED0_0;   /* arg0 in script_yield */


/* Opcode 0x30: Yield until the next frame. */
void script_yield(S_80039ED0_0 *script) {
    script->unk_10 = 0;
}

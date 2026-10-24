#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_80039208_0 {
    u8 pad_00[0x2E];
    s8 unk_2E;
} S_80039208_0;   /* arg0 in script_instant_text */


/* Opcode 0x0B: Instant-text mode (+0x2E = 2). */
void script_instant_text(S_80039208_0 *script_ctx) {
    script_ctx->unk_2E = 2;
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039208_0 {
    u8 pad_00[0x2E];
    s8 unk_2E;
} S_80039208_0;   /* arg0 in func_80039208 */


/* Event-script handler that sets the context byte at offset 0x2E to 2. */
void func_80039208(S_80039208_0 *script_ctx) {
    script_ctx->unk_2E = 2;
}

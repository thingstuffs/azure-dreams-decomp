#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039568_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80039568_0;   /* arg0 in func_80039568 */


extern M2C_UNK func_80038464;

/* Sets the event-script context's handler to func_80038464. */
void func_80039568(S_80039568_0 *script_ctx) {
    script_ctx->unk_10 = &func_80038464;
}

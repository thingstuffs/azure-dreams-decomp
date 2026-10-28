#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script.h"
#include "slus/data.h"
#include "engine/message/state.h"

typedef struct S_80039568_0 {
    u8 pad_00[0x10];
    void (*unk_10)(struct S_80038464_0 *);
} S_80039568_0;   /* arg0 in script_wait_button */

/* Opcode 0x11: Wait for a button press. */
void script_wait_button(S_80039568_0 *script_ctx) {
    script_ctx->unk_10 = &clear_runtime_state_and_set_handler;
}

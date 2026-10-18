#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039568_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_80039568_0;   /* arg0 in vm_op_17_install_action */


extern M2C_UNK clear_runtime_state_and_set_handler;

/* Sets the event-script context's handler to clear_runtime_state_and_set_handler. */
void vm_op_17_install_action(S_80039568_0 *script_ctx) {
    script_ctx->unk_10 = &clear_runtime_state_and_set_handler;
}

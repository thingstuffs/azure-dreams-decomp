#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039568_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80039568_0;   /* arg0 in vmOp17InstallAction */


extern M2C_UNK slusClearRuntimeStateAndSetHandler;

/* Sets the event-script context's handler to slusClearRuntimeStateAndSetHandler. */
void vmOp17InstallAction(S_80039568_0 *script_ctx) {
    script_ctx->unk_10 = &slusClearRuntimeStateAndSetHandler;
}

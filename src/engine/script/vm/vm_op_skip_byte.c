#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "shared/runtime_dispatch.h"
#include "engine/script/vm.h"

   /* Increments the event-script context's counter at offset 0x1C. */
void vm_op_56_skip_byte(ScriptCounterView *script_ctx) {
    script_ctx->unk_1C = (s32) (script_ctx->unk_1C + 1);
}

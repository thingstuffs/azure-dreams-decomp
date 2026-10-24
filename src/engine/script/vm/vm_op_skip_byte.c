#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "shared/runtime_dispatch.h"
#include "engine/script/vm.h"

/* Opcode 0x38: Skip one operand byte. */
void script_skip_byte(ScriptCounterView *script_ctx) {
    script_ctx->unk_1C = (s32) (script_ctx->unk_1C + 1);
}

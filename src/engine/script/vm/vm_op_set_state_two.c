#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_80039208_0 {
    u8 pad_00[0x2E];
    s8 unk_2E;
} S_80039208_0;   /* arg0 in vm_op_11_set_state_two */


/* Event-script handler that sets the context byte at offset 0x2E to 2. */
void vm_op_11_set_state_two(S_80039208_0 *script_ctx) {
    script_ctx->unk_2E = 2;
}

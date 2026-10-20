#include "common.h"

#include "common.h"

typedef struct S_80039ACC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039ACC_0;   /* arg0 in vm_op_87_install_terminator_action */


void noop_script_terminator_action();

/* Set the event-script continuation and decrement its counter. */
void vm_op_87_install_terminator_action(S_80039ACC_0 *script) {
    script->unk_10 = &noop_script_terminator_action;
    script->unk_1C = (s32) (script->unk_1C - 1);
}

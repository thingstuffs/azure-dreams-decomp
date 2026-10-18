#include "common.h"

#include "common.h"

typedef struct S_80039B84_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_80039B84_0;   /* arg0 in vm_op_35_install_action */


extern s32 func_80038A08;

/* Set the event-script context's callback to func_80038A08. */
void vm_op_35_install_action(S_80039B84_0 *script) {
    script->unk_10 = &func_80038A08;
}

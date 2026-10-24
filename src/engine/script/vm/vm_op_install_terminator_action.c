#include "common.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_80039ACC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039ACC_0;   /* arg0 in script_page_break */

/* Opcode 0x57: Page break: wait for a button; the next byte is then read as the wait mode. */
void script_page_break(S_80039ACC_0 *script) {
    script->unk_10 = &noop_script_terminator_action;
    script->unk_1C = (s32) (script->unk_1C - 1);
}

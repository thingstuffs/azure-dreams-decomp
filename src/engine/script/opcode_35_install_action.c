#include "common.h"

#include "common.h"
#include "engine/script.h"
#include "slus/data.h"

typedef struct S_80039B84_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_80039B84_0;   /* arg0 in script_park */

/* Opcode 0x23: Park the script (installs an idle action). */
void script_park(S_80039B84_0 *script) {
    script->unk_10 = &noop_installed_script_action;
}

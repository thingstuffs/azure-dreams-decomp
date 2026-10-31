#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_80039640_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5C];
    void * unk_7C;
} S_80039640_0;   /* arg0 in script_return */

typedef struct S_80039640_1 {
    s32 unk_00;
} S_80039640_1;   /* temp_v1 in script_return; pointer addresses record offset 0x4 */


/* Opcode 0x16: Return from a script subroutine (also pops inserted text strings at a 0x00 byte). */
void script_return(S_80039640_0 *state) {
    void *cursor;

    cursor = state->unk_7C;
    state->unk_7C = (cursor - 4);
    state->unk_1C = (s32) ((S_80039640_1 *)((u8 *)cursor - 0x4))->unk_00;
}

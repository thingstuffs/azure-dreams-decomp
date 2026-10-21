#include "common.h"
#include "engine/script.h"
#include "engine/script/vm.h"
#include "slus.h"

typedef struct S_800390D0_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_800390D0_0;   /* arg0 in handle_vm_opcode_01 */

extern u8 runtime_dispatch_mode_alias[];

/* Selects the next callback or clears it and decrements the state counter. */
void handle_vm_opcode_01(S_800390D0_0 *state) {
    if (runtime_dispatch_mode_alias[0] != 2) {
        if (read_sound_mode_blocking_status(4) != 0x100) {
            SD_Call(0xC4);
        } else {
            state->unk_10 = 0;
            state->unk_1C = (s32) (state->unk_1C - 1);
            return;
        }
    }
    state->unk_10 = &noop_runtime_record_idle;
}

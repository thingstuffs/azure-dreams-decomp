#include "common.h"
#include "engine/script.h"
#include "engine/script/vm.h"
#include "slus.h"

typedef struct S_800390D0_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
    u8 pad_14[0x8];
    s32 unk_1C;
} S_800390D0_0;   /* arg0 in script_end_message */

extern u8 runtime_dispatch_mode_alias[];

/* Opcode 0x01: End of message: unless dispatch mode is 2, rewind while the sound status is 0x100, then send SD_Call(0xC4); park the window. */
void script_end_message(S_800390D0_0 *state) {
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

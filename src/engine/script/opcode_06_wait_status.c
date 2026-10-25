#include "common.h"

#include "common.h"
#include "engine/message.h"
#include "engine/script.h"
#include "slus.h"

typedef struct S_80039A08_0 {
    u8 pad_00[0x10];
    void (*unk_10)(struct S_800389B4_0 *);
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039A08_0;   /* arg0 in script_wait_voice_then_advance */


s32 check_state_or_global_flags();                          /* extern */

/* Opcode 0x06: Voice wait: when gated, rewind while the sound status is nonzero; otherwise hand over to advance_message_when_voice_idle once the status is 0x100, else send SD_Call(0xB4). */
void script_wait_voice_then_advance(S_80039A08_0 *state) {
    s32 status;

    status = read_sound_mode_blocking_status(4);
    if (check_state_or_global_flags(state) != 0) {
        if (status != 0) {
            state->unk_10 = 0;
            state->unk_1C = (s32) (state->unk_1C - 1);
        }
    } else {
        if (status == 0x100) {
            state->unk_10 = &advance_message_when_voice_idle;
            return;
        }
        SD_Call(0xB4);
    }
}

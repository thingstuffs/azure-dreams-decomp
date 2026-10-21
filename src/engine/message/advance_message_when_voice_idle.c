#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "slus.h"
#include "slus/data.h"

typedef struct S_800389B4_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800389B4_0;   /* arg0 in advance_message_when_voice_idle */

/* Triggers action 0xB4 and selects update_message_window when the status is not 0x100. */
void advance_message_when_voice_idle(S_800389B4_0 *context) {
    if (read_sound_mode_blocking_status(4) != 0x100) {
        SD_Call(0xB4);
        context->unk_10 = &update_message_window;
    }
}

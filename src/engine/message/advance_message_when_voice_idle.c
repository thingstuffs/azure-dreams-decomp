#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800389B4_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800389B4_0;   /* arg0 in advance_message_when_voice_idle */
short SD_Call(int flags);                     /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK update_message_window;

/* Triggers action 0xB4 and selects update_message_window when the status is not 0x100. */
void advance_message_when_voice_idle(S_800389B4_0 *context) {
    if (func_80053EF0(4) != 0x100) {
        SD_Call(0xB4);
        context->unk_10 = &update_message_window;
    }
}

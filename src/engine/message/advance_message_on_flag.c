#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038478_0 {
    u8 pad_00[0x84];
    s8 unk_84;
} S_80038478_0;   /* arg0 in advance_message_on_flag */


typedef struct Rec_func_800384A8_arg0 Rec_func_800384A8_arg0;
void wait_message_voice_busy(Rec_func_800384A8_arg0 *state);                            /* extern */

/* Call wait_message_voice_busy when the object's flag is set. */
void advance_message_on_flag(S_80038478_0 *object) {
    if (object->unk_84 != 0) {
        wait_message_voice_busy((Rec_func_800384A8_arg0 *)object);
    }
}

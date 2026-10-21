#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "slus.h"

typedef struct S_80038588_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x70];
    s8 unk_84;
} S_80038588_0;   /* arg0 in advance_message_on_confirm_flag */
extern M2C_UNK update_message_window;

/* Call SD_Call and update the object's handler when its flag is set. */
void advance_message_on_confirm_flag(S_80038588_0 *object) {
    if (object->unk_84 != 0) {
        SD_Call(0xB4);
        object->unk_10 = &update_message_window;
    }
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800385E8_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x70];
    s8 unk_84;
} S_800385E8_0;   /* arg0 in advance_message_on_input_flag */
short SD_Call(int flags);                     /* extern */
extern M2C_UNK update_message_window;

/* When the object's flag is set, call SD_Call and update its handler. */
void advance_message_on_input_flag(S_800385E8_0 *object) {
    if (object->unk_84 != 0) {
        SD_Call(0xB4);
        object->unk_10 = &update_message_window;
    }
}

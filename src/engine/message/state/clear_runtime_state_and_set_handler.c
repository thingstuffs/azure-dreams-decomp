#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038464_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x70];
    s8 unk_84;
} S_80038464_0;   /* arg0 in clear_runtime_state_and_set_handler */


extern M2C_UNK advance_message_on_flag;

/* Clear the object's state byte and set its handler to advance_message_on_flag. */
void clear_runtime_state_and_set_handler(S_80038464_0 *object) {
    object->unk_84 = 0;
    object->unk_10 = &advance_message_on_flag;
}

#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C5620_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C5620_0;   /* arg0 in apply_setup_on_timeout_variant_1 */


void apply_object_setup_and_update(S_800C5620_0 *, M2C_UNK, M2C_UNK);
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero or becomes negative. */
void apply_setup_on_timeout_variant_1(S_800C5620_0 *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}

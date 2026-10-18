#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800CE08C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CE08C_0;   /* arg0 in apply_setup_on_timeout_variant_4 */


void apply_object_setup_and_update(S_800CE08C_0 *, M2C_UNK, M2C_UNK);
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero. */
void apply_setup_on_timeout_variant_4(S_800CE08C_0 *object, M2C_UNK context, M2C_UNK update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C - 1;
    object->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        apply_object_setup_and_update(object, context, update_data);
    }
}

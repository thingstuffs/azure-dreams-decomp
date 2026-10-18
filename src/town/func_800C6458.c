#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C3BB8_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C3BB8_0;   /* arg0 in decrement_object_timer_and_call_handler */


void install_object_handler_and_clear_slot_flag(S_800C3BB8_0 *);
/* Decrements the timer and calls the handler when its signed value is nonpositive. */
void decrement_object_timer_and_call_handler(S_800C3BB8_0 *object) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C - 1;
    object->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        install_object_handler_and_clear_slot_flag(object);
    }
}

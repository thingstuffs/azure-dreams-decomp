/* Advance town actor countdowns and invoke their completion handlers. */

#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C3B7C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C3B7C_0;   /* arg0 in decrement_object_timer_and_update */


void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero or becomes negative. */
void decrement_object_timer_and_update(S_800C3B7C_0 *object, s32 callback_arg_1, s32 callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}
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

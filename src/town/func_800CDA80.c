#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800CB1E0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CB1E0_0;   /* arg0 in advance_entity_countdown */
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero. */
void advance_entity_countdown(S_800CB1E0_0 *object, s32 context, s32 update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C - 1;
    object->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        apply_object_setup_and_update(object, context, update_data);
    }
}

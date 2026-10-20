#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C9F1C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C9F1C_0;   /* arg0 in decrement_reaction_timer_and_update */
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the object countdown and call apply_object_setup_and_update when it expires. */
void decrement_reaction_timer_and_update(S_800C9F1C_0 *object, s32 param_1, s32 param_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, param_1, param_2);
    }
}

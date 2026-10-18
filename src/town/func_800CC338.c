#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C9A98_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C9A98_0;   /* arg0 in decrement_reaction_timer_and_reinitialize */


void initialize_reaction_movement(S_800C9A98_0 *, void *, s32);
/* Decrement the object countdown and call initialize_reaction_movement when it expires. */
void decrement_reaction_timer_and_reinitialize(S_800C9A98_0 *object, void *context, s32 param) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_reaction_movement(object, context, param);
    }
}

#include "common.h"
#include "m2c_compat.h"

/* extern */
void initialize_scene_action_record();    /* extern */

typedef struct S_80090F00_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80090F00_0;   /* arg0 in update_countdown_and_fallback */


void dispatch_actor_interaction_actions(S_80090F00_0 *, s32, s32);
/* Updates the object and decrements its countdown if its state is unchanged. */
void update_countdown_and_fallback(S_80090F00_0 *object, s32 context, s32 data) {
    s32 previous_state;
    u16 countdown;

    previous_state = object->unk_00;
    dispatch_actor_interaction_actions(object, context, data);
    if (previous_state == object->unk_00) {
        countdown = object->unk_0A - 1;
        object->unk_0A = countdown;
        if ((countdown << 0x10) <= 0) {
            initialize_scene_action_record(object, context, data);
        }
    }
}

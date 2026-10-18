#include "common.h"
#include "shared/game_work.h"


extern void initialize_scene_action_record(void *, void *, s32);
extern void func_80093E98(void *, void *, s32);


   /* state in update_and_fallback_on_input */

typedef struct S_80091114_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80091114_1;   /* arg1 in update_and_fallback_on_input */


extern void update_actor_ground_and_input(s32 *, S_80091114_1 *, s32);
/* Updates the value and dispatches follow-up handling if it remains unchanged. */
void update_and_fallback_on_input(s32 *value, S_80091114_1 *context, s32 update_arg) {
    s32 saved_update_arg ;   /* Required for the retail saved-register set and frame layout. */
    s32 previous_value;
    GameWork *state = &g_game_work;

    previous_value = *value;
    update_actor_ground_and_input(value, context, update_arg);

    if (previous_value == *value) {
        saved_update_arg = update_arg;
        if (!(state->buttons & 0x20)) {
            initialize_scene_action_record(value, context, saved_update_arg);
            return;
        }

        if ((context->unk_0C == 0) &&
            (context->unk_10 == 0)) {
            func_80093E98(value, context, saved_update_arg);
        }
    }
}

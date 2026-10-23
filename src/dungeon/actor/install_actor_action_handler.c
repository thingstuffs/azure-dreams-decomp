#include "common.h"
#include "dungeon/actor.h"
/* extern */
                /* extern */
extern u8 D_800D4494;

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
} S_800D45D0_0;   /* arg0 in install_actor_action_handler */


s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object);
/* Select D_800D4494 after the countdown completes and the actor check succeeds. */
void install_actor_action_handler(S_800D45D0_0 *state, s32 transform, s32 entity, s32 actor) {
    if ((update_linked_actor_motion(state, transform, entity, actor) != 0) && ((check_actor_floor_trap(entity, actor) << 0x10) > 0)) {
        state->unk_8C = &D_800D4494;
    }
}

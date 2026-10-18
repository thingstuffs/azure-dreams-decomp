#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 check_actor_floor_trap();                /* extern */
extern u8 D_800D4494;

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D45D0_0;   /* arg0 in install_actor_action_handler */


s32 update_linked_actor_motion(S_800D45D0_0 *, M2C_UNK, M2C_UNK, M2C_UNK);
/* Select D_800D4494 after the countdown completes and the actor check succeeds. */
void install_actor_action_handler(S_800D45D0_0 *state, M2C_UNK transform, M2C_UNK entity, M2C_UNK actor) {
    if ((update_linked_actor_motion(state, transform, entity, actor) != 0) && ((check_actor_floor_trap(entity, actor) << 0x10) > 0)) {
        state->unk_8C = &D_800D4494;
    }
}

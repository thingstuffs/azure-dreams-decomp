#include "common.h"
#include "dungeon/actor/state.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008D024_arg0.h"

/* Set unk_9A to 0x29 and clear unk_9B and unk_8C. */
void initialize_action_state_29(void *state, s32 unused_context, struct SpriteFrameState *unused_sprite, struct ActorRecord *unused_actor) {
    Rec_func_8008D024_arg0 *record;

    record = state;
    record->unk_9A = 0x29;
    record->unk_9B.as_s8 = 0;
    record->unk_8C = 0;
}

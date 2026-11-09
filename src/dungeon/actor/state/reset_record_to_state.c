#include "common.h"
#include "dungeon/actor/state.h"
#include "m2c_compat.h"


/* Reset the record to state 0x34 with flag bit 0 cleared. */
void reset_record_to_state_34(ActorRecord *state, void *unused_context, struct SpriteFrameState *unused_sprite, struct ActorRecord *unused_actor) {
    ActorRecord *record;

    record = state;
    record->action_id = 0x34;
    record->action_phase = 0;
    record->unk_8C.word = 0;
    record->unk_A0.parts.high = record->unk_A0.parts.high & 0xFFFE;
}

#include "common.h"
#include "slus.h"
#include "dungeon/system/random.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/actor.h"

struct Dst;
struct Elem;

extern u8 actor_alternate_frames[];

/* Resets the actor action state, sometimes clears flags 0x620, and selects the alternate animation for
   its facing. */
void run_saved_actor_action(ActorRecord *object_arg, void *unused, SpriteFrameState *animation, ActorRecord *actor) {
        ActorRecord *object = object_arg;
        /* MATCH: retain retail's a0 table base after the explicit argument call. */
    u8 *table;
        /* MATCH: save a2 then a3 before loading the state-byte constant. */
    SpriteFrameState *saved2 = animation;
    ActorRecord *saved = actor;
    object->action_id = 0x39;
    object->action_phase = 0;
    object->unk_8C.word = 0;
    if (!(generate_random_value() & 3)) {
        saved->flags1C = (s32) (saved->flags1C & ~0x620);
    }
    table = actor_alternate_frames;
    saved2->frameTable = table;
    select_record_entry_and_value(saved2, (*(void **)(table + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + saved->facing
        + 0x100) >> 7) & 0x1C))), 0);
}

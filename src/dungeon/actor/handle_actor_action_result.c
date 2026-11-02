#include "common.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"


/*
 * Advances removal fading and decrements the bounded counter on completion; otherwise clears the
 * halfword at offset 0x12.
 */
void handle_actor_action_result(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *context) {
    if (fade_actor_to_removal(actor, position, sprite, context) != 0) {
        decrement_bounded_counter();
        return;
    }

    sprite->clut = 0;
}

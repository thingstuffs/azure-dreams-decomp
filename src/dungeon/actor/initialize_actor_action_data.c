#include "common.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"



/*
 * Advances removal fading and decrements the bounded counter on completion; otherwise sets the CLUT
 * to 0x7E40 and enables sprite flag 0x100.
 */
void initialize_actor_action_data(void *first_ptr, void *second_ptr, SpriteFrameState *sprite, void *entity) {
    if (fade_actor_to_removal(first_ptr, second_ptr, sprite, entity) != 0) {
        decrement_bounded_counter();
        return;
    }

    sprite->clut = 0x7E40;
    sprite->flags |= 0x100;
}

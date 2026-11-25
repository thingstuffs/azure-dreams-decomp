#include "shared/record_ptrs.h"
#include "town/scene/score_sprite_data.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "shared/actor_status_flags.h"

/* Slot availability and the fainted state choose different marker graphics. */
static SpritePartCommand *cached_familiar_slot_markers[3][3] = {
    {0, &cached_available_slot_markers[0], &((SpritePartCommand *)score_sprite_initial_value)[0]},
    {0, &cached_available_slot_markers[1], &((SpritePartCommand *)score_sprite_initial_value)[1]},
    {0, 0, 0},
};

s32 get_familiar_menu_state_mask(void)
{
    PlayerRecord *player = (PlayerRecord *)dungeon_actor_ring_anchor;
    s32 mask = player->familiar_slot_state[0] != 0;

    if (player->familiar_slot_state[1] != 0) {
        mask |= 2;
    }
    return mask;
}

SpritePartCommand *get_familiar_slot_marker(s32 slot)
{
    return cached_familiar_slot_markers[slot][((PlayerRecord *)dungeon_actor_ring_anchor)->familiar_slot_state[slot]];
}

SpritePartCommand *get_assigned_familiar_marker(s32 slot)
{
    s32 state = 0;

    if (slot != 2) {
        ActorRecord *actor = get_cached_player_familiar(slot);

        if (actor->flags1C & ACTOR_PLAYER_AWARE) {
            state = 1;
        } else {
            state = 2;
        }
    }
    return cached_familiar_slot_markers[slot][state];
}

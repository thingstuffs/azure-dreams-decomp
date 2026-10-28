#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"


typedef struct S_80D95000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80D95000_2;

typedef struct S_80D95000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80D95000_4;

s32 generate_random_value(void);
extern u8 dreamin_object_callback[];
extern s32 dreamin_slot_f_action_callback;
extern s32 D_8016D86C;

void *damp_and_fade_effect_sprite(s16 init_flags, s16 x, s16 y, s16 initial_value) ;
/* Allocates an object and initializes its state, placement, and mode. */
/* Creates Dreamin with default frames at D_8016D86C, applies spawn flags, and attempts valid tile
 * placement. */
void *damp_and_fade_effect_sprite(s16 init_flags, s16 x, s16 y, s16 initial_value) {
    s32 unused_slot;
    s32 mode;
    SpriteFrameState *placement;
    ObjectPosition *object_data;
    ObjectNodeHeader *object;
    S_80D95000_4 *extended_state;
    ActorRecord *state = 0;
    void *body;
    s8 saved_x;
    s8 saved_y;
    s16 saved_value;
    s32 state_flags;
    s32 pending_flags;

    saved_x = x;
    saved_value = initial_value;
    saved_y = y;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        body = object + 1;
        state = body;
        object->update_callback = &dreamin_object_callback;
        state->species = MONSTER_DREAMIN;
        register_node(object, project_sprite_chain);
        object_data = object->position;
        object_data->z.w.i = saved_value;
        placement = object->sprite;
        mode = init_flags & 3;
        placement->tile_y = saved_y;
        extended_state = body;
        placement->frameTable = &D_8016D86C;
        placement->tile_x = saved_x;
        if (mode == 1) {
            state_flags = state->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            pending_flags = state->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            state->flags14 = state_flags;
            state->flags1C = pending_flags;
        } else if (mode >= 2) {
            state_flags = state->flags14 | ACTOR_CLASS_ENABLED;
            pending_flags = state->flags1C | ACTOR_PLAYER_SIDE;
            state->flags14 = state_flags;
            state->flags1C = pending_flags;
        } else {
            if (((init_flags & ~3) << 0x10) == 0) {
                if (!(state->flags14 & ACTOR_RESIST_SLEEP)) {
                    if (generate_random_value() & 1) {
                        state->flags1C = (s32) (state->flags1C | ACTOR_ASLEEP);
                        set_or_clear_actor_status_slot(state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, object_data, placement, init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &dreamin_slot_f_action_callback;
        try_move_actor_to_valid_position(extended_state, object_data, placement, state);
    }
    return state;
}

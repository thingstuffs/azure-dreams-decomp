#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

#include "shared/entity.h"

typedef struct R03_80170A28_S_80170A28_2 R03_80170A28_S_80170A28_2;
typedef struct ActorActionView ActorActionView;
typedef struct ActorSpriteView ActorSpriteView;

typedef struct S_80DAD000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DAD000_1;

typedef struct S_80DAD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DAD000_2;

typedef struct S_80DAD000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DAD000_4;

void *allocate_list_node();
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */ /* extern */
s16 set_or_clear_actor_status_slot(); /* extern */
s32 generate_random_value();
void initialize_actor_sprite_and_animation(); /* extern */
s32 try_move_actor_to_valid_position(); /* extern */
void func_80152A3C(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part);
void func_80152E68(ActorActionView *action, void *context, ActorSpriteView *sprite, ActorRecord *entity);
extern M2C_UNK D_8015586C;

void *spawn_dreamin_slot_b(s16 spawn_flags, s16 spawn_x, s16 spawn_y, s16 initial_value) ;
/* Allocates and initializes a dungeon object with the requested flags and placement. */
/* Creates Dreamin with default frames at D_8015586C, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_dreamin_slot_b(s16 spawn_flags, s16 spawn_x, s16 spawn_y, s16 initial_value) {
    s32 unused_slot;
    s32 spawn_mode;
    SpriteFrameState *placement;
    ObjectPosition *base_data;
    ObjectNodeHeader *object;
    S_80DAD000_4 *extended_state;
    S_80DAD000_1 *state = NULL;
    s8 saved_x;
    s8 saved_y;
    s16 saved_value;
    void *object_arg;
    void *base_arg;
    s32 flags_14;
    s32 flags_1c;

    saved_x = spawn_x;
    saved_value = initial_value;
    saved_y = spawn_y;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        object->update_callback = &func_80152A3C;
        state->unk_13 = MONSTER_DREAMIN;
        register_node(object, project_sprite_chain);
        base_data = object->position;
        base_data->z.w.i = saved_value;
        placement = object->sprite;
        spawn_mode = spawn_flags & 3;
        placement->tile_y = saved_y;
        extended_state = state;
        placement->frameTable = &D_8015586C;
        placement->tile_x = saved_x;
        if (spawn_mode == 1) {
            flags_14 = state->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = state->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (spawn_mode >= 2) {
            flags_14 = state->unk_14 | ACTOR_CLASS_ENABLED;
            flags_1c = state->unk_1C | ACTOR_PLAYER_SIDE;
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                if (!(state->unk_14 & ACTOR_RESIST_SLEEP)) {
                    if (generate_random_value() & 1) {
                        state->unk_1C = (s32) (state->unk_1C | ACTOR_ASLEEP);
                        set_or_clear_actor_status_slot(state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, base_data, placement, spawn_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &func_80152E68;
        try_move_actor_to_valid_position(extended_state, base_data, placement, state);
    }
    return state;
}

#include "shared/entity.h"
#include "shared/slus_callbacks.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/actor.h"

typedef void (*Callback)(void);

extern void D_8016AAA4(void);
extern void D_8016DFB8(void);
extern void D_8016E000(void);
extern void tyrant_slot_f_action_callback(void);

typedef struct S_8016A898_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    union { u32 u32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_8016A898_0;   /* result in spawn_tyrant_with_slot_f_action */


/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Tyrant with default frames at D_8016DFB8, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_tyrant_with_slot_f_action(s16 spawn_flags, s16 param_a, s16 param_b, s32 param_c)
{
    register ActorRecord *result;
    ObjectNodeHeader *object;
    ObjectPosition *motion;
    s8 held_a;
    s16 held_b;
    s32 held_c;
    void *tail_actor;
    void *state_data;
    SpriteFrameState *tail_entity;
    SpriteFrameState *part_data;
    s32 value;
    u16 tail_flags;

    held_a = param_a;
    result = 0;
    held_c = param_c;
    held_b = param_b;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        result = NODE_BODY(object);
        (object->update_callback) = D_8016AAA4;
        result->species = MONSTER_TYRANT;
        register_node(object, project_sprite_chain);

        motion = object->position;
        motion->z.w.i = held_c;
        part_data = object->sprite;
        part_data->tile_y = held_b;
        part_data->frameTable = D_8016DFB8;
        part_data->tile_x = held_a;
        state_data = result;

        if ((spawn_flags & 3) == 1) {
            result->flags14 |= 0x6000;
            result->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            result->action_state_flags |= 0x4000;
        } else {
            if ((spawn_flags & 3) >= 2) {
                result->flags14 |= 0x2000;
                result->flags1C |= ACTOR_PLAYER_SIDE;
                result->action_state_flags |= 0x4000;
            } else {
                if (((spawn_flags & -4) << 16) == 0 &&
                    !(result->flags14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        result->flags1C |= ACTOR_ASLEEP;
                        value = generate_random_value();
                        set_or_clear_actor_status_slot(result, STATUS_SLEEP, (value & 0x3F) | 0x20);
                        part_data->frameTable = D_8016E000;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, motion, part_data, spawn_flags);

        tail_actor = state_data;
        (*((u8 *)tail_actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)tail_actor + 0x9C)) = -1;
        (*(Callback *)((u8 *)tail_actor + 0x8C)) = tyrant_slot_f_action_callback;
        tail_flags = part_data->flags;
        tail_entity = part_data;
        tail_flags |= 0xC;
        tail_entity->flags = tail_flags;
        (*(s16 *)((u8 *)tail_actor + 0xAA)) = ((S_8016A898_0 *)result)->unk_14.u16 & 7;
        try_move_actor_to_valid_position(tail_actor, motion, tail_entity, result);
    }
    return result;
}

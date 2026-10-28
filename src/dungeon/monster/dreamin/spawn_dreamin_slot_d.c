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
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"
typedef struct R03_80170A28_S_80170A28_2 R03_80170A28_S_80170A28_2;
typedef struct ActorActionView ActorActionView;
typedef struct ActorSpriteView ActorSpriteView;


typedef struct S_80DA1000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DA1000_2;

typedef struct S_80DA1000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DA1000_4;

s32 generate_random_value(void);
void func_8015EA3C(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part);
void func_8015EE68(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
extern M2C_UNK D_8016186C;

void *move_and_fade_effect_sprite(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 type_id) ;
/* Allocates an entity and initializes its type, placement, flags, and callbacks. */
/* Creates Dreamin with default frames at D_8016186C, applies spawn flags, and attempts valid tile
 * placement. */
void *move_and_fade_effect_sprite(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 type_id) {
    s32 unused_slot;
    s32 spawn_mode;
    s32 flags_14;
    s32 flags_1c;
    SpriteFrameState *placement;
    ObjectPosition *type_data;
    ObjectNodeHeader *object;
    S_80DA1000_4 *entity_data;
    ActorRecord *entity = NULL;
    void *body;
    s8 saved_x;
    s8 saved_y;
    s16 saved_type;
    void *object_arg;
    void *type_arg;

    saved_x = grid_x;
    saved_type = type_id;
    saved_y = grid_y;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        body = object + 1;
        entity = body;
        object->update_callback = &func_8015EA3C;
        entity->species = MONSTER_DREAMIN;
        register_node(object, project_sprite_chain);
        type_data = object->position;
        type_data->z.w.i = saved_type;
        placement = object->sprite;
        spawn_mode = spawn_flags & 3;
        placement->tile_y = saved_y;
        entity_data = body;
        placement->frameTable = &D_8016186C;
        placement->tile_x = saved_x;
        if (spawn_mode == 1) {
            flags_14 = entity->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = entity->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            entity->flags14 = flags_14;
            entity->flags1C = flags_1c;
        } else if (spawn_mode >= 2) {
            flags_14 = entity->flags14 | ACTOR_CLASS_ENABLED;
            flags_1c = entity->flags1C | ACTOR_PLAYER_SIDE;
            entity->flags14 = (s32) flags_14;
            entity->flags1C = (s32) flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                if (!(entity->flags14 & ACTOR_RESIST_SLEEP)) {
                    if (generate_random_value() & 1) {
                        entity->flags1C = (s32) (entity->flags1C | ACTOR_ASLEEP);
                        set_or_clear_actor_status_slot(entity, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, type_data, placement, spawn_flags);
        entity_data->unk_9A = 0xFF;
        entity_data->unk_9C = -1;
        entity_data->unk_8C = &func_8015EE68;
        try_move_actor_to_valid_position(entity_data, type_data, placement, entity);
    }
    return entity;
}

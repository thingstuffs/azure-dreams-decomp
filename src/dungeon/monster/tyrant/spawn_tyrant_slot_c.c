/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"

typedef struct T_80170AA4_S_80170AA4_2 T_80170AA4_S_80170AA4_2;
typedef struct ActorSpriteView ActorSpriteView;

typedef struct S_func_80158898_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_func_80158898_1;



typedef struct S_func_80158898_4 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s16 unk_AA;
} S_func_80158898_4;

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s16 set_or_clear_actor_status_slot();
s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
void func_80158AA4(void *actor, T_80170AA4_S_80170AA4_2 *motion, void *part);
void func_80158F68(Rec_func_800A9E70_arg0 *action, void *context, ActorSpriteView *sprite, EntityRec *actor);
extern M2C_UNK D_8015BFB8;
extern M2C_UNK D_8015C000;

/* Allocate a dungeon object and initialize its placement, flags, and behavior. */
/* Creates Tyrant with default frames at D_8015BFB8, applies spawn flags, and attempts valid tile
 * placement. */
 void *update_variant_part_brightness(s16 spawn_flags, s16 x, s16 y, s16 config_value) {
    S_func_80158898_1 *object_state;
    s32 mode_or_roll;
    u16 state_flags;
    SpriteFrameState *placement;
    ObjectPosition *config;
    S_func_80158898_4 *behavior;
    ObjectNodeHeader *object;
    s8 saved_x;
    s16 saved_config_value;
    s8 saved_y;
    void *init_config;

    object_state = NULL;
    saved_x = x;
    saved_config_value = config_value;
    saved_y = y;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        object_state = ((void *)object) + 0x20;
        object->update_callback = &func_80158AA4;
        object_state->unk_13 = MONSTER_TYRANT;
        register_node(object, project_sprite_chain);
        config = object->position;
        config->z.w.i = saved_config_value;
        placement = object->sprite;
        mode_or_roll = spawn_flags & 3;
        placement->tile_y = saved_y;
        behavior = object_state;
        placement->frameTable = &D_8015BFB8;
        placement->tile_x = saved_x;
        if (mode_or_roll == 1) {
            state_flags = object_state->unk_98;
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x6000);
            object_state->unk_98 = (u16) (state_flags | 0x4000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x6000);
        } else if (mode_or_roll >= 2) {
            state_flags = object_state->unk_98;
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x2000);
            object_state->unk_98 = (u16) (state_flags | 0x4000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x2000);
        } else if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(object_state->unk_14 & 0x200)) {
                init_config = config;
                mode_or_roll = generate_random_value();
                if (mode_or_roll & 1) {
                    object_state->unk_1C = (s32) (object_state->unk_1C | 0x200);
                    set_or_clear_actor_status_slot(object_state, 1, (generate_random_value() & 0x3F) | 0x20);
                    placement->frameTable = &D_8015C000;
                }
            }
        }
        initialize_actor_sprite_and_animation(object, config, placement, spawn_flags);
        behavior->unk_9A = 0xFF;
        behavior->unk_9C = -1;
        behavior->unk_8C = &func_80158F68;
        placement->flags = (u16) (placement->flags | 0xC);
        behavior->unk_AA = (s16) ((u16) object_state->unk_14 & 7);
        try_move_actor_to_valid_position(behavior, config, placement, object_state);
    }
    return object_state;
}

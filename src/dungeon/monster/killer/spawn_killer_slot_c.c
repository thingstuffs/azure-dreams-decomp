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
typedef struct ActionState ActionState;
typedef struct ActorSprite ActorSprite;

typedef struct S_80FF3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FF3000_1;

typedef struct S_80FF3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FF3000_2;

typedef struct S_80FF3000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FF3000_4;

void *allocate_list_node();
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s16 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void func_80158A7C(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part);
void func_80158EA8(ActionState *actor, void *context, ActorSprite *sprite, EntityRec *entity);
extern M2C_UNK D_8015C038;
extern M2C_UNK D_8015C088;

void *spawn_killer_slot_c(s16, s32, s32, s16);

/* Allocates and initializes a dungeon object with flags and placement parameters. */
/* Creates Killer with default frames at D_8015C038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer_slot_c(s16 init_flags, s32 pos_x, s32 pos_y, s16 init_value) {
    S_80FF3000_1 *object_state;
    ObjectNodeHeader *object;
    u16 saved_value;
    ObjectPosition *base_data;
    s8 saved_y;
    s8 saved_x;
    s32 mode_or_flags;
    s32 config_value;
    SpriteFrameState *placement;
    S_80FF3000_4 *extended_state;

    saved_x = pos_x;
    saved_value = init_value;
    saved_y = pos_y;
    pos_y = 0;
    object_state = (void *)pos_y;
    pos_x = 0x112;
    object = allocate_list_node(pos_x, ((void *)&scene_object_list_anchor.next));
    if (object != NULL) {
        object_state = ((void *)object) + 0x20;
        object->update_callback = &func_80158A7C;
        object_state->unk_13 = MONSTER_KILLER;
        register_node(object, project_sprite_chain);
        config_value = (s32) &D_8015C038;
        base_data = object->position;
        base_data->z.w.i = saved_value;
        placement = object->sprite;
        mode_or_flags = init_flags & 3;
        placement->tile_y = saved_y;
        extended_state = object_state;
        placement->frameTable = (void *) config_value;
        placement->tile_x = saved_x;
        if (mode_or_flags == 1) {
            object_state->unk_14 = (s32) (object_state->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER));
            object_state->unk_1C = (s32) (object_state->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER));
        } else if (mode_or_flags >= 2) {
            object_state->unk_14 = (s32) (object_state->unk_14 | ACTOR_CLASS_ENABLED);
            object_state->unk_1C = (s32) (object_state->unk_1C | ACTOR_PLAYER_SIDE);
        } else {
            config_value = init_flags & ~3;
            if ((config_value << 0x10) == 0) {
                if (!(object_state->unk_14 & ACTOR_RESIST_SLEEP)) {
                    if (generate_random_value() & 1) {
                        object_state->unk_1C = (s32) (object_state->unk_1C | ACTOR_ASLEEP);
                        set_or_clear_actor_status_slot(object_state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                        placement->frameTable = &D_8015C088;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, base_data, placement, (s16)(s32) init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &func_80158EA8;
        try_move_actor_to_valid_position(extended_state, base_data, placement, object_state);
    }
    return object_state;
}

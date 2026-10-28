#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"


typedef struct S_80BFD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80BFD000_2;

typedef struct S_80BFD000_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80BFD000_4;   /* actor in spawn_clown_slot_d */

extern u8 clown_object_callback_3[];
s32 generate_random_value(void);
extern M2C_UNK D_8015F014;
extern M2C_UNK D_8016220C;
extern M2C_UNK D_8016225C;

/* Create a dungeon actor and initialize its placement, flags, and behavior. */
/* Creates Clown with default frames at D_8016220C, applies spawn flags, and attempts valid tile placement. */
void *spawn_clown_slot_d(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_value) {
    s32 unused_byte_neg_ba0;
    s32 unused_byte_21d8;
    s32 kind_or_bits;
    ActorRecord *actor_state = NULL;
    void *body;
    ObjectNodeHeader *object;
    SpriteFrameState *placement;
    ObjectPosition *attributes;
    S_80BFD000_4 *actor;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    s32 flags_14;
    s32 flags_1c;
    void *query_object;
    void *query_attributes;

    saved_x = tile_x;
    saved_value = spawn_value;
    saved_y = tile_y;
    unused_byte_21d8 = (s32) *(s8 *)0x21D8;
    unused_byte_neg_ba0 = (s32) *(s8 *)-0xBA0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        body = object + 1;
        actor_state = body;
        actor = body;
        object->update_callback = clown_object_callback_3;
        actor_state->species = MONSTER_CLOWN;
        register_node(object, project_sprite_chain);
        attributes = object->position;
        attributes->z.w.i = saved_value;
        placement = object->sprite;
        kind_or_bits = spawn_flags & 3;
        placement->tile_y = saved_y;
        placement->frameTable = &D_8016220C;
        placement->tile_x = saved_x;
        if (kind_or_bits == 1) {
            flags_14 = actor_state->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = actor_state->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            actor_state->flags14 = flags_14;
            actor_state->flags1C = flags_1c;
        } else if (kind_or_bits >= 2) {
            flags_14 = actor_state->flags14 | ACTOR_CLASS_ENABLED;
            flags_1c = actor_state->flags1C | ACTOR_PLAYER_SIDE;
            actor_state->flags14 = flags_14;
            actor_state->flags1C = flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                query_object = object;
                if (!(actor_state->flags14 & ACTOR_RESIST_SLEEP)) {
                    query_attributes = attributes;
                    kind_or_bits = generate_random_value();
                    if (kind_or_bits & 1) {
                        set_or_clear_actor_status_slot(actor_state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                        placement->frameTable = &D_8016225C;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, attributes, placement, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015F014;
        actor_state->flags1C = (s32) (actor_state->flags1C | 0x40000);
        actor->unk_92 = -0x20;
        try_move_actor_to_valid_position(actor, attributes, placement, actor_state);
    }
    return actor_state;
}

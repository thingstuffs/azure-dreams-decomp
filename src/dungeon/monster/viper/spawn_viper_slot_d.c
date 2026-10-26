#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"

typedef s32 M2C_UNK;

typedef struct  S_80F45000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F45000_1;   /* work in allocate_actor_parts */

typedef struct S_80F45000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80F45000_4;   /* actor in allocate_actor_parts */

extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */

extern u8 D_8015EA68[];
extern M2C_UNK D_8015EE94;
extern u8 D_80162A7C[];
extern u8 viper_frame_set_8[];

/* Allocate an actor and initialize its parts and behavior from the spawn flags. */
/* Creates Viper with default frames at D_80162A7C, applies spawn flags, and attempts valid tile placement. */
void *allocate_actor_parts(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    void *work = 0;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    register SpriteFrameState *part_b;
    S_80F45000_4 *actor;
    register s32 kind;
    s32 random_bits;
    s8 saved_x;
    s16 saved_part_value;
    s8 saved_y;
    void *obj_arg;
    void *part_arg;

    saved_x = tile_x;
    saved_part_value = part_value;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8015EA68;
        ((S_80F45000_1 *)work)->unk_13 = MONSTER_VIPER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_y;
        actor = work;
        part_b->frameTable = D_80162A7C;
        part_b->tile_x = saved_x;

        if (kind == 1) {
            ((S_80F45000_1 *)work)->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((S_80F45000_1 *)work)->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            ((S_80F45000_1 *)work)->unk_14 |= ACTOR_CLASS_ENABLED;
            ((S_80F45000_1 *)work)->unk_1C |= ACTOR_PLAYER_SIDE;
        } else {
            obj_arg = obj;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_80F45000_1 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                    part_arg = part_a;
                    random_bits = generate_random_value();
                    obj_arg = obj;
                    if (random_bits & 1) {
                        ((S_80F45000_1 *)work)->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = viper_frame_set_8;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015EE94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

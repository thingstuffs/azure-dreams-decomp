#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"



extern s32 generate_random_value(void);
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
extern u8 D_8016AA30[];
extern M2C_UNK D_8016AE5C;
extern u8 D_8016DD0C[];
extern u8 D_8016DD4C[];

/* Creates a dungeon actor and initializes its parts and state from the spawn flags. */
/* Creates Battnel with default frames at D_8016DD0C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_dungeon_actor_from_spawn_flags(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    void *body;
    ActorRecord *actor;
    s32 state_bits;
    s32 next_state_bits;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    void *saved_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        body = obj + 1;
        work = body;
        obj->update_callback = D_8016AA30;
        work->species = MONSTER_BATTNEL;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_y;
        actor = body;
        part_b->frameTable = D_8016DD0C;
        part_b->tile_x = saved_x;
        do {

            if (kind == 1) {
                state_bits = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                next_state_bits = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                work->flags14 = state_bits;
                work->flags1C = next_state_bits;
            } else if (kind >= 2) {
                state_bits = work->flags14 | ACTOR_CLASS_ENABLED;
                next_state_bits = work->flags1C | ACTOR_PLAYER_SIDE;
                work->flags14 = state_bits;
                work->flags1C = next_state_bits;
            } else {
                saved_part = obj;
                if (((spawn_flags & ~3) << 16) == 0) {
                    if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                        saved_part = part_a;
                        state_bits = generate_random_value();
                        saved_part = obj;
                        if (!(state_bits & 1)) {
                            break;
                        }
                        work->flags1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_8016DD4C;
                    }
                }
            }
            saved_part = obj;

        } while (0);
        initialize_actor_sprite_and_animation(saved_part, part_a, part_b, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &D_8016AE5C;
        actor->unk_A4.halves.low.s = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

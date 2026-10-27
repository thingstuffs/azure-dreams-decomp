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
#include "dungeon/actor/status.h"




extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern u8 D_8014CA50[];
extern M2C_UNK griffon_slot_a_action_callback;
extern u8 D_80150C3C[];
extern u8 D_80150C8C[];

/* Creates an actor and initializes its parts and flags for the selected kind. */
/* Creates Griffon with default frames at D_80150C3C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_actor_for_selected_kind(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 flags_or_roll;
    s32 state_flags;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    void *init_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_8014CA50;
        work->species = MONSTER_GRIFFON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_y;
        actor = work;
        part_b->frameTable = D_80150C3C;
        part_b->tile_x = saved_x;
        do {

            if (kind == 1) {
                flags_or_roll = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                state_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                work->flags14 = flags_or_roll;
                work->flags1C = state_flags;
            } else if (kind >= 2) {
                flags_or_roll = work->flags14 | ACTOR_CLASS_ENABLED;
                state_flags = work->flags1C | ACTOR_PLAYER_SIDE;
                work->flags14 = flags_or_roll;
                work->flags1C = state_flags;
            } else {
                init_part = obj;
                if (((spawn_flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                    init_part = part_a;
                    flags_or_roll = generate_random_value();
                    init_part = obj;
                    if (!(flags_or_roll & 1)) {
                        break;
                    }
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80150C8C;
                }
            }
            init_part = obj;

        } while (0);
        initialize_actor_sprite_and_animation(init_part, part_a, part_b, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &griffon_slot_a_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

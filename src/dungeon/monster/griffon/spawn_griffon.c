#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"




extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern u8 D_8016AA50[];
extern u8 griffon_slot_f_action_callback;
extern u8 D_8016EC3C[];
extern u8 D_8016EC8C[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Griffon with default frames at D_8016EC3C, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_griffon_actor(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_8016AA50;
        work->species = MONSTER_GRIFFON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_variant;
        actor = work;
        part_b->frameTable = D_8016EC3C;
        part_b->tile_x = saved_kind_id;

        if (kind == 1) {
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
        } else if (kind >= 2) {
            left = work->flags14 | ACTOR_CLASS_ENABLED;
            right = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = left;
            work->flags1C = right;
        } else {
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                call_a1 = part_a;
                left = generate_random_value();
                call_a1 = obj;
                call_a1 = obj;
                if (left & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8016EC8C;
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &griffon_slot_f_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

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

typedef s32 M2C_UNK;




extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(void);
extern u8 D_8015EA50[];
extern M2C_UNK griffon_slot_d_action_callback;
extern u8 D_80162C3C[];
extern u8 D_80162C8C[];

/* Creates a Griffon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_randomized_flagged_object(s16 flags, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;
    void *call_a1;

    work = 0;
    saved_arg1 = value_24;
    saved_arg3 = value_0A;
    saved_arg2 = value_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_8015EA50;
        work->species = MONSTER_GRIFFON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_arg3;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_arg2;
        actor = work;
        part_b->frameTable = D_80162C3C;
        part_b->tile_x = saved_arg1;

        if (kind == 1) {
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
        } else if (kind > 1) {
            left = work->flags14 | ACTOR_CLASS_ENABLED;
            right = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = left;
            work->flags1C = right;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                call_a1 = part_a;
                left = generate_random_value();
                if (left & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80162C8C;
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(obj)), part_a, part_b, flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &griffon_slot_d_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

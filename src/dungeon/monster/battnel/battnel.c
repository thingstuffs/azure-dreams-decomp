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
#include "engine/node.h"

typedef s32 M2C_UNK;



extern s32 generate_random_value(void);
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
extern u8 D_80158A30[];
extern M2C_UNK D_80158E5C;
extern u8 D_8015BD0C[];
extern u8 D_8015BD4C[];

/* Allocates a dungeon object and initializes its flags, parts, and actor state. */
/* Creates Battnel with default frames at D_8015BD0C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_battnel_actor(s16 spawn_flags, s16 part_byte_24, s16 part_byte_25, s16 part_value)
{
    s32 kind;
    ActorRecord *work = 0;
    void *body;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *actor;
    s32 flags_or_roll;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_part_value;
    s8 saved_byte_25;
    void *part_arg;

    saved_byte_24 = part_byte_24;
    saved_part_value = part_value;
    saved_byte_25 = part_byte_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        body = obj + 1;
        work = body;
        obj->update_callback = D_80158A30;
        work->species = MONSTER_BATTNEL;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_byte_25;
        actor = body;
        part_b->frameTable = D_8015BD0C;
        part_b->tile_x = saved_byte_24;
        do {

            if (kind == 1) {
                flags_or_roll = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                secondary_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                work->flags14 = flags_or_roll;
                work->flags1C = secondary_flags;
            } else if (kind >= 2) {
                flags_or_roll = work->flags14 | ACTOR_CLASS_ENABLED;
                secondary_flags = work->flags1C | ACTOR_PLAYER_SIDE;
                work->flags14 = flags_or_roll;
                work->flags1C = secondary_flags;
            } else {
                part_arg = obj;
                if (((spawn_flags & ~3) << 16) == 0) {
                    if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                        part_arg = part_a;
                        flags_or_roll = generate_random_value();
                        part_arg = obj;
                        if (!(flags_or_roll & 1)) {
                            break;
                        }
                        work->flags1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_8015BD4C;
                    }
                }
            }
            part_arg = obj;

        } while (0);
        initialize_actor_sprite_and_animation(part_arg, part_a, part_b, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &D_80158E5C;
        actor->unk_A4.halves.low.s = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

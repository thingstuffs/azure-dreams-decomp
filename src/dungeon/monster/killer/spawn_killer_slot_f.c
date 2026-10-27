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
#include "engine/node.h"





extern s32 generate_random_value(void);

extern u8 D_8016AA7C[];
extern u8 killer_slot_f_default_frames[];
extern u8 killer_frame_set_1[];
extern u8 killer_slot_f_action_address[];

/* Creates a dungeon object and initializes its kind flags and part parameters. */
/* Creates Killer with default frames at D_8016E038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer_slot_f(s16 kind_flags, s32 part_value_24, s32 part_value_25, s16 part_value_0a)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 flags;
    s32 paired_flags;
    s16 saved_value_24;
    s16 saved_value_0a;
    s16 saved_value_25;

    work = 0;
    saved_value_24 = part_value_24;
    saved_value_0a = part_value_0a;
    saved_value_25 = part_value_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_8016AA7C;
        work->species = MONSTER_KILLER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value_0a;
        part_b = obj->sprite;
        kind = kind_flags & 3;
        part_b->tile_y = saved_value_25;
        actor = work;
        part_b->frameTable = killer_slot_f_default_frames;
        part_b->tile_x = saved_value_24;

        if (kind == 1) {
            flags = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            paired_flags = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = flags;
            work->flags1C = paired_flags;
        } else if (kind >= 2) {
            flags = work->flags14 | ACTOR_CLASS_ENABLED;
            paired_flags = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = flags;
            work->flags1C = paired_flags;
        } else {
            if ((((kind_flags & ~3) << 16) == 0) &&
                !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                flags = generate_random_value();
                if (flags & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = killer_frame_set_1;
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &killer_slot_f_action_address;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

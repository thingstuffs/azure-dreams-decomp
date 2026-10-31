#include "shared/entity.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"



extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

#include "dungeon/monster/glacier.h"
extern u8 glacier_frame_set_2[];

/* Spawn the overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Glacier with default frames at D_8017609C, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_configured_overlay_object_alt(s16 flags, s16 kind_id, s16 variant, s32 spawn_value)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    ActorRecord *result;
    ObjectNodeHeader *object;
    ObjectPosition *part0;
    SpriteFrameState *part1;
    ActorRecord *result_copy;

    result = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        result = object;
        result = (ActorRecord *)((u8 *)result + 0x20);
        object->update_callback = update_monster_appearance_motion;
        result->species = MONSTER_GLACIER;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = object->position;
            handler = glacier_direction_frames;
            part0->z.w.i = spawn_value;
            part1 = object->sprite;
            kind = flags & 3;
            part1->tile_y = variant;
            result_copy = result;
            part1->frameTable = handler;
        }
        part1->tile_x = kind_id;

        if (kind == 1) {
            flags0 = result->flags14;
            flags1 = result->flags1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            result->flags14 = flags0;
            result->flags1C = flags1;
        } else if (kind >= 2) {
            flags0 = result->flags14;
            flags1 = result->flags1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            result->flags14 = flags0;
            result->flags1C = flags1;
        } else if (((flags & -4) << 16) == 0) {
            if ((result->flags14 & ACTOR_RESIST_SLEEP) == 0) {
                if ((generate_random_value() & 1) != 0) {
                    set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part1->frameTable = glacier_frame_set_2;
                }
            }
        }

        initialize_actor_sprite_and_animation(object, part0, part1, flags);
        result_copy->action_id.u = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C.address = update_actor_timed_effects;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}

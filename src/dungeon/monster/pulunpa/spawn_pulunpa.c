#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/entity_spawn_variant_data.h"
#include "engine/node/registration.h"
#include "dungeon/system/random.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor.h"
#include "dungeon/monster/pulunpa_frames.h"




extern u8 D_80170AE0[];
extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_variant_action_address[];
#include "dungeon/monster/pulunpa.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Pulunpa, selecting its normal or alternate callback and sprite table from the global spawn
 * variant. */
void *create_actor_grid_object(s16 flags, s16 unused_kind_id, s16 variant, s16 unused_spawn)
{
    s8 kind_id;
    s16 spawn_value;
    s32 kind;
    s32 random;
    s16 arg0_copy;
    s32 alloc_id;
    ObjectNodeHeader **list_head;
    ObjectNodeHeader *part;
    ActorRecord *work;
    ObjectPosition *coord;
    SpriteFrameState *state;
    ActorRecord *actor;

    work = 0;
    alloc_id = 0x112;
    kind_id = unused_kind_id;
    list_head = &scene_object_list_anchor.next;
    spawn_value = unused_spawn;
    part = allocate_list_node(alloc_id, list_head);
    arg0_copy = flags;
    if (part != 0) {
        work = NODE_BODY(part);
        work->species = MONSTER_PULUNPA;
        register_node(part, project_sprite_chain);
        coord = part->position;
        kind = flags & 3;
        coord->z.w.i = spawn_value;
        state = part->sprite;
        state->tile_y = variant;
        actor = work;
        state->tile_x = kind_id;

        if (kind == 1) {
            work->unk_8C.address = pulunpa_action_resume_address;
            work->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            state->frameTable = pulunpa_frame_set_1;
        } else if (kind >= 2) {
            work->unk_8C.address = pulunpa_action_resume_address;
            work->flags14 |= ACTOR_CLASS_ENABLED;
            work->flags1C |= ACTOR_PLAYER_SIDE;
            state->frameTable = pulunpa_frame_set_1;
        } else if (((flags & -4) << 16) == 0) {
            if (!(((u32)work->flags14) & ACTOR_RESIST_SLEEP)) {
                random = generate_random_value();
                if (random & 1) {
                    random = generate_random_value();
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (random & 0x3F) | 0x20);
                    state->frameTable = pulunpa_direction_frames;
                }
            }
            if (entity_spawn_variant_code < 10) {
                actor->unk_8C.address = pulunpa_action_resume_address;
                state->frameTable = pulunpa_frame_set_1;
            } else {
                actor->unk_A4.bytes[3] = 1;
                actor->unk_8C.address = pulunpa_variant_action_address;
                state->frameTable = pulunpa_frame_set_2;
            }
        } else {
            work->unk_8C.address = pulunpa_action_resume_address;
            state->frameTable = pulunpa_frame_set_1;
        }

        part->update_callback = D_80170AE0;
        initialize_actor_sprite_and_animation(part, coord, state, arg0_copy);
        actor->action_id = 0xFF;
        actor->unk_9C = -1;
        (*(u8 *)&actor->unk_A8) = 0;
        try_move_actor_to_valid_position(actor, coord, state, work);
    }
    return work;
}

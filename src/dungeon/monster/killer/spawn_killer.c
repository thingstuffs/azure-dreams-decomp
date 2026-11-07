#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
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






extern u8 D_80170A7C[];
extern u8 killer_action_resume_address[];
#include "dungeon/monster/killer.h"
#include "dungeon/monster/killer_frames.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Killer with default frames at D_80174038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer(s16 flags, s32 kind_id, s32 variant, s32 spawn_value)
{
    void *result = 0;
    ObjectNodeHeader *created;
    ObjectPosition *position;
    SpriteFrameState *part_b;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s16 saved_kind_id;
    s32 saved_spawn;
    s16 saved_variant;
    s16 original_flags;
    void *call_a0;
    void *call_a1;
    s32 kind;

    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    created = allocate_list_node(0x112, &scene_object_list_anchor.next);
    original_flags = flags;
    if (created != 0) {
        result = NODE_BODY(created);
        created->update_callback = D_80170A7C;
        ((ActorRecord *)result)->species = MONSTER_KILLER;
        register_node(created, project_sprite_chain);

        position = created->position;
        position->z.w.i = saved_spawn;
        part_b = created->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_variant;
        actor = result;
        part_b->frameTable = killer_direction_frames;
        part_b->tile_x = saved_kind_id;

        if (kind == 1) {
            ((ActorRecord *)result)->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((ActorRecord *)result)->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            ((ActorRecord *)result)->flags14 |= ACTOR_CLASS_ENABLED;
            ((ActorRecord *)result)->flags1C |= ACTOR_PLAYER_SIDE;
        } else {
            call_a0 = created;
            if (((flags & ~3) << 16) == 0) {
                if (!(((u32)((ActorRecord *)result)->flags14) & ACTOR_RESIST_SLEEP)) {
                    call_a1 = position;
                    if (generate_random_value() & 1) {
                        ((ActorRecord *)result)->flags1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(result, STATUS_SLEEP,
                            (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = killer_frame_set_2;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(created, position, part_b,
            (s16)original_flags);
        actor->action_id = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = killer_action_resume_address;
        try_move_actor_to_valid_position(actor, position,
            part_b, result);
    }

    return result;
}

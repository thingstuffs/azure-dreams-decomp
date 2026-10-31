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
#include "dungeon/actor/status.h"




extern u8 D_80170A8C[];
extern u8 stealth_frame_set[];
extern u8 D_80173D78[];
#include "dungeon/monster/stealth.h"
#include "dungeon/effect/screen.h"

extern s32 generate_random_value(void);

#define BODY_STORAGE
#define BODY_ATTR

BODY_STORAGE void *spawn_mode_dependent_112_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value) BODY_ATTR;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select, then finish through the mode branch that either zeroes or arms the actor's 0xA6 state. */
/* Creates Stealth with frames at D_80173D30; a random display variant changes sprite flags and unlinks the
 * node. */
BODY_STORAGE void *spawn_mode_dependent_112_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    s32 mode;
    void *object_base;
    SpriteFrameState *part1;
    ObjectPosition *part0;
    ActorRecord *actor;
    ObjectNodeHeader *object;
    ActorRecord *result;
    void *body;

    result = 0;
    mode = 1;
    object = allocate_list_node(274, &scene_object_list_anchor.next);
    if (object != 0) {
        body = object + 1;
        result = body;
        object->update_callback = D_80170A8C;
        result->species = MONSTER_STEALTH;
        register_node(object, project_sprite_chain);
        part0 = *(void ** *)&object->position;
        part0->z.w.i = spawn_value;
        part1 = object->sprite;
        part1->tile_y = variant;
        actor = body;
        part1->frameTable = stealth_frame_set;
        kind = flags & 3;
        part1->tile_x = kind_id;
        if (kind == 1) {
            result->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            result->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            result->flags14 |= ACTOR_CLASS_ENABLED;
            result->flags1C |= ACTOR_PLAYER_SIDE;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(result->flags14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    result->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part1->frameTable = D_80173D78;
                }
            }
            mode = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part0, part1, flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = stealth_behavior_entry;
        actor->unk_A4.halves.low.s = -1;
        if (mode != 0) {
            actor->unk_A4.halves.high.s = 0;
        } else {
            object_base = (u8 *)actor - 0x20;
            actor->unk_A4.halves.high.s = 1;
            part1->tpage_abr = 0x60;
            part1->flags |= 0xC;
            part1->clut -= 0x80;
            unlink_node(object_base);
            retire_tracked_effect_by_id(object_base);
        }
        try_move_actor_to_valid_position(actor, part0, part1, result);
    }

    return result;
}

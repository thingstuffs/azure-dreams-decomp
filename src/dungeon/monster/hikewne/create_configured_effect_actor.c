#include "shared/entity.h"
#include "dungeon/monster/hikewne.h"
#include "shared/actor_status_flags.h"
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

extern u8 hikewne_direction_frames[16];
extern u8 hikewne_frame_set_2[16];

/* Creates a Hikewne actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_configured_effect_actor(s16 mask, s16 value_at_24, s16 value_at_25, s32 value_at_0A)
{
    s32 kind;
    s32 flags14;
    s32 flags1c;
    ObjectNodeHeader *object;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    void *handler;
    ActorRecord *actor;
    ActorRecord *actor2;

    actor = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        actor = object;
        actor = (ActorRecord *)((u8 *)actor + 0x20);
        object->update_callback = update_entity_movement_and_ground;
        actor->species = MONSTER_HIKEWNE;
        register_node(object, project_sprite_chain);

        part_a = object->position;
        handler = hikewne_direction_frames;
        part_a->z.w.i = value_at_0A;
        part_b = object->sprite;
        kind = mask & 3;
        part_b->tile_y = value_at_25;
        actor2 = actor;
        part_b->frameTable = handler;
        part_b->tile_x = value_at_24;
        actor->unk_9E.s = 0;

        if (kind == 1) {
            flags14 = actor->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags1c = actor->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            actor->flags14 = flags14;
            actor->flags1C = flags1c;
        } else if (kind >= 2) {
            flags14 = actor->flags14 | ACTOR_CLASS_ENABLED;
            flags1c = actor->flags1C | ACTOR_PLAYER_SIDE;
            actor->flags14 = flags14;
            actor->flags1C = flags1c;
        } else if (((mask & ~3) << 16) == 0 && !(actor->flags14 & ACTOR_RESIST_SLEEP) && (generate_random_value() & 1)) {
            set_or_clear_actor_status_slot(actor, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
            part_b->frameTable = hikewne_frame_set_2;
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, mask);
        actor2->action_id.u = 0xFF;
        actor2->unk_9C = -1;
        actor2->unk_8C.address = update_actor_behavior_animation_and_facing;
        actor->flags1C |= 0x40000;
        actor2->unk_90.parts.high.s = -0x20;
        part_b->tpage_abr = 0x20;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor2, part_a, part_b, actor);
    }
    return actor;
}
/* MECHANISM: 2.8.0-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */

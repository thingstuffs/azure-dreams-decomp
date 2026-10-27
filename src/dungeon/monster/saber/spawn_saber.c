#include "shared/entity.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags);
s32 try_move_actor_to_valid_position(void *action, void *context, void *position, void *entity);

extern u8 D_80171320[];
#include "dungeon/monster/saber.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Saber with default frames at D_80174DEC, applies spawn flags, and attempts valid tile placement. */
void *spawn_saber(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    ActorRecord *result;
    ObjectNodeHeader *object;
    ObjectPosition *part0;
    SpriteFrameState *part1;
    ActorRecord *result_copy;
    void *body_storage;

    result = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        body_storage = object + 1;
        result = body_storage;
        object->update_callback = D_80171320;
        result->species = MONSTER_SABER;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = object->position;
            handler = saber_direction_frames;
            part0->z.w.i = attr_c;
            part1 = object->sprite;
            kind = spawn_flags & 3;
            part1->tile_y = attr_b;
            result_copy = body_storage;
            part1->frameTable = handler;
        }
        part1->tile_x = attr_a;

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
        } else {
            if (((spawn_flags & -4) << 16) == 0) {
                if ((result->flags14 & ACTOR_RESIST_SLEEP) == 0) {
                    if ((generate_random_value() & 1) != 0) {
                        set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                        part1->frameTable = saber_direction_frames_2;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(object, part0, part1, spawn_flags);
        result_copy->action_id.u = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C.address = &saber_behavior_entry;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */

#include "shared/entity.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"


typedef struct S_80171850_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171850_4;   /* result_copy in spawn_dual_part_overlay_effect */

extern s32 generate_random_value(void);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 D_80171A18[];
extern s32 blume_action_resume_address;
#include "dungeon/monster/blume.h"


/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Blume with default frames at D_801753BC, applies spawn flags, and attempts valid tile placement. */
void *spawn_dual_part_overlay_effect(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    ObjectNodeHeader *object;
    ObjectPosition *part0;
    SpriteFrameState *part1;
    S_80171850_4 *result_copy;

    result = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        object->update_callback = D_80171A18;
        ((ActorRecord *)result)->species = MONSTER_BLUME;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = object->position;
            handler = blume_direction_frames;
            part0->z.w.i = attr_c;
            part1 = object->sprite;
            kind = spawn_flags & 3;
            part1->tile_y = attr_b;
            result_copy = result;
            part1->frameTable = handler;
        }
        part1->tile_x = attr_a;

        if (kind == 1) {
            flags0 = ((ActorRecord *)result)->flags14;
            flags1 = ((ActorRecord *)result)->flags1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((ActorRecord *)result)->flags14 = flags0;
            ((ActorRecord *)result)->flags1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((ActorRecord *)result)->flags14;
            flags1 = ((ActorRecord *)result)->flags1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((ActorRecord *)result)->flags14 = flags0;
            ((ActorRecord *)result)->flags1C = flags1;
        } else {
            if (((spawn_flags & -4) << 16) == 0 &&
                (((ActorRecord *)result)->flags14 & ACTOR_RESIST_SLEEP) == 0) {
                if ((generate_random_value() & 1) != 0) {
                    set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part1->frameTable = blume_direction_frames_2;
                }
            }
        }
        initialize_actor_sprite_and_animation(object, part0, part1, spawn_flags);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = &blume_action_resume_address;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}

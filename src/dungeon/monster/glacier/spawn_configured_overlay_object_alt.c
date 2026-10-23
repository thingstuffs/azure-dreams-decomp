#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170E74_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170E74_1;   /* result in spawn_configured_overlay_object_alt */

typedef struct S_80170E74_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170E74_2;   /* part0 in spawn_configured_overlay_object_alt */

typedef struct S_80170E74_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170E74_4;   /* result_copy in spawn_configured_overlay_object_alt */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 D_8017103C[];
extern s32 glacier_action_resume_address;
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
    S_80170E74_1 *result;
    ObjectNodeHeader *object;
    S_80170E74_2 *part0;
    SpriteFrameState *part1;
    S_80170E74_4 *result_copy;

    result = 0;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        result = object;
        result = (S_80170E74_1 *)((u8 *)result + 0x20);
        object->update_callback = D_8017103C;
        result->unk_13 = MONSTER_GLACIER;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = object->position;
            handler = glacier_direction_frames;
            part0->unk_0A = spawn_value;
            part1 = object->sprite;
            kind = flags & 3;
            part1->tile_y = variant;
            result_copy = result;
            part1->frameTable = handler;
        }
        part1->tile_x = kind_id;

        if (kind == 1) {
            flags0 = result->unk_14;
            flags1 = result->unk_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            result->unk_14 = flags0;
            result->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = result->unk_14;
            flags1 = result->unk_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            result->unk_14 = flags0;
            result->unk_1C = flags1;
        } else if (((flags & -4) << 16) == 0) {
            if ((result->unk_14 & ACTOR_RESIST_SLEEP) == 0) {
                if ((generate_random_value() & 1) != 0) {
                    set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part1->frameTable = glacier_frame_set_2;
                }
            }
        }

        initialize_actor_sprite_and_animation(object, part0, part1, flags);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = &glacier_action_resume_address;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}

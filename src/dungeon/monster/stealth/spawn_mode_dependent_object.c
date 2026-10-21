#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170854_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_80170854_0;   /* object in spawn_mode_dependent_112_object */

typedef struct S_80170854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170854_1;   /* result in spawn_mode_dependent_112_object */

typedef struct S_80170854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170854_2;   /* part0 in spawn_mode_dependent_112_object */

typedef struct S_80170854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80170854_4;   /* actor in spawn_mode_dependent_112_object */

extern u8 D_80170A8C[];
extern u8 D_80173D30[];
extern u8 D_80173D78[];
extern u8 D_80170F74[];

extern void *allocate_list_node();
extern s32 register_node();
extern s32 generate_random_value();
extern s16 set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern s32 try_move_actor_to_valid_position();
extern void unlink_node();
extern void retire_tracked_effect_by_id();

#define BODY_STORAGE
#define BODY_ATTR

BODY_STORAGE void *spawn_mode_dependent_112_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value) BODY_ATTR;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select, then finish through the mode branch that either zeroes or arms the actor's 0xA6 state. */
BODY_STORAGE void *spawn_mode_dependent_112_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    s32 mode;
    void *object_base;
    SpriteFrameState *part1;
    S_80170854_2 *part0;
    void *actor;
    void *object;
    S_80170854_1 *result;

    result = 0;
    mode = 1;
    object = allocate_list_node(274, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        result = (u8 *)object + 0x20;
        ((S_80170854_0 *)object)->unk_10 = D_80170A8C;
        result->unk_13 = 0x23;
        register_node(object, project_sprite_chain);
        part0 = ((S_80170854_0 *)object)->unk_08;
        part0->unk_0A = spawn_value;
        part1 = ((S_80170854_0 *)object)->unk_0C;
        part1->unk_25 = variant;
        actor = result;
        part1->frameTable = D_80173D30;
        kind = flags & 3;
        part1->unk_24 = kind_id;
        if (kind == 1) {
            result->unk_14 |= 0x6000;
            result->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            result->unk_14 |= 0x2000;
            result->unk_1C |= 0x2000;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(result->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    result->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
                    part1->frameTable = D_80173D78;
                }
            }
            mode = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part0, part1, flags);
        ((S_80170854_4 *)actor)->unk_9A = 0xFF;
        ((S_80170854_4 *)actor)->unk_9C = -1;
        ((S_80170854_4 *)actor)->unk_8C = D_80170F74;
        ((S_80170854_4 *)actor)->unk_A4 = -1;
        if (mode != 0) {
            ((S_80170854_4 *)actor)->unk_A6 = 0;
        } else {
            object_base = (u8 *)actor - 0x20;
            ((S_80170854_4 *)actor)->unk_A6 = 1;
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

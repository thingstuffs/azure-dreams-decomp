#include "shared/object_node.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "engine/node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct PackedVec3 {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec3;

extern u8 D_8016F99C[];
extern u8 D_80173B1C[];
extern u8 D_80173B28[];
extern u8 encounter_overlay_work[];

typedef struct S_8016FAFC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
} S_8016FAFC_0;   /* part in create_encounter_overlay */

typedef struct S_8016FAFC_3 {
    u8 pad_00[0x5D58];
    void * unk_5D58;
    void * unk_5D5C;
} S_8016FAFC_3;   /* store_page in create_encounter_overlay */

/* Creates a sprite object with the selected vector preset and stores its global pointer. */
void create_encounter_overlay(s32 variant)
{
    ObjectNodeHeader *obj;
    u8 *part;
    ObjectNodeHeader *call_obj;
    SpriteFrameState *sprite;
    u8 *copy_src;
    u8 *sprite_vector;
    ObjectPosition *coords;

    obj = allocate_flagged_object_node(0x12);
    if (obj != NULL) {
        call_obj = obj;
        part = ((u8 *)obj) + 0x20;
        ((S_8016FAFC_0 *)part)->unk_18 = 0;
        ((S_8016FAFC_0 *)part)->unk_1C = variant;
        (obj->update_callback) = D_8016F99C;
        register_node(call_obj, draw_linked_sprites);

        sprite = obj->sprite;
        sprite->flags &= 0xFFF3;

        coords = obj->position;
        coords->x.w.i = 0xA0;
        coords->y.w.i = 0xA;
        coords->z.w.i = 2;

        sprite = obj->sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;

        if (variant == 0) {

            copy_src = D_80173B1C;
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)(copy_src + 0));
            ((S_8016FAFC_3 *)encounter_overlay_work)->unk_5D58 = obj;
        } else {

            copy_src = D_80173B28;
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)(copy_src + 0));
            ((S_8016FAFC_3 *)encounter_overlay_work)->unk_5D5C = obj;
        }
        sprite_vector = part + 0x28;
        sprite->source = sprite_vector;
    }
}

/* MECHANISM: The true-space body uses a local join, not a phantom call at 0x8016FC28.
   A 0x20 frame holds variant, obj, and obj+0x20 in s2/s0/s1; packed 12-byte
   assignments reproduce the two unaligned vector-copy arms. */

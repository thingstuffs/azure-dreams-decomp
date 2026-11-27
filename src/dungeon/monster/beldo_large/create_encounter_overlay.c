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

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern u8 D_8016F99C[];
extern Copy12 D_80173B1C;
extern Copy12 D_80173B28;
extern u8 encounter_overlay_work[];


typedef struct S_8016FAFC_3 {
    u8 pad_00[0x5D58];
    void * unk_5D58;
    void * unk_5D5C;
} S_8016FAFC_3;   /* store_page in create_encounter_overlay */

/* Creates a sprite object with the selected vector preset and stores its global pointer. */
void create_encounter_overlay(s32 variant)
{
    ObjectNodeHeader *obj;
    EncounterOverlayBody *part;
    ObjectNodeHeader *call_obj;
    SpriteFrameState *sprite;
    Copy12 *copy_src;
    u8 *sprite_vector;
    ObjectPosition *coords;

    obj = allocate_flagged_object_node(0x12);
    if (obj != NULL) {
        call_obj = obj;
        part = NODE_BODY(obj);
        part->unk_18 = 0;
        part->unk_1C = variant;
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

            copy_src = &D_80173B1C;
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)(copy_src + 0));
            ((S_8016FAFC_3 *)encounter_overlay_work)->unk_5D58 = obj;
        } else {

            copy_src = &D_80173B28;
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)(copy_src + 0));
            ((S_8016FAFC_3 *)encounter_overlay_work)->unk_5D5C = obj;
        }
        sprite_vector = ((u8 *)part + 0x28);
        sprite->source = sprite_vector;
    }
}

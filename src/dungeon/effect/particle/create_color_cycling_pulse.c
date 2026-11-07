#include "shared/sprite_frame_state.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 word[3];
} __attribute__((packed)) PackedCopy12;

extern u8 D_80173B58[48];

   /* ctrl in create_color_cycling_pulse */


/* Create and initialize an object at the supplied position with a fixed Z offset. */
void create_color_cycling_pulse(ObjectPosition *origin)
{
    ObjectNodeHeader *object;
    ObjectPosition *position;
    SpriteFrameState *control;
    ColorCyclingPulseBody *node;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        node = NODE_BODY(object);
        node->ticks_remaining = 0x1E;
        node->initial_duration = 0x1E;
        (object->update_callback) = update_color_cycling_pulse;
        register_node(object, project_sprite_chain);

        control = object->sprite;

        control->tpage_abr = 0x20;
        control->flags = control->flags | 0xC;

        position = object->position;
        position->x.v = origin->x.v;
        position->y.v = origin->y.v;
        position->z.v = origin->z.v + 0x180000;

        control = object->sprite;

        control->scale_x = 0x1400;
        control->scale_y = 0x1400;
        control->color.c.b = 0;
        control->color.c.g = 0;
        control->color.c.r = 0;
        control->depth_bias = 0;
        control->flags = control->flags | 0x80;

        (*(PackedCopy12 *)((u8 *)object + 0x48)) = (*(PackedCopy12 *)(D_80173B58 + 0));
        (*(PackedCopy12 *)((u8 *)object + 0x54)) = (*(PackedCopy12 *)(D_80173B58 + 0xC));
        (*(PackedCopy12 *)((u8 *)object + 0x60)) = (*(PackedCopy12 *)(D_80173B58 + 0x18));
        (*(PackedCopy12 *)((u8 *)object + 0x6C)) = (*(PackedCopy12 *)(D_80173B58 + 0x24));
        control->source = (u8 *)object + 0x48;
    }
}

/* MECHANISM: Four packed 12-byte assignments emit retail's twelve unaligned copy quartets without gcc's
   large-copy loop. */

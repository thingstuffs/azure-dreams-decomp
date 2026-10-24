#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 word[3];
} __attribute__((packed)) PackedCopy12;

extern void register_node(void *, void *);

extern u8 D_801671AC;
extern u8 D_80173B58[48];

typedef struct S_8016738C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_8016738C_0;   /* node in create_color_cycling_pulse */

typedef struct S_8016738C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016738C_1;   /* ctrl in create_color_cycling_pulse */

typedef struct S_8016738C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8016738C_3;   /* arg0 in create_color_cycling_pulse */

/* Create and initialize an object at the supplied position with a fixed Z offset. */
void create_color_cycling_pulse(S_8016738C_3 *origin)
{
    ObjectNodeHeader *object;
    ObjectPosition *position;
    SpriteFrameState *control;
    S_8016738C_0 *node;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        node = (u8 *)object + 0x20;
        node->unk_18 = 0x1E;
        node->unk_1A = 0x1E;
        (object->update_callback) = &D_801671AC;
        register_node(object, project_sprite_chain);

        control = object->sprite;

        control->tpage_abr = 0x20;
        control->flags = control->flags | 0xC;

        position = object->position;
        position->x.v = origin->unk_00;
        position->y.v = origin->unk_04;
        position->z.v = origin->unk_08 + 0x180000;

        control = object->sprite;

        control->scale_x = 0x1400;
        control->scale_y = 0x1400;
        control->color.c.b = 0;
        control->color.c.g = 0;
        control->color.c.r = 0;
        control->depth_bias = 0;
        control->flags = control->flags | 0x80;

        (*(PackedCopy12 *)((u8 *)object + 0x48)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0));
        (*(PackedCopy12 *)((u8 *)object + 0x54)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0xC));
        (*(PackedCopy12 *)((u8 *)object + 0x60)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0x18));
        (*(PackedCopy12 *)((u8 *)object + 0x6C)) = (*(PackedCopy12 *)((u8 *)D_80173B58 + 0x24));
        control->source = (u8 *)object + 0x48;
    }
}

/* MECHANISM: Four packed 12-byte assignments emit retail's twelve unaligned copy quartets without gcc's
   large-copy loop. */

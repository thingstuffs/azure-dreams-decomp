#include "shared/sprite_frame_state.h"
#include "dungeon/monster/beldo_large.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void register_node(void *, void *);

extern Copy12 D_80173B1C;

typedef struct S_80170298_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80170298_0;   /* part1 in create_encounter_view_darkener */

typedef struct S_80170298_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80170298_1;   /* part2 in create_encounter_view_darkener */

/* Allocate a type 0x12 object, clear its state, and attach a copy of the default data. */
void create_encounter_view_darkener(void)
{
    ObjectNodeHeader * object;
    ObjectPosition *axis_state;
    SpriteFrameState *data_state;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->update_callback) = darken_encounter_view_color;
        register_node(object, draw_linked_sprites);

        axis_state = object->position;
        axis_state->z.w.i = 0;
        axis_state->y.w.i = 0;
        axis_state->x.w.i = 0;

        data_state = object->sprite;
        data_state->scale_y = 0;
        data_state->scale_x = 0;
        data_state->color.c.b = 0;
        data_state->color.c.g = 0;
        data_state->color.c.r = 0;

        (*(Copy12 *)((u8 *)object + 0x48)) = D_80173B1C;
        data_state->source = (u8 *)object + 0x48;
    }
}

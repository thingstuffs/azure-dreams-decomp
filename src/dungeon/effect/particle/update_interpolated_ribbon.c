#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 pad;
} ColorEntry;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[1];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[1];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 pad_0B[1];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[9];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x58];
    u16 out1[2][3];
    u16 out2[2][3];
} ObjectPayload;

typedef struct S_func_81331914_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;
    u8 pad_14[4];
    union { s16 s; u16 u; } unk_18;
    u8 pad_1A[2];
    s16 unk_1C;
} S_func_81331914_0;

typedef struct S_func_81331914_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_func_81331914_4;

extern void register_node(void *, void *);
extern void select_record_entry_and_value(void *, void *, s32);

extern u8 ribbon_sprite_entries[];
extern u8 D_80166914[];
extern u8 D_80167C30[];
extern s16 ribbon_vertices[][8][2][3];

/* Spawn seven colored segments from interpolated vertices and advance the effect lifetime. */
void update_interpolated_ribbon(S_func_81331914_0 *state, s32 *position, S_func_81331914_4 *colors)
{
    s32 step;
    s32 vertex_index;
    s32 axis;
    s32 segment_index;
    ObjectNodeHeader *object;
    ObjectPayload *payload;
    SpriteFrameState *sprite;
    ObjectPosition *object_position;
    ColorEntry *vertex_color;
    u16 ticks_left;

    if ((state->unk_12.s == 0) &&
        (state->unk_18.s < 12)) {
        state->unk_12.u++;
    }

    step = 1;
    do {
        vertex_index = 0;
        do {
            axis = 0;
            do {
                ribbon_vertices[state->unk_1C][step][vertex_index][axis] =
                    ribbon_vertices[state->unk_1C][0][vertex_index][axis] +
                    (ribbon_vertices[state->unk_1C][7][vertex_index][axis] -
                     ribbon_vertices[state->unk_1C][0][vertex_index][axis]) *
                    step / 7;
                axis++;
            } while (axis < 3);
            vertex_index++;
        } while (vertex_index < 2);
        step++;
    } while (step < 7);

    segment_index = 0;
    do {
        object = allocate_flagged_object_node(0x212);
        if (object != 0) {
            payload = (ObjectPayload *)((u8 *)object + 0x20);
            payload->unk_18 = 1;
            payload->unk_1A = 1;
            object->unk_10 = D_80167C30;
            register_node(object, D_80166914);

            sprite = object->sprite;
            sprite->tpage_abr = 0x20;
            sprite->flags |= 0xC;

            object_position = object->position;
            object_position->x.v = position[0];
            object_position->y.v = position[1];
            vertex_color = (ColorEntry *)payload;
            object_position->z.v = position[2];

            sprite = object->sprite;
            sprite->scale_x = sprite->scale_y = 0x1000;
            sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0x80;

            for (step = 0; step < 4; step++) {
                vertex_color[step].red = colors->unk_0C;
                vertex_color[step].green = colors->unk_0D;
                vertex_color[step].blue = colors->unk_0E;
            }

            if (segment_index == 0) {
                payload->unk_00 = payload->unk_01 = payload->unk_02 =
                    payload->unk_04 = payload->unk_05 = payload->unk_06 = 0;
            }
            if (segment_index == 6) {
                payload->unk_08 = payload->unk_09 = payload->unk_0A =
                    payload->unk_0C = payload->unk_0D = payload->unk_0E = 0;
            }

            sprite->unk_06 = 0;
            select_record_entry_and_value(sprite, ribbon_sprite_entries, 0);

            vertex_index = 0;
            do {
                axis = 0;
                do {
                    ((ObjectPayload *)payload)->out1[vertex_index][axis] =
                        ribbon_vertices[state->unk_1C][segment_index][vertex_index][axis];
                    ((ObjectPayload *)payload)->out2[vertex_index][axis] =
                        ribbon_vertices[state->unk_1C][segment_index + 1][vertex_index][axis];
                    axis++;
                } while (axis < 3);
                vertex_index++;
            } while (vertex_index < 2);
        }
        segment_index++;
    } while (segment_index < 7);

    ticks_left = state->unk_18.u - 1;
    state->unk_18.u = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

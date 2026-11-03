#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/system.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct { u16 flags; } AnimationFieldView_813374E8Prefix;

#ifndef NULL
#define NULL 0
#endif



typedef struct S_8016E4E8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x5C];
    s16 unk_78;
    u8 pad_7A[0x4];
    s16 unk_7E;
    u8 pad_80[0x4];
    s16 unk_84;
    u8 pad_86[0x4];
    s16 unk_8A;
} S_8016E4E8_2;   /* part in emit_multi_form_ring_geometry */

typedef struct S_8016E4E8_4 {
    u8 pad_00[0x6];
    s16 unk_06;
    union { void * s; u8 * u; } unk_08;   /* accessed as both */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016E4E8_4;   /* effect in emit_multi_form_ring_geometry */

typedef struct S_8016E4E8_5 {
    u16 unk_00;
} S_8016E4E8_5;   /* dst_word in emit_multi_form_ring_geometry */

typedef struct S_8016E4E8_6 {
    u16 unk_00;
} S_8016E4E8_6;   /* src_word in emit_multi_form_ring_geometry */

typedef struct {
    u8 bytes[12];
} Data12;

extern void *memcpy(void *, const void *, u32);

extern u8 D_8016E450[];
extern u8 D_8016E4A4[];
extern Data12 D_80173B4C;

/* Advances the color fade and creates two rows of animated textured geometry. */
/* Fades the effect color while creating two textured rows with copied vertices and cycling texture
 * coordinates. */
void emit_multi_form_ring_geometry(MultiFormSegmentRingBody *animation, s32 *origin, SpriteFrameState *color)
{
    s32 bottom_y;
    u16 tick_count;
    s32 frame_count;
    register s32 color_index;
    s32 vertex_index;
    s32 axis;
    s32 row;
    s32 one;
    s32 top_y;
    ObjectNodeHeader *object;
    u8 *part;
    S_8016E4E8_4 *effect;
    s32 *position;
    u8 *texture;
    u8 *src_vertices;
    u8 *dst_vertices;
    u8 *src_coord;
    u8 *dst_coord;
    s32 state;

    state = animation->unk_12.s;
    switch ((u32)state) {
    case 0:
        color->color.c.r =
            (animation->unk_00.u * (50 - animation->unk_18.s)) / 10;
        color->color.c.g =
            (animation->unk_01 * (50 - animation->unk_18.s)) / 10;
        color->color.c.b =
            (animation->unk_02 * (50 - animation->unk_18.s)) / 10;
        animation->unk_18.u--;
        if (animation->unk_18.s >= 41) {
            break;
        }
        animation->unk_12.u++;
        break;

    case 2:
        animation->unk_18.u++;
        if (animation->unk_18.s < 20) {
            break;
        }
        animation->unk_18.u = 0;
        animation->unk_12.u++;
        break;

    case 3:
        animation->unk_18.u = 20;
        animation->unk_12.u++;
        break;

    case 4:
        animation->unk_18.u--;
        color->color.c.r =
            (animation->unk_00.u * animation->unk_18.s) / 20;
        color->color.c.g =
            (animation->unk_01 * animation->unk_18.s) / 20;
        color->color.c.b =
            (animation->unk_02 * animation->unk_18.s) / 20;
        if (animation->unk_18.s > 0) {
            break;
        }
        animation->unk_12.u++;
        break;

    case 5:
        (((AnimationFieldView_813374E8Prefix *)animation)[-1].flags) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    row = 0;
    one = 1;
    top_y = -0x20;
    animation->unk_1E++;
    for (;;) {
        object = allocate_flagged_object_node(0x12);
        part = NODE_BODY(object);
        if (object != NULL) {
            ((S_8016E4E8_2 *)part)->unk_18 = one;
            ((S_8016E4E8_2 *)part)->unk_1A = one;
            object->update_callback = D_8016E4A4;
            register_node(object, D_8016E450);

            effect = (S_8016E4E8_4 *)object->sprite;
            state = effect->unk_14;
            effect->unk_10 = 0x20;
            state |= 0xC;
            effect->unk_14 = state;

            position = *(s32 * *)&object->position;
            position[0] = origin[0];
            position[1] = origin[1];
            color_index = 0;
            position[2] = origin[2];
            effect = (S_8016E4E8_4 *)object->sprite;
            effect->unk_1E = 0x1000;
            effect->unk_1C = 0x1000;
            effect->unk_0E = 0x80;
            effect->unk_0D = 0x80;
            effect->unk_0C = 0x80;

            do {
                part[color_index * 4] = color->color.c.r;
                part[color_index * 4 + 1] = color->color.c.g;
                part[color_index * 4 + 2] = color->color.c.b;
                color_index++;
            } while (color_index < 4);

            if (row == one) {
                part[6] = 0;
                part[5] = 0;
                part[4] = 0;
                part[2] = 0;
                part[1] = 0;
                part[0] = 0;
            }

            effect->unk_06 = 0;
            memcpy(part + 0x28, &D_80173B4C, 12);

            vertex_index = 0;
            src_vertices = (u8 *)animation;
            dst_vertices = part;
            texture = part + 0x28;
            effect->unk_08.s = texture;
            texture[8] += animation->unk_1C * 4;
            texture = effect->unk_08.u;
            frame_count = animation->unk_1E;
            texture[9] += (frame_count & 3) << 3;

            do {
                axis = 0;
                dst_coord = dst_vertices + 0x74;
                src_coord = src_vertices + 0x74;
                do {
                    ((S_8016E4E8_5 *)dst_coord)->unk_00 = ((S_8016E4E8_6 *)src_coord)->unk_00;
                    src_coord += 2;
                    axis++;
                    dst_coord += 2;
                } while (axis < 3);
                src_vertices += 6;
                vertex_index++;
                dst_vertices += 6;
            } while (vertex_index < 4);

            ((S_8016E4E8_2 *)part)->unk_7E = top_y;
            ((S_8016E4E8_2 *)part)->unk_78 = top_y;
            bottom_y = -(row << 5);
            ((S_8016E4E8_2 *)part)->unk_8A = bottom_y;
            ((S_8016E4E8_2 *)part)->unk_84 = bottom_y;
        }
        row++;
        top_y -= 0x20;
        if (row < 2) {
            continue;
        }

        if (animation->unk_12.s < 5) {
            tick_count = animation->unk_1A.u;
            animation->unk_1A.u = tick_count + 1;
            if ((tick_count & 0xF) == 1) {
                play_sound_if_enabled(0x60E);
            }
        }

        break;
    }
}

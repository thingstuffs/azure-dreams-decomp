#include "shared/entity.h"
#include "dungeon/effect/shade.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_80025BA0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_80025BA0_1;

typedef struct S_func_80025BA0_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x18];
    s32 unk_34;
    u16 unk_38;
    u8 pad_3A[0x2];
    s32 unk_3C;
    u16 unk_40;
    u8 pad_42[0x2];
    s32 unk_44;
    u16 unk_48;
    u8 pad_4A[0x2];
    s32 unk_4C;
    u16 unk_50;
    u8 pad_52[0x2];
    s32 unk_54;
    s32 unk_58;
} S_func_80025BA0_3;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Cell;

extern void register_node(void *, void *);
extern s32 rand(void);

extern u8 D_800255E8[];

extern s16 D_80026476;
extern s32 row_quad_top_color;
extern s32 row_quad_bottom_color;
extern Cell particle_quad_vertices[];
extern Cell D_80026648[];

#define SET_COUNT_PAGE() (count_page = (u8 *)&D_80026476)
#define READ_COUNT_PAGE() (*(s16 *)count_page)

/* Spawn quad effects at cell centers with randomized motion, then clear the pending count. */
void spawn_randomized_quad_effects(void) {
    Cell *vertices;
    Cell *diagonal;
    Cell *below;
    Cell *right;
    ObjectNodeHeader *effect;
    ObjectPosition *motion;
    SpriteFrameState *angles;
    S_func_80025BA0_3 *quad_data;
    s32 quad_index;
    s32 row_start;
    s32 index_or_coord;
    s32 right_offset;
    s32 right_y;
    s32 below_y;
    s32 diagonal_y;
    s32 effect_or_x;
    s32 right_z;
    s32 below_z;
    s32 diagonal_z;
    s32 addr_or_coord;
    s32 rounded_index;
    u8 *count_page;

    for (quad_index = 0; quad_index < D_80026476; quad_index++) {
        vertices = particle_quad_vertices;
        effect = allocate_flagged_object_node(0x202);
        if (effect != NULL) {
            effect_or_x = (s32)effect;
            effect->update_callback = D_800255E8;
            register_node((void *)effect_or_x, build_sorted_effect_quads);

            row_start = quad_index & ~0xF;
            index_or_coord = (quad_index + 1) & 0xF;
            right_offset = (row_start + index_or_coord) * 8;
            right = (Cell *)((unsigned long)right_offset + (unsigned long)vertices);
            below = (Cell *)((unsigned long)((quad_index + 0x10) * 8) + (unsigned long)vertices);

            motion = effect->position;
            effect_or_x = (vertices[quad_index].x + right->x + below->x + (diagonal = &vertices[row_start + 0x10 + index_or_coord])->x) >> 2;
            right_y = (vertices[quad_index].y + right->y + below->y + diagonal->y) >> 2;
            below_y = (vertices[quad_index].z + right->z + below->z + diagonal->z) >> 2;
            motion->x.w.i = effect_or_x;
            motion->y.w.i = right_y;
            motion->z.w.i = below_y;

            motion->velocity_x = ((rand() & 0xF) - 8) << 0x10;
            motion->velocity_y = ((rand() & 0xF) - 8) << 0x10;
            motion->velocity_z = ((rand() & 0xF) - 8) << 0x10;

            angles = effect->sprite;
            angles->angle_x = (rand() & 0x1FF) - 0x100;
            angles->angle_y = (rand() & 0x1FF) - 0x100;

            quad_data = (S_func_80025BA0_3 *)((u8 *)effect + 0x20);
            quad_data->unk_1A = 0x20;
            quad_data->unk_34 = *(s32 *)&vertices[quad_index];
            quad_data->unk_38 = vertices[quad_index].z;
            quad_data->unk_3C = *(s32 *)right;
            quad_data->unk_40 = right->z;
            quad_data->unk_44 = *(s32 *)&D_80026648[quad_index];
            quad_data->unk_48 = below->z;
            quad_data->unk_4C = *(s32 *)((u8 *)D_80026648 + right_offset);
            quad_data->unk_50 = diagonal->z;

            if ((quad_index % 32) < 0x10) {
                *(s32 *)((u8 *)quad_data + 0x54) = row_quad_top_color;
                quad_data->unk_58 = row_quad_bottom_color;
            } else {
                *(s32 *)((u8 *)quad_data + 0x58) = row_quad_top_color;
                quad_data->unk_54 = row_quad_bottom_color;
            }
        }
    }
    D_80026476 = 0;
}


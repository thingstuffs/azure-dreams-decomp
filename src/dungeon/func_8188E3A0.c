#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_80025BA0_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_80025BA0_0;

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

typedef struct S_func_80025BA0_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_func_80025BA0_2;

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

typedef struct S_func_80025BA0_4 {
    u8 pad_00[0x6476];
    s16 unk_6476;
} S_func_80025BA0_4;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Cell;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);

extern u8 D_800255E8[];
extern u8 D_800259DC[];
extern s16 D_80026476;
extern s32 D_800265C0;
extern s32 D_800265C4;
extern Cell D_800265C8[];
extern Cell D_80026648[];

#ifdef NON_MATCHING
#define SET_COUNT_PAGE() (count_page = (u8 *)&D_80026476)
#define READ_COUNT_PAGE() (*(s16 *)count_page)
#else
#define SET_COUNT_PAGE() (addr_or_coord = 0x80020000)
#define READ_COUNT_PAGE() ((S_func_80025BA0_4 *)addr_or_coord)->unk_6476
#endif

/* Spawn quad effects at cell centers with randomized motion, then clear the pending count. */
void func_80025BA0(void) {
    Cell *vertices;
    Cell *diagonal;
    Cell *below;
    Cell *right;
    S_func_80025BA0_0 *effect;
    S_func_80025BA0_1 *motion;
    S_func_80025BA0_2 *angles;
    S_func_80025BA0_3 *quad_data;
    s32 quad_index;
    s32 row_start;
    register s32 index_or_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it recolours the column index ($3 -> $2, local-alloc scan order); the source shape that makes it unnecessary has not been found */
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
#ifdef NON_MATCHING
    u8 *count_page;
#endif

    for (quad_index = 0; quad_index < D_80026476; quad_index++) {
        vertices = D_800265C8;
        effect = func_8003FC64(0x202);
        if (effect != NULL) {
            effect_or_x = (s32)effect;
            effect->unk_10 = D_800255E8;
            func_8004491C((void *)effect_or_x, D_800259DC);

            row_start = quad_index & ~0xF;
            index_or_coord = (quad_index + 1) & 0xF;
            right_offset = (row_start + index_or_coord) * 8;
            right = (Cell *)((unsigned long)right_offset + (unsigned long)vertices);
            below = (Cell *)((unsigned long)((quad_index + 0x10) * 8) + (unsigned long)vertices);
            diagonal = (Cell *)((unsigned long)((row_start + 0x10 + index_or_coord) * 8) + (unsigned long)vertices);

            motion = effect->unk_08;
            effect_or_x = (vertices[quad_index].x + right->x + below->x + diagonal->x) >> 2;
            right_y = (vertices[quad_index].y + right->y + below->y + diagonal->y) >> 2;
            below_y = (vertices[quad_index].z + right->z + below->z + diagonal->z) >> 2;
            motion->unk_02 = effect_or_x;
            motion->unk_06 = right_y;
            motion->unk_0A = below_y;

            motion->unk_0C = ((func_80069EF8() & 0xF) - 8) << 0x10;
            motion->unk_10 = ((func_80069EF8() & 0xF) - 8) << 0x10;
            motion->unk_14 = ((func_80069EF8() & 0xF) - 8) << 0x10;

            angles = effect->unk_0C;
            angles->unk_16 = (func_80069EF8() & 0x1FF) - 0x100;
            angles->unk_18 = (func_80069EF8() & 0x1FF) - 0x100;

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
                *(s32 *)((u8 *)quad_data + 0x54) = D_800265C0;
                quad_data->unk_58 = D_800265C4;
            } else {
                *(s32 *)((u8 *)quad_data + 0x58) = D_800265C0;
                quad_data->unk_54 = D_800265C4;
            }
        }
    }
    D_80026476 = 0;
}

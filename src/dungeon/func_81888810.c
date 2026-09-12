#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81888810_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_81888810_0;

typedef struct S_func_81888810_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81888810_1;

typedef struct S_func_81888810_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_func_81888810_2;

typedef struct S_func_81888810_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0x14];
    s32 unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    s32 unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    s32 unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_func_81888810_3;

typedef struct S_func_81888810_4 {
    u8 pad_00[0x632A];
    s16 unk_632A;
} S_func_81888810_4;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Cell;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern u8 D_80025A58[];
extern u8 D_80025E4C[];
extern s16 D_8002632A;
extern s32 D_80026470;
extern s32 D_80026474;
extern Cell D_80026478[];
extern Cell D_800264F8[];

#ifdef NON_MATCHING
#define SET_COUNT_PAGE() (count_page = (u8 *)&D_8002632A)
#define READ_COUNT_PAGE() (*(s16 *)count_page)
#else
#define SET_COUNT_PAGE() (addr_or_coord = 0x80020000)
#define READ_COUNT_PAGE() (((S_func_81888810_4 *)addr_or_coord)->unk_632A)
#endif

/* Create quad fragments from the vertex grid with randomized motion and rotation. */
void func_80026010(void) {
    Cell *vertices;
    Cell *lower_right;
    Cell *lower_left;
    Cell *upper_right;
    S_func_81888810_0 *fragment;
    S_func_81888810_1 *motion;
    S_func_81888810_2 *angles;
    S_func_81888810_3 *quad;
    s32 quad_index;
    s32 row_start;
    register s32 column_or_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 right_offset;
    s32 upper_right_y;
    s32 lower_left_y;
    s32 lower_right_y;
    register s32 object_or_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 upper_right_z;
    s32 lower_left_z;
    s32 lower_right_z;
    register s32 addr_or_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 biased_index;
    s32 quad_count;
#ifdef NON_MATCHING
    u8 *count_page;
#endif

    quad_index = 0;
    if (D_8002632A > 0) {
        vertices = D_80026478;
        do {
            fragment = func_8003FC64(0x202);
            SET_COUNT_PAGE();
            if (fragment != NULL) {
                object_or_x = (s32)fragment;
                addr_or_coord = (s32)D_80025A58;
                fragment->unk_10 = (void *)addr_or_coord;
                func_8004491C((void *)object_or_x, D_80025E4C);

                row_start = quad_index & ~0xF;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                column_or_coord = (quad_index + 1) & 0xF;
                right_offset = (row_start + column_or_coord) * 8;
                upper_right = (Cell *)((unsigned long)right_offset + (unsigned long)vertices);
                lower_left = (Cell *)((unsigned long)((quad_index + 0x10) * 8) + (unsigned long)vertices);
                ASM_KEEP(column_or_coord);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                column_or_coord += 0x10;
                lower_right = (Cell *)((unsigned long)((row_start + column_or_coord) * 8) + (unsigned long)vertices);

                object_or_x = vertices[quad_index].x;
                addr_or_coord = upper_right->x;
                column_or_coord = lower_right->x;
                motion = fragment->unk_08;
                upper_right_y = upper_right->y;
                lower_left_y = lower_left->y;
                lower_right_y = lower_right->y;
                upper_right_z = upper_right->z;
                lower_left_z = lower_left->z;
                object_or_x += addr_or_coord;
                addr_or_coord = lower_left->x;
                lower_right_z = lower_right->z;
                object_or_x += addr_or_coord;
                object_or_x += column_or_coord;
                addr_or_coord = vertices[quad_index].y;
                column_or_coord = vertices[quad_index].z;
                object_or_x >>= 2;
                motion->unk_02 = object_or_x;
                addr_or_coord = (addr_or_coord + upper_right_y + lower_left_y + lower_right_y) >> 2;
                motion->unk_06 = addr_or_coord;
                column_or_coord = (column_or_coord + upper_right_z + lower_left_z + lower_right_z) >> 2;
                motion->unk_0A = column_or_coord;

                motion->unk_0C = ((rand() & 0xF) - 8) << 0x10;
                motion->unk_10 = ((rand() & 0xF) - 8) << 0x10;
                motion->unk_14 = ((rand() & 0xF) - 8) << 0x10;

                angles = fragment->unk_0C;
                angles->unk_16 = (rand() & 0x1FF) - 0x100;
                angles->unk_18 = (rand() & 0x1FF) - 0x100;

                quad = (S_func_81888810_3 *)((u8 *)fragment + 0x20);
                quad->unk_1A = 0x20;
                quad->unk_30 = *(s32 *)&vertices[quad_index];
                quad->unk_34 = vertices[quad_index].z;
                quad->unk_38 = *(s32 *)upper_right;
                quad->unk_3C = upper_right->z;
                quad->unk_40 = *(s32 *)&D_800264F8[quad_index];
                quad->unk_44 = lower_left->z;
                quad->unk_48 = *(s32 *)((u8 *)D_800264F8 + right_offset);
                quad->unk_4C = lower_right->z;

                biased_index = quad_index;
                if (quad_index < 0) {
                    biased_index = quad_index + 0x1F;
                }
                if ((quad_index - ((biased_index >> 5) << 5)) < 0x10) {
                    *(s32 *)((u8 *)quad + 0x50) = D_80026470;
                    quad->unk_54 = D_80026474;
                } else {
                    *(s32 *)((u8 *)quad + 0x54) = D_80026470;
                    quad->unk_50 = D_80026474;
                }
                SET_COUNT_PAGE();
            }
            quad_count = READ_COUNT_PAGE();
               /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            quad_index++;
        } while (quad_index < quad_count);
    }
    *(volatile s16 *)&D_8002632A = 0;
}

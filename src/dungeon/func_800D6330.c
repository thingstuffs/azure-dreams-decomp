#include "common.h"

extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064CF0(void *matrix);
extern void func_80064D80(void *values);
extern void func_80065450(void *vertex, void *coordinates, s32 *result);
extern void func_80065820(void *transform_fields, void *matrix);
extern void func_80065AB0(s16 value, void *matrix, s32 diagonal_value, s32 last_column_index_index);
extern void func_80065C50(s16 value, void *matrix);
extern void func_80065DF0(s16 value, void *matrix);

typedef struct {
    /* 0x00 */ s32 *unk00;
    /* 0x04 */ s16 *unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u16 unk1A;
} Struct_800D6330;

/* Transforms source_vertices using the selected rotation matrix and stores their coordinates. */
void func_800DBA90(Struct_800D6330 *transform) {
    union {
        s16 rotation_matrix[9];
        struct {
            s8 pad1[0x14];
            s32 input_0;
            s32 input_1;
            s32 input_2;
            s32 output_x;
            s32 output_y;
            s32 output_z;
        } s;
    } scratch;
    s32 column_index;
    s16 *matrix_row;
    s16 *row_start;
    s16 *matrix_cell;
    s32 index;
    s32 last_column_index;
    s32 diagonal_value;
    s32 vertex_byte_offset = 0;
    s32 *source_vertices;
    void *output_coordinates;

    func_800649A0();
    scratch.s.input_0 = transform->unk10;
    scratch.s.input_1 = transform->unk12;
    scratch.s.input_2 = transform->unk14;
    func_80064D80(scratch.rotation_matrix);
    if (transform->unk1A == 0) {
        func_80065820((s8 *) transform + 8, scratch.rotation_matrix);
    } else {
        index = 2;
        if (transform->unk1A != 0x8000) {
            last_column_index = index;
            diagonal_value = 0x1000;
            matrix_row = scratch.rotation_matrix + 6;
            do {
                column_index = last_column_index;
                row_start = matrix_row;
                do {
                    matrix_cell = (s16 *) ((column_index << 1) + (u32) row_start);
                    if (index == column_index) {
                        *matrix_cell = diagonal_value;
                    } else {
                        *matrix_cell = 0;
                    }
                    column_index--;
                } while (column_index >= 0);
                index--;
                matrix_row -= 3;
            } while (index >= 0);
            if (transform->unk1A == 1) {
                func_80065AB0(transform->unk08, scratch.rotation_matrix, diagonal_value, last_column_index);
                func_80065C50(transform->unk0A, scratch.rotation_matrix);
                func_80065DF0(transform->unk0C, scratch.rotation_matrix);
            }
        }
    }
    func_80064CF0(scratch.rotation_matrix);
    index = 0;
    if (transform->unk18 > 0) {
        output_coordinates = &scratch.s.output_x;
        do {
            vertex_byte_offset = index * 8;
            source_vertices = transform->unk00;
            func_80065450((s8 *) source_vertices + vertex_byte_offset, output_coordinates, &column_index);
            *(u16 *) ((s8 *) transform->unk04 + index * 8) = *(u16 *) &scratch.s.output_x;
            *(u16 *) ((s8 *) transform->unk04 + index * 8 + 2) = *(u16 *) &scratch.s.output_y;
            vertex_byte_offset = (s32)transform->unk04 + vertex_byte_offset;
            *(u16 *) (vertex_byte_offset + 4) = *(u16 *) &scratch.s.output_z;
            index++;
            if (index >= transform->unk18) {
                break;
            }
            output_coordinates = &scratch.s.output_x;
        } while (1);
    }
    func_80064A40();
}

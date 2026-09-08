#include "common.h"

extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064CF0(void *arg0);
extern void func_80064D80(void *arg0);
extern void func_80065450(void *arg0, void *arg1, s32 *arg2);
extern void func_80065820(void *arg0, void *arg1);
extern void func_80065AB0(s16 arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_80065C50(s16 arg0, void *arg1);
extern void func_80065DF0(s16 arg0, void *arg1);

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

/* Transforms vertices using the selected rotation matrix and stores their coordinates. */
void func_800DBA90(Struct_800D6330 *transform) {
    union {
        s16 sp10[9];
        struct {
            s8 pad1[0x14];
            s32 sp24;
            s32 sp28;
            s32 sp2C;
            s32 sp30;
            s32 sp34;
            s32 sp38;
        } s;
    } scratch;
    s32 column_flags;
    s16 *matrix_row;
    s16 *row_base;
    s16 *matrix_cell;
    s32 row_vertex_index;
    s32 last_column;
    s32 unit_scale;
    s32 vertex_offset;
    s32 *vertices;
    void *transformed;

    func_800649A0();
    scratch.s.sp24 = transform->unk10;
    scratch.s.sp28 = transform->unk12;
    scratch.s.sp2C = transform->unk14;
    func_80064D80(scratch.sp10);
    if (transform->unk1A == 0) {
        func_80065820((s8 *) transform + 8, scratch.sp10);
        goto post_init;
    }
    row_vertex_index = 2;
    if (transform->unk1A != 0x8000) {
        last_column = row_vertex_index;
        unit_scale = 0x1000;
        matrix_row = scratch.sp10 + 6;
        do {
            column_flags = last_column;
            row_base = matrix_row;
            do {
                matrix_cell = (s16 *) ((column_flags << 1) + (u32) row_base);
                if (row_vertex_index == column_flags) {
                    *matrix_cell = unit_scale;
                } else {
                    *matrix_cell = 0;
                }
                column_flags--;
            } while (column_flags >= 0);
            row_vertex_index--;
            matrix_row -= 3;
        } while (row_vertex_index >= 0);
        if (transform->unk1A == 1) {
            func_80065AB0(transform->unk08, scratch.sp10, unit_scale, last_column);
            func_80065C50(transform->unk0A, scratch.sp10);
            func_80065DF0(transform->unk0C, scratch.sp10);
        }
    }
post_init:
    func_80064CF0(scratch.sp10);
    row_vertex_index = 0;
    if (transform->unk18 > 0) {
        do {
            transformed = &scratch.s.sp30;
            ASM_KEEP(transformed);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            vertex_offset = row_vertex_index * 8;
            vertices = transform->unk00;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_80065450((s8 *) vertices + vertex_offset, transformed, &column_flags);
            *(u16 *) ((s8 *) transform->unk04 + row_vertex_index * 8) = *(u16 *) &scratch.s.sp30;
            *(u16 *) ((s8 *) transform->unk04 + row_vertex_index * 8 + 2) = *(u16 *) &scratch.s.sp34;
            *(u16 *) ((s8 *) transform->unk04 + row_vertex_index * 8 + 4) = *(u16 *) &scratch.s.sp38;
            row_vertex_index++;
        } while (row_vertex_index < transform->unk18);
    }
    func_80064A40();
}

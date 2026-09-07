#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CE4E8_0 {
    s16 unk_00;
    s16 unk_02;
    u8 pad_04[0x64];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    union { u16 s; s16 u; } unk_6E;   /* accessed as both */
} S_800CE4E8_0;   /* temp_s3 in func_800CE4E8 */

typedef struct S_800CE4E8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CE4E8_1;   /* global_base in func_800CE4E8 */



typedef struct {
    u8 pad_00[0x10];
    void *field_10;
    u8 pad_14[0xC];
    s16 field_20;
    s16 field_22;
} DungeonObject;

extern void *func_8003FC64(s32);
extern void func_800419EC(s32, s32);
extern s32 func_800A6DA4(s32, s32);
extern s32 func_800BCA68(s32, s32);

extern u8 D_800CE028[];
extern s32 D_80083460;
extern s32 D_800E296C;

/* Creates a dungeon object with two 5x5 value grids and sets its effect flags. */
s32 func_800CE4E8(s32 center_x, s32 center_y, s16 unused_value, void *unused_data, s32 reverse_offset)
{
    u16 offset_mode;
    s32 reverse_flag;
    s32 col;
    s32 row;
    s32 tile_value;
    s32 rand_min;
    s32 rand_max;
    s32 origin_x;
    s32 origin_y;
    u16 *base_cell;
    u16 *offset_cell;
    s32 random_offset;
    register u8 *base_row ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u8 *grid_data;
    DungeonObject *object;
    u8 *row_data;
    u8 *global_base;
    u8 *row_base;

    object = func_8003FC64(2);
    offset_mode = reverse_offset;
    if (object != NULL) {
        row = 0;
        reverse_flag = (s16)reverse_offset;
        grid_data = (u8 *)&object->field_20;
        row_data = grid_data;
        object->field_10 = D_800CE028;
        object->field_20 = center_x - 2;
        ((S_800CE4E8_0 *)grid_data)->unk_02 = center_y - 2;
        do {
            col = 0;
            row_base = row_data;
            offset_cell = (u16 *)(row_data + 0x36);
            do {
                origin_x = ((S_800CE4E8_0 *)grid_data)->unk_00;
                origin_y = ((S_800CE4E8_0 *)grid_data)->unk_02;
                tile_value = func_800BCA68(
                    ((col + origin_x) << 6) & 0xFFC0,
                    ((row + origin_y) << 6) & 0xFFC0);
                rand_min = 1;
                rand_max = 3;
                ASM_KEEP(rand_min);   /* MATCH pin: load-bearing for the whole function shape */
                base_row = row_base + 4;
                base_cell = (u16 *)((unsigned long)(col * 2) +
                    (unsigned long)base_row);
                *base_cell = -tile_value;
                random_offset = func_800A6DA4(rand_min, rand_max);
                random_offset = (random_offset & 0xFFFF) << 5;
                *offset_cell = random_offset;
                if (reverse_flag != 0) {
                    *offset_cell = -random_offset;
                }
                col++;
                *offset_cell += *base_cell;
                offset_cell++;
            } while (col < 5);
            row++;
            row_data += 0xA;
        } while (row < 5);

        ((S_800CE4E8_0 *)grid_data)->unk_6C = 0x10;
        ((S_800CE4E8_0 *)grid_data)->unk_68 = 0x20;
        ((S_800CE4E8_0 *)grid_data)->unk_6E.s = offset_mode;
        func_800419EC(0x20, 8);

        if (((S_800CE4E8_0 *)grid_data)->unk_6E.u == 0) {
            D_800E296C |= 0x80080000;
        } else {
            D_800E296C |= 0x40080000;
        }
        global_base = (u8 *)&D_80083460;
        ((S_800CE4E8_1 *)global_base)->unk_0A++;
    }
    return (s32)object;
}

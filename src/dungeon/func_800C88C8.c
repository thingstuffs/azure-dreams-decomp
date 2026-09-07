#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct {
    s16 x;
    s16 y;
    s16 initial[25];
    s16 target[25];
    s16 timer;
    s16 state;
    s16 delay;
    s16 flag;
} DungeonEffect;

typedef struct {
    u16 unused;
    s16 height;
    u16 other;
} DungeonTile;

typedef struct {
    DungeonTile *tiles;
    u8 pad_04[0x10];
    s16 row_shift;
} DungeonGrid;

typedef struct {
    u16 field_00;
    u16 flags;
    u8 pad_04[6];
    u16 count;
} DungeonState;

extern u8 D_8008333C[32];
extern DungeonState D_80083460;
extern u32 D_800E296C;
extern u32 D_800814A0;

extern void func_8009D6F4(void);
extern void func_800A56E0(s32);
extern void func_800CDE0C(void);
extern void func_800CDE40(s32, s32, s32);
extern void func_800CDF40(s32, s32, s32);
extern void func_800419EC(s32, s32);

void func_800CE028(DungeonEffect *arg0) {
    s16 *var_s2;
    s16 *var_s2_3;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v1;
    s32 temp_a2;
    s32 temp_a2_3;
    DungeonGrid *grid;
    DungeonTile *tiles;
    s32 var_a0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 temp_y;
    s32 temp_shift;
    s32 temp_x;
    u16 *var_s2_2;
    u16 *var_s2_4;
    u16 temp_a2_2;
    u16 temp_a2_4;
    u16 temp_v0_2;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *var_s4;
    u8 *var_s4_2;
    u8 *var_s4_3;
    u8 *var_s4_4;

    temp_v1 = arg0->state;
    if (temp_v1 == 0) {
        grid = (DungeonGrid *)D_8008333C;
        tiles = grid->tiles;
        var_s1 = 0;
        var_s4 = arg0;
        do {
            var_s0 = 0;
            var_s2 = (s16 *)(var_s4 + 0x36);
loop_3:
            temp_y = arg0->y;
            temp_shift = grid->row_shift;
            temp_x = arg0->x;
            temp_a2 = (s32)(*var_s2 - tiles[((var_s1 + temp_y) << temp_shift) + temp_x + var_s0].height) / arg0->timer;
            var_s2++;
            tiles[((var_s1 + temp_y) << temp_shift) + temp_x + var_s0].height =
                (u16)tiles[((var_s1 + temp_y) << temp_shift) + temp_x + var_s0].height + temp_a2;
            func_800CDE40((s16)((u16)arg0->x + var_s0),
                          (s16)((u16)arg0->y + var_s1),
                          (s16)-temp_a2);
            var_s0++;
            if (var_s0 < 5) {
                goto loop_3;
            }
            var_s1++;
            var_s4 += 0xA;
        } while (var_s1 < 5);

        func_800CDE0C();
        if (!((u16)arg0->timer & 7)) {
            func_800A56E0(0x818);
        }
        temp_v0 = (u16)arg0->timer - 1;
        arg0->timer = temp_v0;
        var_s1 = 0;
        if ((temp_v0 << 16) <= 0) {
            var_s4_2 = arg0;
            do {
                var_s0_2 = 0;
                var_s2_2 = (u16 *)(var_s4_2 + 0x36);
loop_10:
                temp_y = arg0->y;
                temp_shift = grid->row_shift;
                temp_x = arg0->x;
                tiles[((var_s1 + temp_y) << temp_shift) + temp_x + var_s0_2].height = *var_s2_2;
                temp_a2_2 = *var_s2_2;
                var_s2_2++;
                func_800CDF40((s16)((u16)arg0->x + var_s0_2),
                                  (s16)((u16)arg0->y + var_s1),
                                  (s16)-temp_a2_2);
                var_s0_2++;
                if (var_s0_2 < 5) {
                    goto loop_10;
                }
                var_s1++;
                var_s4_2 += 0xA;
            } while (var_s1 < 5);
            func_8009D6F4();
            D_80083460.count--;
            D_800E296C &= 0xFFF7FFFF;
            arg0->state++;
            goto end;
        }
    } else if (temp_v1 == 1) {
        if (D_80083460.flags & 0x10) {
            temp_v0_2 = (u16)arg0->delay - 1;
            arg0->delay = temp_v0_2;
            if ((temp_v0_2 << 16) <= 0) {
                D_80083460.count++;
                arg0->timer = 0x20;
                func_800419EC(0x20, 8);
                arg0->state++;
                D_800E296C |= 0x80000;
            }
        }
    } else {
        grid = (DungeonGrid *)D_8008333C;
        tiles = grid->tiles;
        var_s1_3 = 0;
        var_s4_3 = arg0;
        do {
            var_s0_3 = 0;
            var_s2_3 = (s16 *)(var_s4_3 + 4);
loop_21:
            temp_y = arg0->y;
            temp_shift = grid->row_shift;
            temp_x = arg0->x;
            temp_a2_3 = (s32)(*var_s2_3 - tiles[((var_s1_3 + temp_y) << temp_shift) + temp_x + var_s0_3].height) / arg0->timer;
            var_s2_3++;
            tiles[((var_s1_3 + temp_y) << temp_shift) + temp_x + var_s0_3].height =
                (u16)tiles[((var_s1_3 + temp_y) << temp_shift) + temp_x + var_s0_3].height + temp_a2_3;
            func_800CDE40((s16)((u16)arg0->x + var_s0_3),
                          (s16)((u16)arg0->y + var_s1_3),
                          (s16)-temp_a2_3);
            var_s0_3++;
            if (var_s0_3 < 5) {
                goto loop_21;
            }
            var_s1_3++;
            var_s4_3 += 0xA;
        } while (var_s1_3 < 5);

        if (!((u16)arg0->timer & 7)) {
            func_800A56E0(0x818);
        }
        temp_v0_3 = (u16)arg0->timer - 1;
        arg0->timer = temp_v0_3;
        if ((temp_v0_3 << 16) <= 0) {
            var_s1_3 = 0;
            var_s4_4 = arg0;
            do {
                var_s0_4 = 0;
                var_s2_4 = (u16 *)(var_s4_4 + 4);
loop_28:
                temp_y = arg0->y;
                temp_shift = grid->row_shift;
                temp_x = arg0->x;
                tiles[((var_s1_3 + temp_y) << temp_shift) + temp_x + var_s0_4].height = *var_s2_4;
                temp_a2_4 = *var_s2_4;
                var_s2_4++;
                var_a0 = (s16)((u16)arg0->x + var_s0_4);
                func_800CDF40(var_a0,
                                  (s16)((u16)arg0->y + var_s1_3),
                                  (s16)-temp_a2_4);
                var_s0_4++;
                if (var_s0_4 < 5) {
                    goto loop_28;
                }
                var_s1_3++;
                var_s4_4 += 0xA;
            } while (var_s1_3 < 5);
            func_8009D6F4();
            D_80083460.count--;
            var_a0 = 0xBFF70000;
            if (arg0->flag == 0) {
                var_a0 = 0x7FF70000;
            }
            var_a0 |= 0xFFFF;
            D_800E296C &= var_a0;
            FIELD(arg0, u16 *, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        func_800CDE0C();
    }
end:
    return;
}

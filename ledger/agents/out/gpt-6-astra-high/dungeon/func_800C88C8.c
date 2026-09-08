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

/* Animate a 5x5 tile patch to target heights, wait, then restore its initial heights. */
void func_800CE028(DungeonEffect *effect) {
    s16 *target_ptr;
    s16 *initial_ptr;
    s16 target_ticks;
    s16 restore_ticks;
    s16 state;
    s32 target_step;
    s32 restore_step;
    DungeonGrid *grid;
    DungeonTile *tiles;
    s32 x_or_mask;
    s32 target_col;
    s32 snap_target_col;
    s32 restore_col;
    s32 snap_initial_col;
    s32 target_row;
    s32 restore_row;
    s32 origin_y;
    s32 row_shift;
    s32 origin_x;
    u16 *snap_target_ptr;
    u16 *snap_initial_ptr;
    u16 target_height;
    u16 initial_height;
    u16 delay_ticks;
    u8 *target_row_base;
    u8 *snap_target_base;
    u8 *initial_row_base;
    u8 *snap_initial_base;

    state = effect->state;
    if (state == 0) {
        grid = (DungeonGrid *)D_8008333C;
        tiles = grid->tiles;
        target_row = 0;
        target_row_base = effect;
        do {
            target_col = 0;
            target_ptr = (s16 *)(target_row_base + 0x36);
step_target_tile:
            origin_y = effect->y;
            row_shift = grid->row_shift;
            origin_x = effect->x;
            target_step = (s32)(*target_ptr - tiles[((target_row + origin_y) << row_shift) + origin_x + target_col].height) / effect->timer;
            target_ptr++;
            tiles[((target_row + origin_y) << row_shift) + origin_x + target_col].height =
                (u16)tiles[((target_row + origin_y) << row_shift) + origin_x + target_col].height + target_step;
            func_800CDE40((s16)((u16)effect->x + target_col),
                          (s16)((u16)effect->y + target_row),
                          (s16)-target_step);
            target_col++;
            if (target_col < 5) {
                goto step_target_tile;
            }
            target_row++;
            target_row_base += 0xA;
        } while (target_row < 5);

        func_800CDE0C();
        if (!((u16)effect->timer & 7)) {
            func_800A56E0(0x818);
        }
        target_ticks = (u16)effect->timer - 1;
        effect->timer = target_ticks;
        target_row = 0;
        if ((target_ticks << 16) <= 0) {
            snap_target_base = effect;
            do {
                snap_target_col = 0;
                snap_target_ptr = (u16 *)(snap_target_base + 0x36);
snap_target_tile:
                origin_y = effect->y;
                row_shift = grid->row_shift;
                origin_x = effect->x;
                tiles[((target_row + origin_y) << row_shift) + origin_x + snap_target_col].height = *snap_target_ptr;
                target_height = *snap_target_ptr;
                snap_target_ptr++;
                func_800CDF40((s16)((u16)effect->x + snap_target_col),
                                  (s16)((u16)effect->y + target_row),
                                  (s16)-target_height);
                snap_target_col++;
                if (snap_target_col < 5) {
                    goto snap_target_tile;
                }
                target_row++;
                snap_target_base += 0xA;
            } while (target_row < 5);
            func_8009D6F4();
            D_80083460.count--;
            D_800E296C &= 0xFFF7FFFF;
            effect->state++;
            goto end;
        }
    } else if (state == 1) {
        if (D_80083460.flags & 0x10) {
            delay_ticks = (u16)effect->delay - 1;
            effect->delay = delay_ticks;
            if ((delay_ticks << 16) <= 0) {
                D_80083460.count++;
                effect->timer = 0x20;
                func_800419EC(0x20, 8);
                effect->state++;
                D_800E296C |= 0x80000;
            }
        }
    } else {
        grid = (DungeonGrid *)D_8008333C;
        tiles = grid->tiles;
        restore_row = 0;
        initial_row_base = effect;
        do {
            restore_col = 0;
            initial_ptr = (s16 *)(initial_row_base + 4);
step_initial_tile:
            origin_y = effect->y;
            row_shift = grid->row_shift;
            origin_x = effect->x;
            restore_step = (s32)(*initial_ptr - tiles[((restore_row + origin_y) << row_shift) + origin_x + restore_col].height) / effect->timer;
            initial_ptr++;
            tiles[((restore_row + origin_y) << row_shift) + origin_x + restore_col].height =
                (u16)tiles[((restore_row + origin_y) << row_shift) + origin_x + restore_col].height + restore_step;
            func_800CDE40((s16)((u16)effect->x + restore_col),
                          (s16)((u16)effect->y + restore_row),
                          (s16)-restore_step);
            restore_col++;
            if (restore_col < 5) {
                goto step_initial_tile;
            }
            restore_row++;
            initial_row_base += 0xA;
        } while (restore_row < 5);

        if (!((u16)effect->timer & 7)) {
            func_800A56E0(0x818);
        }
        restore_ticks = (u16)effect->timer - 1;
        effect->timer = restore_ticks;
        if ((restore_ticks << 16) <= 0) {
            restore_row = 0;
            snap_initial_base = effect;
            do {
                snap_initial_col = 0;
                snap_initial_ptr = (u16 *)(snap_initial_base + 4);
snap_initial_tile:
                origin_y = effect->y;
                row_shift = grid->row_shift;
                origin_x = effect->x;
                tiles[((restore_row + origin_y) << row_shift) + origin_x + snap_initial_col].height = *snap_initial_ptr;
                initial_height = *snap_initial_ptr;
                snap_initial_ptr++;
                x_or_mask = (s16)((u16)effect->x + snap_initial_col);
                func_800CDF40(x_or_mask,
                                  (s16)((u16)effect->y + restore_row),
                                  (s16)-initial_height);
                snap_initial_col++;
                if (snap_initial_col < 5) {
                    goto snap_initial_tile;
                }
                restore_row++;
                snap_initial_base += 0xA;
            } while (restore_row < 5);
            func_8009D6F4();
            D_80083460.count--;
            x_or_mask = 0xBFF70000;
            if (effect->flag == 0) {
                x_or_mask = 0x7FF70000;
            }
            x_or_mask |= 0xFFFF;
            D_800E296C &= x_or_mask;
            FIELD(effect, u16 *, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        func_800CDE0C();
    }
end:
    return;
}

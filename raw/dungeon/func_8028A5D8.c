#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 value;
} DungeonRect;

typedef struct {
    s16 unused[10];
    s16 stride;
} DungeonState;

typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} DungeonCell;

typedef struct {
    u8 unused[0x146E];
    s16 level;
} DungeonPage;

extern DungeonState D_8008333C;
extern DungeonCell D_800EA000[];

extern void func_8001D900(void) __attribute__((noreturn));
extern void func_8001D920(void) __attribute__((noreturn));


extern void func_8001D9CC(s16 x0, s16 y0, s16 x1, s16 y1, s16 value);
extern void func_8001DD08(DungeonCell *cell, s16 value);
extern void func_8001DD48(DungeonCell *cell, s16 value);
extern s32 func_800A6D30(void);

void func_8001D5D8(DungeonRect *arg0) {
    register u32 value = arg0->value;
    s16 x0;
    u16 y0;
    u16 width;
    u16 height;
    u16 x1;
    s16 y1;
    s16 x;
    s16 y;
    s16 start_x;
    s16 start_y;
    s16 current_x;
    s32 attempts;
    s16 x_count;
    s16 y_count;
    s16 remaining_x;
    s16 remaining_y;
    s16 signed_width;
    s16 signed_height;
    s32 area;
    register s32 attempt_init ASM_REG("$4");
    s16 flag0;
    s16 flag1;
    register s16 fill_value ASM_REG("$8");
    register s32 value_40_shift ASM_REG("$18");
    DungeonCell *cell;
    s32 row;
    s32 raw_bound;
    register u32 dead_page ASM_REG("$2") = 0x80080000;
    DungeonState *page = &D_8008333C;

    ASM_KEEP(dead_page);
    ASM_KEEP_NV(value);
    y0 = arg0->y;
    start_y = y0;
    fill_value = value - 0x80;
    x0 = arg0->x;
    width = arg0->width;
    height = arg0->height;
    x1 = x0 + width;
    y1 = y0 + height;

    if ((s16)y0 < (s16)y1) {
        do {
            start_x = x0;
            if (((s32)(s16)x0 << 16) <
                (raw_bound = (s32)(s16)x1 << 16)) {
                s32 signed_row;
                s32 signed_bound;

                ASM_SCHED_BARRIER();
                signed_row = (s16)start_y;
                signed_bound = raw_bound >> 16;

                do {
                    s16 next_col;

                    dead_page = (u32)(u16)start_x << 16;
                    next_col = start_x + 1;
                    start_x = next_col;
                    cell = &D_800EA000[
                        (signed_row << page->stride) +
                        ((s32)dead_page >> 16)];
                    cell->kind = 25;
                    cell->value = fill_value;
                    cell->flags = 6;
                } while ((s16)start_x < signed_bound);
            }
            start_y++;
        } while ((s16)start_y < (s16)y1);
    }
    flag0 = func_800A6D30() & 1;
    signed_width = (s16)width;
    signed_height = (s16)height;
    area = signed_width + signed_height;

    if (area < 0) {
        area += 3;
    }
    attempt_init = area >> 2;
    {
        DungeonPage *level_page = (DungeonPage *)0x80080000;

        ASM_KEEP_NV(level_page);
        if (level_page->level < 5) {
            attempt_init = area >> 4;
        }
    }
    attempts = attempt_init;
    if (attempt_init > 0) {
        do {
            x = (s16)x0 + ((func_800A6D30() & 0xFFFF) % signed_width);
            y = (s16)y0 + ((func_800A6D30() & 0xFFFF) % signed_height);
            start_x = x;
            start_y = y;
            x_count = ((signed_width - (x - (s16)x0)) / 2 +
                (func_800A6D30() & 7)) - 4;
            y_count = ((signed_height - (y - (s16)y0)) / 2 +
                (func_800A6D30() & 7)) - 4;
            flag1 = (func_800A6D30() & 7) != 0;

            remaining_y = y_count;
            if (y_count > 0) {
                do {
                    if (start_y < (s16)y1) {
                        remaining_x = x_count;
                        current_x = start_x;

                        if (remaining_x > 0) {
                            register s32 current_flag ASM_REG("$19");

                            register s32 val_40 ASM_REG("$2");

                            row = start_y;
                            current_flag = flag1;
                            val_40 = value - 0x40;
                            value_40_shift = val_40 << 16;
                            do {
                                if (current_x < (s16)x1) {
                                    cell = &D_800EA000[
                                        (row << D_8008333C.stride) + current_x];
                                    if (flag0 != 0) {
                                        if (current_flag != 0) {
                                            func_8001DD08(cell, value_40_shift >> 16);
                                        } else {
                                            register DungeonCell *tail_cell ASM_REG("$4") = cell;
                                            register s32 tail_value ASM_REG("$5") = value - 0xC0;
                                            ASM_TAILSLOT_PIN(tail_value);
                                            func_8001D900();
                                        }
                                    } else {
                                        if (current_flag != 0) {
                                            register u16 tail_remaining ASM_REG("$2");
                                            func_8001DD48(cell, (s16)(value - 0xC0));
                                            ASM_USE_NV(current_x);
                                            tail_remaining = remaining_x - 1;
                                            ASM_TAILSLOT_PIN(tail_remaining);
                                            func_8001D920();
                                        } else {
                                            func_8001DD08(cell, value_40_shift >> 16);
                                        }
                                    }
                                }
                                remaining_x--;
                                current_x++;
                            } while (remaining_x > 0);
                        }
                    }
                    remaining_y--;
                    start_y++;
                } while (remaining_y > 0);
            }
            attempts--;
        } while (attempts > 0);
    }
    ASM_USE_G_NV(page);
    func_8001D9CC((s16)x0, (s16)y0, (s16)x1, (s16)y1, (s16)value);
}

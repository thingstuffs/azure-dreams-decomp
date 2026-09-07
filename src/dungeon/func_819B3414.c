#include "common.h"

extern s32 func_800644B8();
extern s32 func_80064710();
extern s32 func_80065420();
extern s32 func_80066460();
extern s32 func_80066640();
extern s32 func_80066708();
extern s32 func_80067F20();
extern void *D_80083160[];

s32 func_80024C14(void *arg0) {
    u16 work[3];
    u32 grid[16][16];
    s32 helper_a;
    s32 helper_b;
    u8 *input;
    register u32 mask ASM_REG("$22") = 0x00ffffff;   /* MATCH pin: keeps a statement from moving across a call/branch */
    u32 home_scratch;
    register u8 *next ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    do {
    input = (u8 *)arg0;
    ASM_KEEP_MEMDEP(input, home_scratch, arg0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    {
        s32 seed_index = 7;
        u32 *seed_cursor;
        register u32 *seed_base ASM_REG("$8") = (u32 *)0x1f800000;   /* MATCH pin: retail register colouring depends on it */

        ASM_KEEP_NV(seed_base);   /* MATCH pin: load-bearing for the whole function shape */
        seed_cursor = seed_base + 7;
        do {
            s32 x;
            s32 value;
            s32 packed;
            x = seed_index + *(s16 *)(input + 0x48);
            value = func_800644B8((x * 75) << 4);
            value = (value >> 7) + 32;
            packed = (value << 8) + (value << 16);
            value += packed;
            *seed_cursor = value;
            seed_cursor--;
        } while (--seed_index >= 0);
    }

    {
        s32 row;
        for (row = 0; row < 16; row++) {
            s32 row_offset;
            s32 column;
            column = 0;
            row_offset = row << 6;
            do {
                register s32 dx ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                register s32 dx_square ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                register s32 dy ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                register s32 dy_square ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
                s32 distance;
                s32 value;
                s32 scaled;
                u16 *work_arg = work;
                s32 column_offset = column << 6;
                register u8 *column_base ASM_REG("$3") =
                    (u8 *)grid + column_offset;
                register s32 row_word_offset ASM_REG("$5") = row << 2;   /* MATCH pin: load-bearing for the whole function shape */

                ASM_KEEP_NV(work_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
                row_word_offset = (u32)column_base + row_word_offset;

                work[0] = *(u16 *)(input + 0x0c) + column_offset;
                work[1] = *(u16 *)(input + 0x0e) + row_offset;
                work[2] = *(u16 *)(input + 0x10);
                func_80065420(work_arg, (u32 *)row_word_offset,
                              &helper_a, &helper_b);

                work[0] -= *(u16 *)(input + 4);
                dx = (s16)work[0];
                dx_square = dx * dx;
                work[1] -= *(u16 *)(input + 6);
                dy = (s16)work[1];
                dy_square = dy * dy;
                distance = func_80064710(dx_square + dy_square);
                value = func_800644B8(
                    100 * (distance >> 2) -
                    (*(s16 *)(input + 0x48) << 8));
                value = (value >> 7) + 32;
                scaled = value * (32 - *(s16 *)(input + 0x48));
                helper_a = value;
                if (scaled < 0) {
                    scaled += 31;
                }
                {
                    register u8 *base ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                    u8 *cell;
                    cell = (u8 *)(column << 2);
                    column++;
                    scaled >>= 5;
                    base = (u8 *)0x1f800000;
                    cell = (u8 *)((u32)cell + (u32)base);
                    helper_a = scaled;
                    *(volatile u32 *)(row_offset + (u32)cell) =
                    scaled + (scaled << 8) + (scaled << 16);
                }
            } while (column < 16);
        }
    }

    {
        s32 level = *(s16 *)(input + 0x48);
        register s32 first ASM_REG("$21");   /* MATCH pin: retail register colouring depends on it */
        register s32 row ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
        register s32 row_limit ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

        if (level < 7) {
            register s32 seven ASM_REG("$2") = 7;   /* MATCH pin: retail register colouring depends on it */
            first = seven - level;
        } else {
            first = 0;
        }
        {
            register s32 limit_value ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
            row = first;
            limit_value = 15;
            row_limit = limit_value - row;
        }

        if (row < row_limit) {
            volatile s32 saved_row_limit = row_limit;
            register s32 loop_limit ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
            register s32 more_rows ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            do {
            register s32 active ASM_REG("$8") = 1;   /* MATCH pin: retail register colouring depends on it */
            register s32 column ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP_NV(active);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            column = first;
            if (active) {
                register s32 row_offset = row << 6;
                s32 row_word_offset = row << 2;
                s32 column_limit;
                register u8 *cell ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

                {
                    s32 fifteen = 15;
                    column_limit = fifteen - column;
                }
                {
                    register s32 column_word ASM_REG("$2") = column << 2;   /* MATCH pin: retail register colouring depends on it */
                    register u8 *table_base ASM_REG("$8") =
                        (u8 *)0x1f800000;
                    cell = (u8 *)(column_word + (u32)table_base);
                }

                do {
                    u8 *current;
                    u32 first_grid_value;
                    register void **global ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                    u8 *row_cell;

                    {
                        u8 *alloc_state;
                        register void **global ASM_REG("$8") = D_80083160;   /* MATCH pin: retail register colouring depends on it */
                        ASM_KEEP_NV(global);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        alloc_state = (u8 *)global[0];
                        current = *(u8 **)(alloc_state + 0x8d0);
                        *(u8 **)(alloc_state + 0x8d0) = current + 36;
                    }

                    row_cell = (u8 *)(row_offset + (u32)cell);
                    *(u32 *)(current + 4) = *(u32 *)(row_cell + 0);
                    *(u32 *)(current + 12) = *(u32 *)(row_cell + 64);
                    *(u32 *)(current + 20) = *(u32 *)(row_cell + 4);
                    *(u32 *)(current + 28) = *(u32 *)(row_cell + 68);
                    func_80066708(current);
                    func_80066640(current, 1);

                    {
                        s32 grid_offset = column << 6;
                        register u8 *grid_cell ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

                        grid_cell = (u8 *)(grid_offset + (u32)grid - 32);
                        ASM_KEEP_NV(grid_cell);   /* MATCH pin: load-bearing for the whole function shape */
                        grid_cell += 32;
                        grid_cell = (u8 *)(row_word_offset + (u32)grid_cell);
                        global = (void **)0x80080000;
                        ASM_KEEP_NV(global);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        first_grid_value = *(u32 *)(grid_cell + 0);
                        ASM_KEEP(first_grid_value);   /* MATCH pin: keeps a statement from moving across a call/branch */
                        global = (void **)((u8 *)global + 0x3160);
                        ASM_KEEP_NV(global);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        *(u32 *)(current + 8) = first_grid_value;
                        *(u32 *)(current + 16) = *(u32 *)(grid_cell + 4);
                        grid_cell = (u8 *)grid + 64;
                        grid_cell += grid_offset;
                        grid_cell = (u8 *)(row_word_offset + (u32)grid_cell);
                        *(u32 *)(current + 24) = *(u32 *)(grid_cell + 0);
                        *(u32 *)(current + 32) = *(u32 *)(grid_cell + 4);
                        column++;
                    }

                    {
                        u8 *first_state;
                        u32 current_high;
                        first_state = (u8 *)global[0];
                        ASM_KEEP_NV(first_state);   /* MATCH pin: load-bearing for the whole function shape */
                        {
                        register u32 high_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
                        current_high = *(u32 *)current & high_mask;
                        }
                        {
                        register void **second_global ASM_REG("$8") =
                            (void **)0x80080000;
                        u8 *second_state;
                        ASM_KEEP_NV(second_global);   /* MATCH pin: keeps a statement from moving across a call/branch */
                        first_state = (u8 *)(u32)*(u32 *)(first_state + 0xb0);
                        ASM_KEEP_NV(first_state);   /* MATCH pin: load-bearing for the whole function shape */
                        second_global = (void **)((u8 *)second_global + 0x3160);
                        ASM_KEEP_NV(second_global);   /* MATCH pin: keeps a statement from moving across a call/branch */
                        *(u32 *)current = current_high | ((u32)first_state & mask);
                        second_state = (u8 *)second_global[0];
                        {
                        register u32 high_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
                        ASM_KEEP_NV(high_mask);
                        *(u32 *)(second_state + 0xb0) =
                            (*(u32 *)(second_state + 0xb0) & high_mask) |
                            ((u32)current & mask);
                        }
                        }
                    }
                } while (column < column_limit && (cell += 4, 1));
            }
            loop_limit = saved_row_limit;
            row++;
            more_rows = row < loop_limit;
            } while (more_rows);
        }
    }

    {
        u8 *current;
        s32 value;

        {
            s32 zero_arg = 0;
            s32 two = 2;
            u8 *alloc_state;
            register void **global ASM_REG("$8") = D_80083160;   /* MATCH pin: retail register colouring depends on it */
            ASM_KEEP_NV(zero_arg);
            ASM_KEEP_NV(two);
            ASM_KEEP_NV(global);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            alloc_state = (u8 *)global[0];
            current = *(u8 **)(alloc_state + 0x8d0);

            *(u8 **)(alloc_state + 0x8d0) = current + 12;
            value = func_80066460(zero_arg, two, zero_arg, zero_arg);
        }
        {
            register u8 *current_arg ASM_REG("$4") = current;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            s32 zero_arg = 0;
            ASM_KEEP_NV(current_arg);
            ASM_KEEP_NV(zero_arg);
            func_80067F20(current_arg, zero_arg, zero_arg,
                          value & 0xffff, 0);
        }

        {
            u8 *first_state;
            u32 current_word;
            register void **global ASM_REG("$8") = D_80083160;   /* MATCH pin: retail register colouring depends on it */
            ASM_KEEP_NV(global);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            first_state = (u8 *)global[0];
            ASM_KEEP_NV(first_state);   /* MATCH pin: load-bearing for the whole function shape */
            current_word = *(u32 *)current;
            ASM_KEEP_NV(current_word);
            {
            register u32 high_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
            current_word &= high_mask;
            }
            {
            register void **second_global ASM_REG("$8") =
                (void **)0x80080000;
            u8 *second_state;
            ASM_KEEP_NV(second_global);   /* MATCH pin: keeps a statement from moving across a call/branch */
            first_state = (u8 *)(u32)*(u32 *)(first_state + 0xb0);
            ASM_KEEP_NV(first_state);   /* MATCH pin: load-bearing for the whole function shape */
            second_global = (void **)((u8 *)second_global + 0x3160);
            ASM_KEEP_NV(second_global);   /* MATCH pin: keeps a statement from moving across a call/branch */
            *(u32 *)current = current_word | ((u32)first_state & mask);
            second_state = (u8 *)second_global[0];
            {
            register u32 high_mask ASM_REG("$8") = 0xff000000;   /* MATCH pin: retail register colouring depends on it */
            *(u32 *)(second_state + 0xb0) =
                (*(u32 *)(second_state + 0xb0) & high_mask) |
                ((u32)current & mask);
            }
            }
        }
    }

    {
        register u8 *arg_cursor ASM_REG("$8") = (u8 *)arg0;   /* MATCH pin: retail register colouring depends on it */
        next = *(u8 **)(arg_cursor - 8);
    }
    } while (next != 0 && (arg0 = next + 32, 1));

    return 0;
}

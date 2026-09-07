#include "common.h"
#include "m2c_compat.h"

extern struct S_8003E2D8 D_80083160;
extern u8 D_80089660[];
extern void *memcpy(void *dst, const void *src, u32 n);

typedef struct S_800BDC98_0 {
    u8 pad_00[0x1DC];
    s8 * unk_1DC;
} S_800BDC98_0;   /* base in func_800BDC98 */

typedef struct S_800BDC98_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    s16 unk_1A;
} S_800BDC98_1;   /* temp_t2 in func_800BDC98 */

/* Writes a selected pair of 16-bit values to adjacent positions in the wrapped buffer. */
void func_800BDC98(s16 start_x, s16 start_y, s16 mode, s32 pair_index) {
    u16 value_pairs[8];
    s32 selected_pair;
    register s32 saved_pair ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 first_x;
    s32 height;
    s32 y;
    s32 x;
    s32 x_limit;
    register s32 pair_test ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 shifted_y;
    s32 x_end;
    s32 y_limit;
    s32 wrapped_y;
    s32 pair_offset;
    s8 *state;
    s8 *pair_src;
    s8 *buffer_info;
    s8 *buffer;

    saved_pair = pair_index;
    selected_pair = saved_pair;
    M2C_MEMCPY_UNALIGNED(value_pairs, D_80089660, 0x10);
    state = (s8 *)&D_80083160;
    buffer_info = state + 0x1DC;
    buffer = ((S_800BDC98_0 *)state)->unk_1DC;
    height = 1;
    if ((mode == 2) || (selected_pair = 3, pair_test = saved_pair << 0x10, (pair_test == 0))) {
        x = start_x;
        x_limit = x;
        x_limit += 2;
        if (x < x_limit) {
            shifted_y = start_y << 0x10;
            pair_offset = ((s32)(selected_pair << 0x10) >> 0xE);
            pair_src = (s8 *)((long)pair_offset + (long)value_pairs);
            first_x = x;
            x_end = x_limit;
            while (x < x_end) {
                y = shifted_y >> 0x10;
                y_limit = y + height;
                if (y < y_limit) {
                    s8 *value_src;
                    s32 y_end;
                    value_src = (s8 *)((long)((x - first_x) * 2) + (long)pair_src);
                    y_end = y_limit;
                    do {
                        wrapped_y = y & ((S_800BDC98_1 *)buffer_info)->unk_1A;
                        y += 1;
                        *(u16 *)((long)((s32) (((((S_800BDC98_1 *)buffer_info)->unk_18 & x) + (wrapped_y << ((S_800BDC98_1 *)buffer_info)->unk_14)) << 0x10) >> 0xF) + (long)buffer) = *(u16 *)value_src;
                    } while (y < y_end);
                }
                x += 1;
            }
        }
    }
}

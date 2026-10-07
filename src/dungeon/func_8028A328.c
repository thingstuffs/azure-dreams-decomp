#include "common.h"
#include "m2c_compat.h"

s32 func_8001E660(); /* extern */
void func_8009A21C();             /* extern */
s32 func_8009A350();         /* extern */
/* extern */
s32 func_800A6DA4();                    /* extern */
extern u8 D_800E3549[];
extern u8 D_800E36C8[];

typedef struct S_8001D328_0 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
    u8 pad_03[0x1];
    u16 unk_04;
    u16 unk_06;
} S_8001D328_0;   /* arg0 in func_8001D328 */

typedef struct S_8001D328_1 {
    u8 unk_00;
    u8 unk_01;
} S_8001D328_1;   /* var_s1 in func_8001D328 */


s32 func_800A6D30(void);
/* Choose random coordinates within a region and mark eligible tiles. */
void func_8001D328(S_8001D328_0 *region, s32 setup_arg1) {
    s32 random_bits;
    u16 tile_flags;
    s16 count;
    s32 entry_index;
    s32 x_offset;
    s32 y_offset;
    u8 *state;
    u8 *state_prefix;
    S_8001D328_1 *coords;
    s32 sum;
    u8 *state_base;
    u8 *prefix_base;
    u8 *coords_base;
    s32 state_offset;
    s32 coords_offset;

    random_bits = func_800A6D30();
    sum = ((region->unk_06 * region->unk_04) >> 6) + (random_bits & 7) + 4;
    count = sum;
    if ((s16)sum >= 0x3D) {
        count = 0x3C;
    }
    entry_index = count;
    if (entry_index >= 0) {
        state_base = D_800E3549;
        prefix_base = state_base - 1;
        state_offset = entry_index * 4;
        state_prefix = state_offset + prefix_base;
        state = state_offset + state_base;
        coords_base = D_800E36C8;
        coords_offset = entry_index * 0xC;
        coords = (S_8001D328_1 *)(coords_offset + coords_base);
loop:
            x_offset = func_800A6DA4(0, (region->unk_04 - 1) & 0xFFFF) & 0xFFFF;
            y_offset = func_800A6DA4(0, (region->unk_06 - 1) & 0xFFFF) & 0xFFFF;
            coords->unk_00 = region->unk_00 + x_offset;
            coords->unk_01 = region->unk_02 + y_offset;
            if (((func_8009A350(coords->unk_00 - 1, coords->unk_01, 0, &tile_flags) << 16) == 0) || !(tile_flags & 0xFF20)) {
                func_8009A21C(coords->unk_00, coords->unk_01, 0x800);
                func_8001E660(state, state_prefix, 0, 1);
            }
            state_prefix -= 4;
            state -= 4;
            entry_index--;
            coords = (S_8001D328_1 *)((u8 *)coords - 0xC);
            if (entry_index >= 0) {
                goto loop;
            }
    }
}

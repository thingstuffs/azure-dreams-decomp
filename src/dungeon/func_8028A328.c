#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001E660(); /* extern */
M2C_UNK func_8009A21C();             /* extern */
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


s32 func_800A6D30(S_8001D328_0 *, s32, s32, s32);
/* Choose random coordinates within a region and mark eligible tiles. */
void func_8001D328(S_8001D328_0 *region, s32 setup_arg1, s32 setup_arg2, s32 setup_arg3) {
    s32 random_bits;
    u16 tile_flags;
    s16 limit_test;
    s32 x_offset;
    s32 y_offset;
    s32 coord;
    s32 entry_index;
    s32 last_index;
    void *coords;
    void *state;
    void *state_prefix;
    u8 *state_base;

    random_bits = func_800A6D30(region, setup_arg1, setup_arg2, setup_arg3);
    {
        register s32 height ASM_REG("$4");
        register s32 width ASM_REG("$3");
        register s32 area ASM_REG("$8");
        register s32 index_sum ASM_REG("$3");

        height = region->unk_06;
        width = region->unk_04;
        area = height * width;
        random_bits &= 7;
        index_sum = (area >> 6) + random_bits + 4;
        last_index = index_sum;
        ASM_KEEP(last_index);
        limit_test = index_sum;
    }
    limit_test = limit_test < 0x3D;
    if (!limit_test) {
        last_index = 0x3C;
    }
    entry_index = (s16) last_index;
    if (entry_index >= 0) {
        register u8 *prefix_base ASM_REG("$4");
        register s32 state_offset ASM_REG("$3");
        u8 *coords_base;
        s32 coords_offset;

        state_base = D_800E3549;
        prefix_base = state_base - 1;
        state_offset = entry_index * 4;
        state_prefix = (void *) (state_offset + (s32) prefix_base);
        state = state_offset + state_base;
        coords_base = D_800E36C8;
        coords_offset = entry_index * 0xC;
        coords = (void *) (coords_offset + (s32) coords_base);
        do {
            x_offset = func_800A6DA4(0, (region->unk_04 - 1) & 0xFFFF) & 0xFFFF;
            y_offset = func_800A6DA4(0, (region->unk_06 - 1) & 0xFFFF) & 0xFFFF;
            coord = region->unk_00 + x_offset;
            ((S_8001D328_1 *)coords)->unk_00 = (u8) coord;
            coord = region->unk_02 + y_offset;
            ((S_8001D328_1 *)coords)->unk_01 = (u8) coord;
            if (((func_8009A350(((S_8001D328_1 *)coords)->unk_00 - 1, *(volatile u8 *) ((u8 *) coords + 1), 0, &tile_flags) << 0x10) == 0) || !(tile_flags & 0xFF20)) {
                func_8009A21C(((S_8001D328_1 *)coords)->unk_00, ((S_8001D328_1 *)coords)->unk_01, 0x800);
                func_8001E660(state, state_prefix, 0, 1);
            }
            state_prefix -= 4;
            state -= 4;
            entry_index -= 1;
            coords -= 0xC;
        } while (entry_index >= 0);
    }
}

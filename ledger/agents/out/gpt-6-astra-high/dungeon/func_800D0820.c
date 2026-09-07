#include "common.h"
#include "m2c_compat.h"

extern s8 D_800E2468[];
s32 func_800A45D8(s32, s32, s16);
s16 func_800BCB04(s32, s32, s16);

typedef struct S_800D5F80_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D5F80_0;   /* arg0 in func_800D5F80 */

typedef struct S_800D5F80_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800D5F80_1;   /* arg1 in func_800D5F80 */

typedef struct S_800D5F80_2 {
    s16 unk_00;
    s16 unk_02;
} S_800D5F80_2;   /* temp_a1 in func_800D5F80 */

/* Checks whether the position ahead passes the collision and height tests. */
s32 func_800D5F80(S_800D5F80_0 *position, S_800D5F80_1 *orientation) {
    s16 surface_height;
    s32 probe_y;
    s32 probe_x;
    s16 probe_height;
    s32 height;
    void *offset_table;
    S_800D5F80_2 *offset;

    height = position->unk_0A;
    probe_height = height - 0x20;
    offset_table = D_800E2468;
    offset = offset_table + ((orientation->unk_2A >> 7) & 0x1C);
    probe_x = (position->unk_02 + (offset->unk_00 << 6)) & 0xFFFF;
    probe_y = (position->unk_06 + (offset->unk_02 << 6)) & 0xFFFF;
    if ((func_800A45D8(probe_x, probe_y, probe_height) << 0x10) == 0) {
        surface_height = func_800BCB04(probe_x, probe_y, probe_height);
        if (surface_height < 0x200 &&
            (position->unk_0A - 0x40) < surface_height) {
            goto fail;
        }
    }
    return 1;
fail:
    return 0;
}

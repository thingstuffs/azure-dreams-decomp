#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern s8 D_800E2468[];
s32 func_800A45D8(s32, s32, s16);
s16 func_800BCB04(s32, s32, s16);


typedef struct S_800D5F80_2 {
    s16 unk_00;
    s16 unk_02;
} S_800D5F80_2;   /* temp_a1 in func_800D5F80 */

/* Checks whether the position ahead passes the collision and height tests. */
s32 func_800D5F80(EntityRec *position, EntityRec *orientation) {
    s16 surface_height;
    s32 probe_y;
    s32 probe_x;
    s16 probe_height;
    s32 height;
    void *offset_table;
    S_800D5F80_2 *offset;

    height = position->z.w.i;
    probe_height = height - 0x20;
    offset_table = D_800E2468;
    offset = offset_table + ((((u16)orientation->facing) >> 7) & 0x1C);
    probe_x = (position->x.w.i + (offset->unk_00 << 6)) & 0xFFFF;
    probe_y = (position->y.w.i + (offset->unk_02 << 6)) & 0xFFFF;
    if ((func_800A45D8(probe_x, probe_y, probe_height) << 0x10) == 0) {
        surface_height = func_800BCB04(probe_x, probe_y, probe_height);
        if (surface_height < 0x200 &&
            (position->z.w.i - 0x40) < surface_height) {
            goto fail;
        }
    }
    return 1;
fail:
    return 0;
}

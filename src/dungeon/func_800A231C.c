#include "common.h"

typedef struct {
    u8 b0;
    u8 b1;
    u16 w2;
    u16 w4;
    u16 pad6;
    s32 value;
} DungeonRecord;

extern u8 D_80082E80[];
extern u8 *D_800E3D7C[];
extern s32 D_800E3548[];
extern DungeonRecord D_800E36C8[];
extern s32 D_800E0B54;

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099368(s32 *, s32);
extern s32 func_800A4300(void *, void *);
extern void func_800A5720(s32);
extern s16 func_800A71F4(void);
extern s32 func_800A7234(s32, s32, s32, s16 *, s16 *, s16 *);
extern void func_800A7700(s32, s32, s32, s32 *);
extern s32 func_800A794C(s32, s32, s32, s32 *, s32, s32, s32);
extern s32 func_800A7A38(s32 *);
extern void func_8009A21C(s16, s16, s32);

/* Registers an object at a resolved dungeon position or processes its fallback placement. */
s32 func_800A7A7C(s32 x, s32 y, s32 z, s32 unused, s32 *object_data) {
    s16 tile_x;
    s16 tile_y;
    s16 tile_value;
    s32 output_start;
    s32 output_cursor;
    s16 x_short;
    s16 y_short;
    s16 z_short;

    x_short = (s16)x;
    y_short = (s16)y;
    z_short = (s16)z;
    if ((func_800A7234(x_short, y_short, z_short,
                       &tile_x, &tile_y, &tile_value) << 16) != 0) {
        s16 record_index;
        DungeonRecord *record;

        record_index = func_800A71F4();
        if (record_index >= 0) {
            if (func_800A794C(x_short, y_short, z_short, object_data,
                              tile_x, tile_y, tile_value) == 0) {
                D_800E3548[record_index] = *object_data;
                record = &D_800E36C8[record_index];
                record->b0 = (u8)tile_x;
                record->b1 = (u8)tile_y;
                record->w4 = (u16)tile_value;
                record->w2 = (u16)tile_value;
                record->value = func_800A7A38(object_data);
                func_8009A21C(tile_x, tile_y, 0x800);
                func_800A4300(D_80082E80, *D_800E3D7C);
            }
            return 1;
        }
    }

    func_800A7700(x_short, y_short, z_short, object_data);
    output_cursor = func_800990FC();
    output_start = output_cursor;
    output_cursor = func_80099368(object_data, output_cursor);
    output_cursor = func_80099194(&D_800E0B54, output_cursor);
    func_80099290(output_cursor);
    func_800A5720(output_start);
    return 0;
}

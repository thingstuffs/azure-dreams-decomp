#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 field8;
    s16 fieldA;
    u8 padC[4];
    s32 field10;
    s32 field14;
    s32 field18;
} TownRecord;

extern TownRecord D_800D1178;
extern TownRecord D_800D119C;
extern u16 D_80100D18;
extern u16 D_80100D40;
extern u16 D_80100D42;

extern void draw_random_colored_line();
extern void transform_and_queue_mesh_quads();

/* Initialize and apply the two town records to the target. */
void apply_two_records_to_target(s32 target, s32 setup_data)
{
    s32 record_value;
    s32 record_value2;

    draw_random_colored_line(setup_data, target);

    record_value = (s16)D_80100D18 / 2;
    D_800D1178.field10 = record_value;
    D_800D1178.field14 = record_value;
    D_800D1178.field18 = record_value;
    D_800D1178.fieldA = -D_80100D40;
    transform_and_queue_mesh_quads(&D_800D1178, target);

    record_value2 = (s16)D_80100D18;
    D_800D119C.field10 = record_value2;
    D_800D119C.field14 = record_value2;
    D_800D119C.field18 = record_value2;
    D_800D119C.field8 = D_80100D42;
    transform_and_queue_mesh_quads(&D_800D119C, target);
}

#include "common.h"
#include "shared/entity.h"



extern s32 rsin(s32 value_a);
extern s32 rcos(s32 value_b);
extern void clear_entity_record_fields(void *record);
extern s32 D_80098690;

typedef struct S_80098764_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x1E];
    s16 unk_30;
    s16 unk_32;
} S_80098764_0;   /* arg0 in interpolate_position_by_angle_offset */


/* Interpolate the position toward an angle-based offset until the countdown expires. */
void interpolate_position_by_angle_offset(void *motion, EntityRec *position) {
    u16 ticks_left;
    s32 old_y;

    ticks_left = ((S_80098764_0 *)motion)->unk_0A - 1;
    ((S_80098764_0 *)motion)->unk_0A = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        position->x.v =
            ((rsin(((S_80098764_0 *)motion)->unk_10) << 9)
             + (((S_80098764_0 *)motion)->unk_30 << 0x10)
             + position->x.v) / 2;
        position->y.v =
            ((rcos(((S_80098764_0 *)motion)->unk_10) << 9)
             + (((S_80098764_0 *)motion)->unk_32 << 0x10)
             + (old_y = position->y.v)) / 2;
        return;
    }
    clear_entity_record_fields(position);
    ((S_80098764_0 *)motion)->unk_0A = 7;
    ((S_80098764_0 *)motion)->unk_04 = &D_80098690;
}

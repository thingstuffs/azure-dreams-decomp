#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_800A05A4_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A05A4_1;   /* found in scan_monster_along_heading */


extern void *find_eligible_entry_at_coordinates(void *, u16, u16);
extern s32 is_map_coordinate_out_of_bounds(s16, s16);
extern s16 check_layer_offset_height(u16, u16, s16, u32);

/* Scans along a heading for an object within the height range and records the stopping coordinates. */
void *scan_actor_along_heading(EntityRec *source, s32 start_x, s32 start_y, s16 heading, s16 max_steps)
{
    s32 dir;
    u16 x;
    u16 y;
    s16 height;
    void *found;
    s32 i;

    found = 0;
    dir = heading = (heading >> 9) & 7;
    height = 0x20;
    x = dir_step_x[dir] + start_x;
    y = dir_step_y[dir] + start_y;
    if (is_map_coordinate_out_of_bounds(x, y) != 0) {
        source->unk_72 = dir_step_x[dir] - x;
        source->unk_73 = dir_step_y[dir] - y;
        return 0;
    }
    for (i = 0; i < max_steps; i++) {
        found = find_eligible_entry_at_coordinates(source, x, y);
        if (found != 0 && abs(((S_800A05A4_1 *)found)->unk_88 - source->unk_88) <= height) {
            break;
        }
        if (is_map_coordinate_out_of_bounds(x + dir_step_x[dir], y + dir_step_y[dir]) != 0) {
            source->unk_72 = dir_step_x[dir] - x;
            source->unk_73 = dir_step_y[dir] - y;
            return 0;
        }
        if (check_layer_offset_height(x << 6, y << 6, source->unk_88 - height, heading << 9) != 0) {
            source->unk_72 = -x;
            source->unk_73 = -y;
            return 0;
        }
        height += 0x20;
        x += dir_step_x[dir];
        y += dir_step_y[dir];
    }
    source->unk_72 = x;
    source->unk_73 = y;
    return found;
}

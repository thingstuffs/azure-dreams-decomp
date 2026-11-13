#include "common.h"
#include "town/scene/grid_queries.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player.h"
#include "town.h"
#include "town/player/coordinates.h"
#include "sdk/libgte_matrix.h"


typedef struct S_80018094_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
} S_80018094_1;   /* (((Rec_D_80016000 *)D_80016000)->unk_08.at00_s32.v << 5) +
            *((Rec_D_80016000 *)D_80016000)->unk_30.as_ps32 in apply_target_grid_rectangle */



/* Applies a target rectangle positioned at the given grid cell center. */
u32 apply_target_grid_rectangle(s32 target_x, s32 target_y)
{
    SVECTOR current_rect;
    SVECTOR target_rect;
    s32 coord_offset;

    copy_current_record_components_3(&current_rect);
    target_x <<= 6;
    target_y <<= 6;
    current_rect.vz = 0;
    coord_offset = ((S_80018094_1 *)((town_scene_root->entry_index << 5) +
            *((s32 *)town_scene_root->unk_30)))->unk_0C + 0x20;
    target_x += coord_offset;
    target_rect.vx = target_x;
    coord_offset = ((S_80018094_1 *)((town_scene_root->entry_index << 5) +
            *((s32 *)town_scene_root->unk_30)))->unk_0E + 0x20;
    target_rect.vz = 0;
    target_y += coord_offset;
    target_rect.vy = target_y;
    return points_within_squared_threshold(&current_rect, &target_rect, 0x20);
}

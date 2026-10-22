/* Grid rectangle preset and its file-private helper. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
typedef struct S_80018094_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
} S_80018094_1;
/* (((Rec_D_80016000 *)D_80016000)->unk_08.at00_s32.v << 5) +
            *((Rec_D_80016000 *)D_80016000)->unk_30.as_ps32 in apply_target_grid_rectangle */


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;
extern void copy_current_record_components_3();
extern void points_within_squared_threshold();
#include "m2c_compat.h"

/* Scales a tile target by 64, adds the grid origin and 32, then tests it against the current position. */
static void apply_target_grid_rectangle(s32 target_x, s32 target_y)
{
    Rect current_rect;
    Rect target_rect;
    s32 coord_offset;

    copy_current_record_components_3(&current_rect);
    target_x <<= 6;
    target_y <<= 6;
    current_rect.w = 0;
    coord_offset = ((S_80018094_1 *)((D_80016000->unk_08 << 5) +
            *((s32 *)D_80016000->unk_30)))->unk_0C + 0x20;
    target_x += coord_offset;
    target_rect.x = target_x;
    coord_offset = ((S_80018094_1 *)((D_80016000->unk_08 << 5) +
            *((s32 *)D_80016000->unk_30)))->unk_0E + 0x20;
    target_rect.w = 0;
    target_y += coord_offset;
    target_rect.y = target_y;
    points_within_squared_threshold(&current_rect, &target_rect, 0x20);
}

void apply_rectangle_preset_10x7(void) {
    apply_target_grid_rectangle(0x10, 7);
}

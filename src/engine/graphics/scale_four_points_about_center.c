#include "common.h"
#include "shared/game_work.h"

#include "engine/graphics.h"
#include "engine/resource.h"
#include "slus/data.h"

/* Copy XYZ for all six outline points, then scale the first four about their center. */
void copy_and_scale_screen_outline_points(void)
{
    u16 *dst_first = scaled_window_quad_points;
    u16 *dst_base = dst_first;
    GameWork *state = &g_game_work;
    const u8 *source_data = (const u8 *)&state->view;
    const SVECTOR *src_first = state->view.outline;
    s32 record_count = 0;
    /* Four clipping halfwords precede the first XYZ record. */
    const u8 *src_third = source_data + 4 * sizeof(state->view.clip_x) + 2 * sizeof(s16);
    s32 z_index = 2;

    do {
        u16 field_value = src_first->vx;
        src_first++;
        record_count++;
        *dst_first = field_value;
        field_value = *(const u16 *)(src_third - sizeof(u16));
        dst_first += 4;
        dst_base[z_index - 1] = field_value;
        field_value = *(const u16 *)src_third;
        src_third += sizeof(SVECTOR);
        dst_base[z_index] = field_value;
        z_index += 4;
    } while (record_count < 6);

    scale_quad_points_about_center(scaled_window_quad_points, 6, 4);
}

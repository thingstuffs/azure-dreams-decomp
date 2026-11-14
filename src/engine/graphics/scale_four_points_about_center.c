#include "common.h"
#include "shared/game_work.h"

#include "engine/graphics.h"
#include "engine/graphics/outline_points_data.h"
#include "engine/resource.h"

/* Copies three fields from each of six records and processes the destination buffer. */
void copy_and_scale_screen_outline_points(void)
{
    u16 *dst_first = scaled_window_quad_points;
    u8 *source_data = ((u8 *)(&g_game_work));
    u16 *src_first = (u16 *)(source_data + 0x20);
    s32 record_count = 0;
    u16 *src_third = (u16 *)(source_data + 0x24);
    u16 *dst_third = dst_first + 2;

    do {
        u16 field_value = *src_first;
        src_first += 4;
        record_count++;
        *dst_first = field_value;
        field_value = src_third[-1];
        dst_first += 4;
        dst_third[-1] = field_value;
        field_value = *src_third;
        src_third += 4;
        *dst_third = field_value;
        dst_third += 4;
    } while (record_count < 6);

    scale_quad_points_about_center(scaled_window_quad_points, 6, 4);
}

#include "common.h"
#include "shared/game_work.h"

#include "common.h"

extern u8 D_80082D08[0x100];
extern void runtime_scale_four_points_about_center(u16 *, s32, s32);

/* Copies three fields from each of six records and processes the destination buffer. */
void copy_and_scale_screen_outline_points(void)
{
    u16 *dst_first = (u16 *)D_80082D08;
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

    runtime_scale_four_points_about_center((u16 *)D_80082D08, 6, 4);
}

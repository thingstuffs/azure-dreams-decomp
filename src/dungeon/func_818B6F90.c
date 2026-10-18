#include "modules/dungeon_ovl_18d6800.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"




   /* scratch in func_80024790 */

   /* base in func_80024790 */

   /* packet in func_80024790 */

   /* arg1 in func_80024790 */

/* Projects a textured color-gradient quad and links it into the ordering table if its depth is in range. */
s32 func_80024790(s32 texture_index, u8 *color_source)
{
    u8 *render_buffer;
    u8 *packet;
    u8 *scratch;
    s32 texture_u;
    s16 texture_id;
    u32 *ot_read;
    u32 *ot_write;
    u32 depth_index;
    u32 write_depth;
    u32 ot_entry;
    u8 *screen_xy0;
    u8 *screen_xy1;
    u8 *screen_xy2;
    u8 *screen_xy3;
    u8 *depth_cue;
    u8 *transform_flags;

    scratch = (u8 *)0x1F800000;
    render_buffer = *(u8 **)((u8 *)(&g_game_work));
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_00 = render_buffer + 0xB0;
    packet = ((GpuContext *)render_buffer)->packetCursor;
    ((GpuContext *)render_buffer)->packetCursor = packet + 0x34;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_00.at03.v = 0x0C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_07 = 0x3E;

    texture_id = func_80066460(0, 3, 0x300, 0x100);
    texture_u = (texture_index << 16) >> 13;
    texture_u += 0x80;
    screen_xy0 = scratch + 0x70;
    screen_xy1 = scratch + 0x74;
    screen_xy2 = scratch + 0x78;
    screen_xy3 = scratch + 0x7C;
    depth_cue = scratch + 0x08;
    transform_flags = scratch + 0x0C;

    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1A = texture_id;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_0E = 0x7DCF;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_0C = texture_u;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_0D = 0x40;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_18 = texture_u | 7;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_19 = 0x40;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_24 = texture_u | 7;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_25 = 0x7F;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_30 = texture_u;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_31 = 0x7F;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_04 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_05 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_06 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_10 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_11 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_12 = 0;

    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1C = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1D = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0D;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1E = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0E;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_28 = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_29 = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0D;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_2A = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0E;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_10 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_30 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_18 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_40 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_20 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_50 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_28 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_60 >> 16;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_12 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_34 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_1A = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_44 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_22 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_54 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_2A = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_64 >> 16;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_14 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_38 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_1C = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_48 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_24 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_58 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_2C = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_68 >> 16;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_04.v = func_80065590(
        scratch + 0x10, scratch + 0x18, scratch + 0x20, scratch + 0x28,
        screen_xy0, screen_xy1, screen_xy2, screen_xy3,
        depth_cue, transform_flags);

    (*(u16 *)((u8 *)packet + (0x08))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_70;
    (*(u16 *)((u8 *)packet + (0x0A))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_72;
    (*(u16 *)((u8 *)packet + (0x14))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_74;
    (*(u16 *)((u8 *)packet + (0x16))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_76;
    (*(u16 *)((u8 *)packet + (0x20))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_78;
    (*(u16 *)((u8 *)packet + (0x22))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_7A;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_2C = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_7C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_2E = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_7E;

    depth_index = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_04.v2;
    if (depth_index < 0x1E0) {
        ot_read = ((u32 *)((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_00);
        ot_entry = ot_read[depth_index];
        ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_00.at00.v =
            (((B28_818B6F90_S_818B6F90_2 *)packet)->unk_00.at00.v & 0xFF000000) |
            (ot_entry & 0x00FFFFFF);
        write_depth = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_04.v2;
        ot_write = ((u32 *)((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_00);
        ot_write[write_depth] =
            (ot_write[write_depth] & 0xFF000000) |
            ((u32)packet & 0x00FFFFFF);
    }

    return 0;
}

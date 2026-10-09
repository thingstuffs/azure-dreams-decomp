#include "modules/dungeon_ovl_1840800.h"
#include "common.h"
#include "shared/game_work.h"




/* Draw four jittered triangles per linked item into the ordering table. */
s32 func_80024A1C(void *first_item)
{
    u16 screen_coords[3];
    void *list_item;
    void *item_data;
    GameWork *render_context;
    u8 *draw_mode;
    u8 *triangle;
    u32 depth_index;
    s32 point_index;
    s32 blend_mode;
    s32 byte_offset;
    u32 *ot_entry_base;
    u32 ot_tag;

    list_item = first_item;
    render_context = &gameWork;

    do {
        item_data = list_item;
        point_index = 3;
        do {
            draw_mode = render_context->unk_000 + 0x8D0;
            draw_mode = *(u8 **)draw_mode;
            *(u8 **)(render_context->unk_000 + 0x8D0) = draw_mode + 0xC;

            triangle = *(u8 **)(render_context->unk_000 + 0x8D0);
            *(u8 **)(render_context->unk_000 + 0x8D0) = triangle + 0x14;

            ((TrailTriangle *)triangle)->unk_04 = ((TrailRenderItem *)item_data)->unk_48;
            func_80066690(triangle);
            func_80066640(triangle, 1);

            blend_mode = 3;
            if (((TrailRenderItem *)item_data)->unk_54 > 0) {
                blend_mode = 1;
            }
            func_80067F20(draw_mode, 0, 0,
                func_80066460(0, blend_mode, 0, 0) & 0xFFFF, 0);

            byte_offset = (point_index * 8) + 0x28;
            depth_index = func_80065420((u8 *)item_data + byte_offset,
                screen_coords, &screen_coords[2], &screen_coords[2]) - 8;

            ((TrailTriangle *)triangle)->unk_08 = screen_coords[0] + (func_80069EF8() & 1) + 1;
            ((TrailTriangle *)triangle)->unk_0A = screen_coords[1] + (func_80069EF8() & 1) + 1;
            ((TrailTriangle *)triangle)->unk_0C = screen_coords[0] - (func_80069EF8() & 1) - 1;
            ((TrailTriangle *)triangle)->unk_0E = screen_coords[1] + (func_80069EF8() & 1) + 1;
            ((TrailTriangle *)triangle)->unk_10 = screen_coords[0] + (func_80069EF8() & 4) - 2;
            ((TrailTriangle *)triangle)->unk_12 = screen_coords[1] - (func_80069EF8() & 1) - 1;

            if (depth_index < 0x1E0U) {
                u32 addr_mask = 0x00FFFFFF;
                u32 length_mask = 0xFF000000;

                byte_offset = depth_index * 4;
                ((GpuLinkTag *)triangle)->addr = ((GpuLinkTag *)&((u32 *)(render_context->unk_000 + 0xB0))[depth_index])->addr;
                ot_entry_base = (u32 *)(byte_offset + (s32) render_context->unk_000);
                ot_tag = ((TrailOrderEntry *)ot_entry_base)->unk_B0;
                (*(u32 *)((u8 *)ot_entry_base + 0xB0)) = (ot_tag & length_mask) |
                    ((u32)triangle & addr_mask);

                (*(u32 *)((u8 *)draw_mode + 0)) =
                    (((TrailDrawMode *)draw_mode)->unk_00 & length_mask) |
                    (((u32 *)(render_context->unk_000 + 0xB0))[depth_index] & addr_mask);
                ((u32 *)(render_context->unk_000 + 0xB0))[depth_index] =
                    (((u32 *)(render_context->unk_000 + 0xB0))[depth_index] & length_mask) |
                    ((u32)draw_mode & addr_mask);
            }
            point_index--;
        } while (point_index >= 0);

        if (((TrailChainPrefix *)list_item)[-1].unk_00 == 0) break;
        list_item = (void *)(((TrailChainPrefix *)list_item)[-1].unk_00 + 0x20);
    } while (1);

    return 0;
}

#include "modules/dungeon_ovl_191284c.h"

s32 dungeonDrawLinkedShadedTiles(void *first_point, void *first_position)
{
    void *point = first_point;
    void *position = first_position;
    GameWork *render_state = &gameWork;
    u32 addr_mask = 0x00FFFFFF;
    u8 *render_ctx = *(u8 **)((u8 *)(&gameWork));
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Row_818F30EC_Scratch800248EC *scratch =
        (Row_818F30EC_Scratch800248EC *)0x1F800000;
    Row_818F30EC_Packet800248EC *tile;
    Row_818F30EC_Packet800248EC *draw_mode;
    u8 *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    void *next_node;

    packet_start = ((GpuContext *)render_ctx)->packetCursor;
    scratch->ot = (u32 *)(render_ctx + 0xB0);
    scratch->cursor = packet_start;

    for (;;) {
        tile = *(Row_818F30EC_Packet800248EC **)&scratch->cursor;
        scratch->x = ((Row_818F30EC_S_800248EC_1 *)position)->unk_02;
        scratch->y = ((Row_818F30EC_S_800248EC_1 *)position)->unk_06;
        scratch->z = ((Row_818F30EC_S_800248EC_1 *)position)->unk_0A;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)tile + 8,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            ((Row_818F30EC_S_800248EC_2 *)tile)->unk_04.at00.v = ((Row_818F30EC_S_800248EC_3 *)point)->unk_08;

            color_value = (s32)tile->r * ((Row_818F30EC_S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * ((Row_818F30EC_S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * ((Row_818F30EC_S_800248EC_3 *)point)->unk_32;
            tile->b = (color_value / 128);

            ((Row_818F30EC_S_800248EC_2 *)tile)->unk_03 = 2;
            ((Row_818F30EC_S_800248EC_2 *)tile)->unk_04.at03.v = 0x6A;
            ((Row_818F30EC_P_TAG *)&tile->tag)->addr = ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr;
            ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (Row_818F30EC_Packet800248EC *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            ((Row_818F30EC_P_TAG *)&draw_mode->tag)->addr = ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr;
            ((Row_818F30EC_P_TAG *)&scratch->ot[scratch->index])->addr = (u32)((u32)draw_mode);
        }

        next_node = ((Row_818F30EC_S_800248EC_3_pre *)point)[-1].unk_00;
        if (next_node != 0) {
            point = (u8 *)next_node + 0x20;
            position = ((Row_818F30EC_S_800248EC_4 *)next_node)->unk_08;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->unk_000;
    ((GpuContext *)final_render_ctx)->packetCursor = scratch->cursor;
    return 0;
}

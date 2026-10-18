#include "modules/dungeon_ovl_190c800.h"

void draw_effect_and_restore_clip(s32 draw_data, Row_818ED25C_S_80024A5C_5 *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param)
{
    u16 draw_pos[2];
    u16 clear_enabled;
    s32 draw_y;
    s32 rect_y;
    u8 *clip_packet;
    GameWork *page_ptr;
    s16 saved_param;
    u32 tag_mask;
    u8 *pos_or_ot;
    u8 *order_table;
    void *draw_page;
    Row_818ED25C_S_80024A5C_3 *packet_page;
    s16 offset_y;
    void *call_pos;
    s32 call_data;
    void *call_order_table;
    s32 call_param;

    draw_page = g_game_work.unk_000;
    pos_or_ot = screen_pos;
    clip_packet = ((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8D0;
    offset_y = draw_page != (void *)D_801C9E40;
    ((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8D0 = clip_packet + 0xC;
    saved_param = draw_param;
    clear_enabled = clear_rect;
    page_ptr = &g_game_work;
    func_80067E2C(clip_packet, g_game_work.unk_000);
    tag_mask = 0xFF000000U;

    ((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 = (((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 & tag_mask) |
                            (((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8B0 & 0x00FFFFFFU);
    ((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8B0 = (((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8B0 & tag_mask) |
                             ((u32)clip_packet & 0x00FFFFFFU);

    draw_pos[0] = ((Row_818ED25C_S_80024A5C_2 *)pos_or_ot)->unk_00;
    draw_y = ((Row_818ED25C_S_80024A5C_2 *)pos_or_ot)->unk_02;
    pos_or_ot = (u8 *)draw_page + 0x8B0;
    order_table = pos_or_ot;
    if (offset_y != 0) {
        draw_y -= 0xE0;
    }
    call_pos = draw_pos;
    call_param = (s32)((u32)saved_param << 16) >> 16;
    call_order_table = order_table;
    call_data = draw_data;
    draw_pos[1] = draw_y;
    render_rotated_effect_quads(call_pos, call_data, call_order_table, call_param);

    if (clear_enabled != 0) {
        u8 *fill_packet;

        packet_page = g_game_work.unk_000;
        fill_packet = packet_page->unk_8D0;
        packet_page->unk_8D0 = fill_packet + 0x10;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_04 = 0x60000000;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_00.at03.v = 3;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_08 = clip_rect->unk_00;
        rect_y = clip_rect->unk_02;
        if (offset_y != 0) {
            rect_y -= 0xE0;
        }
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_0A = rect_y;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_0C = clip_rect->unk_04;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_00.at00.v = (((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_00.at00.v & tag_mask) |
                                 (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & 0x00FFFFFFU);
        ((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 = (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & tag_mask) |
                            ((u32)fill_packet & 0x00FFFFFFU);
    }

    packet_page = page_ptr->unk_000;
    clip_packet = packet_page->unk_8D0;
    packet_page->unk_8D0 = clip_packet + 0xC;
    func_80067E2C(clip_packet, clip_rect);
    ((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 = (((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 & 0xFF000000U) |
                            (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & 0x00FFFFFFU);
    ((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 = (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & 0xFF000000U) |
                        ((u32)clip_packet & 0x00FFFFFFU);
}

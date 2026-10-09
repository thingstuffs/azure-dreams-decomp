#include "common.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"

/* Draw-environment page reached through gameWork.unk_000: an ordering-table head at +0x8B0 and the
 * packet allocation cursor at +0x8D0 (partial layout; GpuContext does not cover +0x8B0). */
typedef struct DrawPage {
    u8 pad_000[0x8B0];
    u32 order_tag;
    u8 pad_8B4[0x1C];
    u8 *packet_cursor;
} DrawPage;

/* Screen position: x, then y (a page-relative row). */
typedef struct ScreenPos {
    u16 x;
    s16 y;
} ScreenPos;

/* Clip/fill rectangle: origin, then the size word copied verbatim. */
typedef struct ScreenRect {
    u16 x;
    s16 y;
    s32 size;
} ScreenRect;

/* Link packet: tag word (next address + length), then payload. */
typedef struct FillPacket {
    u32 tag;       /* low 24 bits next address; byte 3 = word count (3) */
    u32 command;   /* 0x60000000: monochrome rectangle, black */
    u16 x;
    s16 y;
    s32 size;
} FillPacket;

extern u8 D_801C9E40[16];

extern void func_80024190(void *, s32, void *, s32);
extern void func_80067E2C(void *, void *);

/* Draws at a page-adjusted position with clipping commands and an optional black rectangle.
 * Keeping the page pointer live across setup and spelling the sign extension as one expression
 * reproduce the retail allocation and call-argument order. */
void func_80024B6C(s32 draw_data, ScreenRect *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param)
{
    u16 draw_pos[2];
    u16 clear_enabled;
    s32 draw_y;
    s32 rect_y;
    u8 *clip_packet;
    GameWork *page_ptr;
    s16 saved_param;
    u32 tag_mask;
    ScreenPos *pos_or_ot;
    u8 *order_table;
    DrawPage *draw_page;
    DrawPage *packet_page;
    s16 offset_y;
    void *call_pos;
    s32 call_data;
    void *call_order_table;
    s32 call_param;

    draw_page = gameWork.unk_000;
    pos_or_ot = screen_pos;
    clip_packet = draw_page->packet_cursor;
    offset_y = (void *)draw_page != (void *)D_801C9E40;
    draw_page->packet_cursor = clip_packet + 0xC;
    saved_param = draw_param;
    clear_enabled = clear_rect;
    page_ptr = &gameWork;
    func_80067E2C(clip_packet, gameWork.unk_000);
    tag_mask = 0xFF000000U;

    *(u32 *)clip_packet = (*(u32 *)clip_packet & tag_mask) |
                            (draw_page->order_tag & 0x00FFFFFFU);
    draw_page->order_tag = (draw_page->order_tag & tag_mask) |
                             ((u32)clip_packet & 0x00FFFFFFU);

    draw_pos[0] = pos_or_ot->x;
    draw_y = pos_or_ot->y;
    order_table = (u8 *)draw_page + 0x8B0;
    if (offset_y != 0) {
        draw_y -= 0xE0;
    }
    call_pos = draw_pos;
    call_param = (s32)((u32)saved_param << 16) >> 16;
    call_order_table = order_table;
    call_data = draw_data;
    draw_pos[1] = draw_y;
    func_80024190(call_pos, call_data, call_order_table, call_param);

    if (clear_enabled != 0) {
        FillPacket *fill_packet;

        packet_page = gameWork.unk_000;
        fill_packet = (FillPacket *)packet_page->packet_cursor;
        packet_page->packet_cursor = (u8 *)fill_packet + 0x10;
        fill_packet->command = 0x60000000;
        ((GpuLinkTag *)&fill_packet->tag)->len = 3;
        fill_packet->x = clip_rect->x;
        rect_y = clip_rect->y;
        if (offset_y != 0) {
            rect_y -= 0xE0;
        }
        fill_packet->y = rect_y;
        fill_packet->size = clip_rect->size;
        fill_packet->tag = (fill_packet->tag & tag_mask) |
                                 (*(u32 *)order_table & 0x00FFFFFFU);
        *(u32 *)order_table = (*(u32 *)order_table & tag_mask) |
                            ((u32)fill_packet & 0x00FFFFFFU);
    }

    packet_page = page_ptr->unk_000;
    clip_packet = packet_page->packet_cursor;
    packet_page->packet_cursor = clip_packet + 0xC;
    func_80067E2C(clip_packet, clip_rect);
    *(u32 *)clip_packet = (*(u32 *)clip_packet & 0xFF000000U) |
                            (*(u32 *)order_table & 0x00FFFFFFU);
    *(u32 *)order_table = (*(u32 *)order_table & 0xFF000000U) |
                        ((u32)clip_packet & 0x00FFFFFFU);
}

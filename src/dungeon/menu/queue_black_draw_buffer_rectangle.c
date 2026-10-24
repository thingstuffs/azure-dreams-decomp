#include "common.h"
#include "shared/game_work.h"
#include "dungeon/menu.h"

extern u8 upper_draw_context[16];

extern void AddPrim(void *, void *);
extern void SetDrawArea(void *, void *);


/* Queues drawing commands and a black 64-by-64 rectangle in the active draw buffer. */
void queue_black_draw_buffer_rectangle(s32 draw_param) {
    s32 draw_rect[2];
    s32 rect_y;
    s32 adjust_y;
    u8 *draw_buffer;
    u8 *ordering_table;
    u8 *rect_packet;
    u8 *area_packet;

    draw_rect[0] = 0xC00300;
    draw_rect[1] = 0x400040;
    draw_buffer = g_game_work.draw_buffer;
    adjust_y = draw_buffer != upper_draw_context;
    ordering_table = draw_buffer + 0x8B0;
    area_packet = *(u8 **)(draw_buffer + 0x8D0);
    *(u8 **)(draw_buffer + 0x8D0) = area_packet + 0xC;
    SetDrawArea(area_packet, *(u8 * *)&g_game_work.draw_buffer);
    AddPrim(ordering_table, area_packet);
    draw_nearby_map_markers(ordering_table, draw_param);

    rect_packet = *(u8 **)(g_game_work.draw_buffer + 0x8D0);
    *(u8 **)(g_game_work.draw_buffer + 0x8D0) = rect_packet + 0x10;
    *(s32 *)(rect_packet + 4) = 0x60000000;
    *(s8 *)(rect_packet + 3) = 3;
    *(s32 *)(rect_packet + 8) = draw_rect[0];
    rect_y = *(s16 *)(rect_packet + 0xA);
    if (adjust_y) {
        rect_y -= 0xE0;
    }
    *(s16 *)(rect_packet + 0xA) = rect_y;
    *(s32 *)(rect_packet + 0xC) = draw_rect[1];
    AddPrim(ordering_table, rect_packet);

    area_packet = *(u8 **)(g_game_work.draw_buffer + 0x8D0);
    *(u8 **)(g_game_work.draw_buffer + 0x8D0) = area_packet + 0xC;
    SetDrawArea(area_packet, &draw_rect[0]);
    AddPrim(ordering_table, area_packet);
}

#include "common.h"

extern u8 *D_80083160;
extern u8 D_801C9E40[16];

extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
extern void func_8009DAD8(void *, s32);

/* Queues drawing commands and a black 64-by-64 rectangle in the active draw buffer. */
void func_8009DF0C(s32 draw_param) {
    s32 draw_rect[2];
    s32 rect_y;
    s32 adjust_y;
    u8 *draw_buffer;
    u8 *ordering_table;
    u8 *rect_packet;
    u8 *area_packet;

    draw_rect[0] = 0xC00300;
    draw_rect[1] = 0x400040;
    draw_buffer = D_80083160;
    adjust_y = draw_buffer != D_801C9E40;
    ordering_table = draw_buffer + 0x8B0;
    area_packet = *(u8 **)(draw_buffer + 0x8D0);
    *(u8 **)(draw_buffer + 0x8D0) = area_packet + 0xC;
    func_80067E2C(area_packet, *(u8 * volatile *)&D_80083160);
    func_8006658C(ordering_table, area_packet);
    func_8009DAD8(ordering_table, draw_param);

    rect_packet = *(u8 **)(D_80083160 + 0x8D0);
    *(u8 **)(D_80083160 + 0x8D0) = rect_packet + 0x10;
    *(s32 *)(rect_packet + 4) = 0x60000000;
    *(s8 *)(rect_packet + 3) = 3;
    *(s32 *)(rect_packet + 8) = draw_rect[0];
    rect_y = *(s16 *)(rect_packet + 0xA);
    if (adjust_y) {
        rect_y -= 0xE0;
    }
    *(s16 *)(rect_packet + 0xA) = rect_y;
    *(s32 *)(rect_packet + 0xC) = draw_rect[1];
    func_8006658C(ordering_table, rect_packet);

    area_packet = *(u8 **)(D_80083160 + 0x8D0);
    *(u8 **)(D_80083160 + 0x8D0) = area_packet + 0xC;
    func_80067E2C(area_packet, &draw_rect[0]);
    func_8006658C(ordering_table, area_packet);
}

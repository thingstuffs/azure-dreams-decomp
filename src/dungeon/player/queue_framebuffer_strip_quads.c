#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_D_80083160.h"

typedef struct S_80089588_3 {
    s32 unk_00;
} S_80089588_3;

typedef struct S_80089588_4 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80089588_4;


typedef struct S_80089588_1 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    s16 unk_08;
    u16 unk_0A;
    union { s16 s; s16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80089588_1;

typedef struct S_80089588_2 {
    s32 unk_00;
} S_80089588_2;


struct S_8003E2D8;
typedef struct S_8003E2D8 S_8003E2D8;
extern u8 upper_draw_context[16];
s32 func_8006658C(void *, void *);
s32 func_80067E2C(void *, s32);
s32 func_80067EF4(void *, s32, s32);
s32 func_80067F20(void *, s32, s32, s32, s32);

/* Queue draw settings and horizontal strips for both ordering tables. */
void queue_framebuffer_strip_quads(void) {
    s32 draw_area[2];
    u8 alternate_buffer;
    s16 saved_alternate;
    u16 strip_y;
    u16 other_strip_y;
    void *packet;
    u32 context_slot;

    alternate_buffer = (s32) g_game_work.draw_buffer != (s32) upper_draw_context;
    packet = ((Rec_D_80083160 *)g_game_work.draw_buffer)->unk_8D0;
    func_80067E2C(packet, g_game_work.draw_buffer);
    func_8006658C((u8 *)g_game_work.draw_buffer + 0x7B0, packet);
    packet += 0xC;
    func_80067E2C(packet, g_game_work.draw_buffer);
    func_8006658C((u8 *)g_game_work.draw_buffer + 0x830, packet);
    packet += 0xC;
    func_80067EF4(packet, 0, 0);
    func_8006658C((u8 *)g_game_work.draw_buffer + 0x830, packet);
    packet += 0xC;
    {
        s32 cmd_value;
        cmd_value = 0x2A000000;
        (*(s32 *)((u8 *)packet + 4)) = cmd_value;
        cmd_value = 1;
        (*(s16 *)((u8 *)packet + 0x10)) = cmd_value;
        (*(s16 *)((u8 *)packet + 8)) = cmd_value;
        cmd_value = 0x100;
        (*(s16 *)((u8 *)packet + 0x14)) = cmd_value;
        (*(s16 *)((u8 *)packet + 0xC)) = cmd_value;
    }
    context_slot = (u32) &g_game_work.draw_buffer;
    saved_alternate = alternate_buffer != 0;
    {
        register s32 strip_top;
        if (saved_alternate != 0) {
            (*(u16 *)((u8 *)packet + 0xE)) = 0xE0;
        } else {
            (*(u16 *)((u8 *)packet + 0xE)) = 0x1C0;
        }
    }
    strip_y = (*(u16 *)((u8 *)packet + 0xE));
    (*(s8 *)((u8 *)packet + 3)) = 5;
    (*(u16 *)((u8 *)packet + 0xA)) = strip_y;
    (*(s16 *)((u8 *)packet + 0x16)) = strip_y + 0xE;
    (*(s16 *)((u8 *)packet + 0x12)) = strip_y + 0xE;
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0x18;
    {
        s32 cmd_value;
        cmd_value = 0x2A000000;
        (*(s32 *)((u8 *)packet + 4)) = cmd_value;
        cmd_value = 1;
        (*(s16 *)((u8 *)packet + 0x10)) = cmd_value;
        (*(s16 *)((u8 *)packet + 8)) = cmd_value;
        cmd_value = 0x100;
        (*(s16 *)((u8 *)packet + 0x14)) = cmd_value;
        (*(s16 *)((u8 *)packet + 0xC)) = cmd_value;
    }
    {
        s32 strip_top;
        strip_top = saved_alternate;
        if (strip_top != 0) {
            (*(u16 *)((u8 *)packet + 0xE)) = 0xE0;
        } else {
            (*(u16 *)((u8 *)packet + 0xE)) = 0x1C0;
        }
    }
    other_strip_y = (*(u16 *)((u8 *)packet + 0xE));
    (*(s8 *)((u8 *)packet + 3)) = 5;
    (*(u16 *)((u8 *)packet + 0xA)) = other_strip_y;
    (*(s16 *)((u8 *)packet + 0x16)) = other_strip_y + 0xE;
    (*(s16 *)((u8 *)packet + 0x12)) = other_strip_y + 0xE;
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0x18;
    func_80067EF4(packet, 0, 1);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    func_80067F20(packet, 0, 0, 0x20, 0);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0xC;
    func_80067F20(packet, 0, 0, 0x20, 0);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    draw_area[0] = 0x01C00000;
    draw_area[1] = 0x100100;
    func_80067E2C(packet, (s32) draw_area);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0xC;
    func_80067E2C(packet, (s32) draw_area);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    ((S_80089588_4 *)(((S_80089588_3 *)context_slot)->unk_00))->unk_8D0 = packet;
}

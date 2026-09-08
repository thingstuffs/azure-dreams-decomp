#include "common.h"

typedef struct {
    u8 pad0[0x8D0];
    u8 *cursor;
} DungeonState;

typedef struct {
    u8 pad0[3];
    u8 type;
    u32 command;
    u16 x;
    s16 y;
    u32 wordC;
} DungeonPacket;

typedef struct {
    u16 x;
    s16 y;
    union {
        u32 word4;
        struct {
            u16 z;
            u16 w;
        } half;
    } data;
} DungeonInput;

extern DungeonState *D_80083160[4];
extern u8 D_801C9E40[16];

extern void func_80067E2C(u8 *, DungeonState *);
extern void func_8006658C(u8 *, u8 *);
extern void func_800B84E4(s16 *, s32, u8 *, s32);

/* Draw at the rectangle center and optionally emit a filled rectangle. */
void func_800B835C(s32 draw_value, DungeonInput *rect, u16 fill_rect, u16 draw_mode) {
    DungeonState *initial_state;
    DungeonState *active_state;
    DungeonState **state_slot = &D_80083160[0];
    u8 *draw_list;
    u8 *command_cursor;
    DungeonPacket *fill_packet;
    s16 center[2];
    s32 center_y;
    s32 packet_y;
    s16 offset_y;

    initial_state = D_80083160[0];
    offset_y = initial_state != (DungeonState *)D_801C9E40 ? 1 : 0;
    command_cursor = initial_state->cursor;
    draw_list = (u8 *)initial_state + 0x8B0;
    initial_state->cursor = command_cursor + 0xC;
    func_80067E2C(command_cursor, D_80083160[0]);
    func_8006658C(draw_list, command_cursor);

    center[0] = rect->x + ((s32)(rect->data.half.z << 0x10) >> 0x11);
    center_y = (s32)rect->y + ((s32)(rect->data.half.w << 0x10) >> 0x11);
    if (offset_y) {
        center_y -= 0xE0;
    }
    center[1] = center_y;
    func_800B84E4(center, draw_value, draw_list, draw_mode & 0xFFFF);

    if ((fill_rect & 0xFFFF) != 0) {
        active_state = D_80083160[0];
        fill_packet = (DungeonPacket *)active_state->cursor;
        active_state->cursor = (u8 *)fill_packet + 0x10;
        fill_packet->command = 0x60000000;
        fill_packet->type = 3;
        fill_packet->x = rect->x;
        packet_y = rect->y;
        if (offset_y) {
            packet_y -= 0xE0;
        }
        fill_packet->y = packet_y;
        fill_packet->wordC = rect->data.word4;
        func_8006658C(draw_list, (u8 *)fill_packet);
    }

    active_state = *state_slot;
    command_cursor = active_state->cursor;
    active_state->cursor = command_cursor + 0xC;
    func_80067E2C(command_cursor, rect);
    func_8006658C(draw_list, command_cursor);
}

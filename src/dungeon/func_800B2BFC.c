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

void func_800B835C(s32 arg0, DungeonInput *arg1, u16 arg2, u16 arg3) {
    DungeonState *state;
    DungeonState *state2;
    DungeonState **state_slot = &D_80083160[0];
    u8 *draw;
    u8 *cursor;
    DungeonPacket *packet;
    s16 coords[2];
    s32 var_v1;
    s32 packet_y;
    s16 adjusted;

    state = D_80083160[0];
    adjusted = state != (DungeonState *)D_801C9E40 ? 1 : 0;
    cursor = state->cursor;
    draw = (u8 *)state + 0x8B0;
    state->cursor = cursor + 0xC;
    func_80067E2C(cursor, D_80083160[0]);
    func_8006658C(draw, cursor);

    coords[0] = arg1->x + ((s32)(arg1->data.half.z << 0x10) >> 0x11);
    var_v1 = (s32)arg1->y + ((s32)(arg1->data.half.w << 0x10) >> 0x11);
    if (adjusted) {
        var_v1 -= 0xE0;
    }
    coords[1] = var_v1;
    func_800B84E4(coords, arg0, draw, arg3 & 0xFFFF);

    if ((arg2 & 0xFFFF) != 0) {
        state2 = D_80083160[0];
        packet = (DungeonPacket *)state2->cursor;
        state2->cursor = (u8 *)packet + 0x10;
        packet->command = 0x60000000;
        packet->type = 3;
        packet->x = arg1->x;
        packet_y = arg1->y;
        if (adjusted) {
            packet_y -= 0xE0;
        }
        packet->y = packet_y;
        packet->wordC = arg1->data.word4;
        func_8006658C(draw, (u8 *)packet);
    }

    state2 = *state_slot;
    cursor = state2->cursor;
    state2->cursor = cursor + 0xC;
    func_80067E2C(cursor, arg1);
    func_8006658C(draw, cursor);
}

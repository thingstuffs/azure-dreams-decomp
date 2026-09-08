#include "common.h"

typedef struct {
    u16 x;
    s16 y;
    s32 value;
} Position;

typedef struct {
    u16 x;
    s16 y;
} Coord;

typedef struct {
    u8 pad0[0x8B0];
    u32 ordering_table;
    u8 pad8B4[0x1C];
    u8 *next_packet;
} DungeonState;

typedef struct {
    u32 tag;
    u32 code;
    u16 x;
    s16 y;
    s32 value;
} Packet16;

extern DungeonState *D_80083160[3];
extern u8 D_801C9E40[16];
extern void func_8002405C(void *, s32, s32, u32 *, s32);
extern void func_80067E2C(void *, void *);

void func_80024CD4(s32 arg0, s32 arg1, Position *arg2, Position *arg3,
                   u32 arg4, s32 arg5)
{
    Coord pos;
    u16 make_extra;
    DungeonState *state;
    DungeonState **state_ptr;
    u8 *packet;
    u32 *ordering_table;
    register s32 shifted ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 y;
    s32 call_arg5 = arg5;

    state = D_80083160[0];
    state_ptr = &D_80083160[0];
    packet = state->next_packet;
    shifted = state != (DungeonState *)D_801C9E40;
    state->next_packet = packet + 12;
    make_extra = arg4;

    func_80067E2C(packet, D_80083160[0]);
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
    state->ordering_table = (state->ordering_table & 0xFF000000) |
                            ((u32)packet & 0x00FFFFFF);

    pos.x = arg3->x;
    y = arg3->y;
    ordering_table = &state->ordering_table;
    if (shifted) {
        y -= 0xE0;
    }
    pos.y = y;

    {
        s32 narrowed = (s16)call_arg5;
        func_8002405C(&pos, arg0, arg1, ordering_table, narrowed);
    }

    if (make_extra != 0) {
        Packet16 *extra;
        DungeonState *current;

        current = D_80083160[0];
        extra = (Packet16 *)current->next_packet;
        current->next_packet = (u8 *)extra + 16;
        extra->code = 0x60000000;
        ((u8 *)extra)[3] = 3;
        extra->x = arg2->x;
        y = arg2->y;
        if (shifted) {
            y -= 0xE0;
        }
        extra->y = y;
        extra->value = arg2->value;
        extra->tag = (extra->tag & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
        state->ordering_table = (state->ordering_table & 0xFF000000) |
                                ((u32)extra & 0x00FFFFFF);
    }

    {
        DungeonState *tail_state;

        tail_state = state_ptr[0];
        packet = tail_state->next_packet;
        tail_state->next_packet = packet + 12;
        func_80067E2C(packet, arg2);
    }
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (*ordering_table & 0x00FFFFFF);
    *ordering_table = (*ordering_table & 0xFF000000) |
                      ((u32)packet & 0x00FFFFFF);
}

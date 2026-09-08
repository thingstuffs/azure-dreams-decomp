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

/* Queue drawing with an optional cleared rectangle, then restore the drawing area. */
void func_80024CD4(s32 draw_param_a, s32 draw_param_b, Position *restore_area, Position *draw_pos,
                   u32 clear_area, s32 draw_option)
{
    Coord pos;
    u16 clear_enabled;
    DungeonState *state;
    DungeonState **state_ptr;
    u8 *packet;
    u32 *ordering_table;
    register s32 offset_y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 y;
    s32 saved_option = draw_option;

    state = D_80083160[0];
    state_ptr = &D_80083160[0];
    packet = state->next_packet;
    offset_y = state != (DungeonState *)D_801C9E40;
    state->next_packet = packet + 12;
    clear_enabled = clear_area;

    func_80067E2C(packet, D_80083160[0]);
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
    state->ordering_table = (state->ordering_table & 0xFF000000) |
                            ((u32)packet & 0x00FFFFFF);

    pos.x = draw_pos->x;
    y = draw_pos->y;
    ordering_table = &state->ordering_table;
    if (offset_y) {
        y -= 0xE0;
    }
    pos.y = y;

    {
        s32 signed_option = (s16)saved_option;
        func_8002405C(&pos, draw_param_a, draw_param_b, ordering_table, signed_option);
    }

    if (clear_enabled != 0) {
        Packet16 *clear_packet;
        DungeonState *alloc_state;

        alloc_state = D_80083160[0];
        clear_packet = (Packet16 *)alloc_state->next_packet;
        alloc_state->next_packet = (u8 *)clear_packet + 16;
        clear_packet->code = 0x60000000;
        ((u8 *)clear_packet)[3] = 3;
        clear_packet->x = restore_area->x;
        y = restore_area->y;
        if (offset_y) {
            y -= 0xE0;
        }
        clear_packet->y = y;
        clear_packet->value = restore_area->value;
        clear_packet->tag = (clear_packet->tag & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
        state->ordering_table = (state->ordering_table & 0xFF000000) |
                                ((u32)clear_packet & 0x00FFFFFF);
    }

    {
        DungeonState *tail_state;

        tail_state = state_ptr[0];
        packet = tail_state->next_packet;
        tail_state->next_packet = packet + 12;
        func_80067E2C(packet, restore_area);
    }
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (*ordering_table & 0x00FFFFFF);
    *ordering_table = (*ordering_table & 0xFF000000) |
                      ((u32)packet & 0x00FFFFFF);
}

#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u16 x;
    s16 y;
} Position;

typedef struct {
    u8 pad0[3];
    u8 size;
    u32 code;
    u16 x;
    s16 y;
    u32 data;
} Packet;

typedef struct DrawContext {
    u8 pad[0x8B0];
    u8 ordering_table[0x20];
    Packet *next_packet;
} DrawContext;

extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
extern void func_800B9144(Position *, s32, void *, s16);
extern u8 D_801C9E40[16];

/* Queue a clipped sprite with an optional black background, adjusting Y for the active buffer. */
void func_800B8FC8(s32 sprite, Position *clip_rect, Position *screen_pos, s32 clear_bg, s16 draw_flags)
{
    Position draw_pos;
    DrawContext *context;
    void *draw_context;
    void *ordering_table;
    Packet *area_packet;
    u16 saved_clear_bg;
    s16 shift_y;
    s32 y;

    context = (DrawContext *)gameWork.unk_000;
    saved_clear_bg = clear_bg;
    shift_y = context != (DrawContext *)D_801C9E40;
    area_packet = context->next_packet;
    ordering_table = context->ordering_table;
    context->next_packet = (Packet *)((u8 *)area_packet + 0xC);
    draw_context = gameWork.unk_000;
    func_80067E2C(area_packet, draw_context);
    func_8006658C(ordering_table, area_packet);

    draw_pos.x = screen_pos->x;
    y = screen_pos->y;
    {
        DrawContext **context_slot;

        if (shift_y) {
            y -= 0xE0;
        }
        context_slot = (DrawContext **)&gameWork.unk_000;
        draw_pos.y = y;
        func_800B9144(&draw_pos, sprite, ordering_table, draw_flags);

        if ((u16)saved_clear_bg != 0) {
            Packet *clear_packet;

            context = *context_slot;
            clear_packet = context->next_packet;
            context->next_packet = (Packet *)((u8 *)clear_packet + 0x10);
            clear_packet->code = 0x60000000;
            clear_packet->size = 3;
            clear_packet->x = clip_rect->x;
            y = clip_rect->y;
            if (shift_y) {
                y -= 0xE0;
            }
            clear_packet->y = y;
            clear_packet->data = *(u32 *)((u8 *)clip_rect + 4);
            func_8006658C(ordering_table, clear_packet);
        }

        context = *context_slot;
        area_packet = context->next_packet;
        context->next_packet = (Packet *)((u8 *)area_packet + 0xC);
        func_80067E2C(area_packet, clip_rect);
        func_8006658C(ordering_table, area_packet);
    }
}


#include "common.h"

typedef struct {
    char pad0[0x8D0];
    u8 *field_8D0;
} Ctx;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_Rect;

typedef struct {
    char pad0[0xB8];
    s16 x;
    s16 y;
    char pad_BC[4];
    u32 index;
} S_Arg1;

typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 h;
} S_Stack;

extern u8 D_80080000[];
extern u8 D_801C9E40[16];
extern void func_80066890(u8 *dst, S_Stack *rect, s32 x, s32 y);
extern void func_8006658C(void *addr, u8 *cursor);

/* Queue a rectangle copy when both source and destination fit on screen. */
void func_800C96E8(S_Rect *copy_rect, S_Arg1 *source) {
    S_Stack source_rect;
    s16 source_y, width, source_x, height;
    s32 dest_y, second_buffer, dest_x, buffer_y;
    u8 *packet;
    u8 *cursor;
    Ctx **active_ctx;

    active_ctx = (Ctx **)((u8 *)&D_80080000 + 0x3160);
    cursor = (*(Ctx **)((u8 *)&D_80080000 + 0x3160))->field_8D0;
    second_buffer = *(Ctx **)((u8 *)&D_80080000 + 0x3160) != (Ctx *)D_801C9E40;
    if (source->index < 480) {
        source_x = source->x;
        source_y = source->y;
        dest_x = source_x + copy_rect->w;
        dest_y = source_y + copy_rect->h;
        if (dest_x >= 0) {
            width = copy_rect->x;
            if (((dest_x + width) < 320) && (dest_y >= 0)) {
                height = copy_rect->y;
                if (((dest_y + height) < 224) && (source_x >= 0) && ((source_x + width) < 320) && (source_y >= 0) && ((source_y + height) < 224)) {
                    source_rect.x = source->x;
                    buffer_y = source->y;
                    if ((s16)second_buffer) {
                        buffer_y += 224;
                    }
                    source_rect.y = buffer_y;
                    source_rect.w = copy_rect->x;
                    source_rect.h = copy_rect->y;
                    func_80066890(cursor, &source_rect, source_x + copy_rect->w, (s16)buffer_y + copy_rect->h);
                    packet = cursor;
                    cursor += 24;
                    func_8006658C((u8 *)(*(Ctx **)((u8 *)&D_80080000 + 0x3160)) + ((source->index * 4) + 0xB0), packet);
                }
            }
        }
    }
    (*active_ctx)->field_8D0 = cursor;
}

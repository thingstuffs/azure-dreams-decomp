#include "common.h"
#include "shared/game_work.h"


typedef struct {
    struct S_Ctx *ctx;
} CtxHolder;

typedef struct S_Ctx {
    u8 pad0[0x82C];
    s32 field_82C;
    u8 pad1[0x8D0 - 0x830];
    void *cur;
} S_Ctx;

typedef struct PacketTag {
    unsigned addr : 24;
    unsigned len : 8;
} PacketTag;

#define setaddr(packet, address) (((PacketTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
(setaddr((primitive), getaddr(ordering_table)), \
    setaddr((ordering_table), (primitive)))

extern void func_80066758(void *prim);
extern void func_80066640(void *prim, s32 flag);
extern s16 func_8006649C(s32 a0, s32 a1);
extern s32 func_80066460(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80067F20(void *prim, s32 a1, s32 a2, s32 a3, s32 a4);

/* Builds layered sprite tiles and texture-page commands for each linked node. */
s32 func_8008A794(void *node_data, void *scroll_state)
{
    CtxHolder *ctx_ptr;
    s32 layer_offset;
    s32 tile_row;
    s32 tile_col;
    s32 tile_y;
    s32 page_x;
    u16 scroll_y;
    s32 screen_y;
    s16 screen_x;
    s32 clut_x;
    void *sprite;
    void *draw_mode;
    void *next_node;
    struct S_Ctx *ctx;

    ctx_ptr = (CtxHolder *)&gameWork.unk_000;

    do {
        layer_offset = 2;
        do {
            tile_row = 0;
            do {
                tile_col = 1;
                tile_y = tile_row << 8;
                page_x = 0x280;
                do {
                    sprite = ctx_ptr->ctx->cur;
                    ctx_ptr->ctx->cur = (u8 *)sprite + 0x14;
                    *(s32 *)((u8 *)sprite + 4) = 0x505050;
                    func_80066758(sprite);
                    func_80066640(sprite, 1);
                    clut_x = 0;
                    screen_x = tile_col;
                    screen_x <<= 8;
                    screen_x += layer_offset;
                    *(s16 *)((u8 *)sprite + 8) = screen_x;
                    scroll_y = *(u16 *)((u8 *)scroll_state + 6);
                    *(s16 *)((u8 *)sprite + 16) = 0x100;
                    *(s16 *)((u8 *)sprite + 18) = 0x100;
                    *(s16 *)((u8 *)sprite + 12) = 0;
                    screen_y = (tile_y - scroll_y) + layer_offset;
                    *(s16 *)((u8 *)sprite + 10) = screen_y;
                    *(s16 *)((u8 *)sprite + 14) = func_8006649C(clut_x, 0x1F0);
                    addPrim(&ctx_ptr->ctx->field_82C, sprite);

                    ctx = ctx_ptr->ctx;
                    draw_mode = ctx->cur;
                    ctx->cur = (u8 *)draw_mode + 0xC;
                    func_80067F20(draw_mode, 0, 0,
                                  func_80066460(1, 3, page_x, tile_y) & 0xFFFF, 0);
                    tile_col -= 1;
                    addPrim(&ctx_ptr->ctx->field_82C, draw_mode);
                    page_x -= 0x80;
                } while (tile_col >= 0);
                tile_row += 1;
            } while (tile_row < 2);
            layer_offset -= 1;
        } while (layer_offset >= 0);

        next_node = *(void **)((u8 *)node_data - 8);
        if (next_node == 0) {
            break;
        }
        node_data = (u8 *)next_node + 0x20;
        scroll_state = *(void **)((u8 *)next_node + 8);
    } while (1);
    return 0;
}

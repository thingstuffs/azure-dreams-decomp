#include "common.h"

typedef struct S_Ctx {
    u8 pad0[0x82C];
    s32 field_82C;
    u8 pad1[0x8D0 - 0x830];
    void *cur;
} S_Ctx;

extern S_Ctx *D_80083160;

extern void func_80066758(void *prim);
extern void func_80066640(void *prim, s32 flag);
extern s16 func_8006649C(s32 a0, s32 a1);
extern s32 func_80066460(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80067F20(void *prim, s32 a1, s32 a2, s32 a3, s32 a4);

/* Builds layered sprite tiles and texture-page commands for each linked node. */
s32 func_8008A794(void *node_data, void *scroll_state)
{
    S_Ctx **ctx_ptr;
    s32 addr_mask;
    s32 tag_mask;
    register s32 layer_offset ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 tile_row ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 tile_col;
    s32 tile_y;
    s32 page_x;
    u16 scroll_y;
    s32 screen_y;
    s32 screen_x;
    s32 clut_x;
    void *sprite;
    void *draw_mode;
    void *next_node;
    S_Ctx *ctx;

    ctx_ptr = &D_80083160;
    addr_mask = 0xFFFFFF;
    tag_mask = 0xFF000000;

restart:
    layer_offset = 2;
    do {
        tile_row = 0;
        do {
            tile_col = 1;
            tile_y = tile_row << 8;
            addr_mask += tile_col;
            addr_mask -= tile_col;
            page_x = 0x280;
            addr_mask += page_x;
            addr_mask -= page_x;
            do {
                sprite = (*ctx_ptr)->cur;
                (*ctx_ptr)->cur = (u8 *)sprite + 0x14;
                *(s32 *)((u8 *)sprite + 4) = 0x505050;
                func_80066758(sprite);
                func_80066640(sprite, 1);
                clut_x = 0;
                ASM_KEEP(clut_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
                *(u32 *)sprite = (*(u32 *)sprite & tag_mask) | ((*ctx_ptr)->field_82C & addr_mask);
                *(volatile s32 *)&(*ctx_ptr)->field_82C =
                    ((*ctx_ptr)->field_82C & tag_mask) | ((u32)sprite & addr_mask);

                ctx = *(S_Ctx *volatile *)ctx_ptr;
                draw_mode = ctx->cur;
                ctx->cur = (u8 *)draw_mode + 0xC;
                func_80067F20(draw_mode, 0, 0,
                              func_80066460(1, 3, page_x, tile_y) & 0xFFFF, 0);
                tile_col -= 1;
                *(u32 *)draw_mode = (*(u32 *)draw_mode & tag_mask) | ((*ctx_ptr)->field_82C & addr_mask);
                page_x -= 0x80;
                (*ctx_ptr)->field_82C = ((*ctx_ptr)->field_82C & tag_mask) | ((u32)draw_mode & addr_mask);
            } while (tile_col >= 0);
            tile_row += 1;
        } while (tile_row < 2);
        layer_offset -= 1;
    } while (layer_offset >= 0);

    next_node = *(void **)((u8 *)node_data - 8);
    if (next_node != 0) {
        node_data = (u8 *)next_node + 0x20;
        scroll_state = *(void **)((u8 *)next_node + 8);
        goto restart;
    }
    return 0;
}

#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_80053A88_TILE {
    u32 tag;
    u32 code;
    s16 x0;
    s16 y0;
    s16 w;
    s16 h;
} S_80053A88_TILE;
typedef struct S_80053A88_DRTPAGE {
    u32 tag;
    u16 code[4];
} S_80053A88_DRTPAGE;

typedef struct S_80053A88_Node {
    u8 pad_00[0x8];
    u32 unk8;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    s16 unk14;
    u16 unk16;
} S_80053A88_Node;
extern void SetTile(S_80053A88_TILE *p);
extern void SetSemiTrans(void *p, s32 abe);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetDrawMode(S_80053A88_DRTPAGE *p, s32 a1, s32 a2, s32 a3, s32 a4);

/* Builds tile and draw-mode packets for each node and links enabled packets into the draw list. */
s32 func_80053A88(S_80053A88_Node *first_node)
{
    GameWork *work;
    S_80053A88_Node *node;
    GpuContext *draw_base;
    S_80053A88_TILE *tile;
    S_80053A88_DRTPAGE *draw_mode;
    s32 tpage;
    void *next_link;
    u32 addr_mask;
    u32 tag_mask;
    node = first_node;
    work = &gameWork;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;
    do {
        {
            draw_base = ((GpuContext *)work->unk_000);
            tile = (S_80053A88_TILE *)draw_base->packetCursor;
            draw_base->packetCursor = (void *)(((u8 *)tile) + 0x10);
            tile->x0 = node->unkC;
            tile->y0 = node->unkE;
            tile->w = node->unk10;
            tile->h = node->unk12;
            tile->code = node->unk8;
            SetTile(tile);
            if (node->unk16 & 1) {
                SetSemiTrans(tile, 1);
            }
            if (!(node->unk16 & 2)) {
                tile->tag = (tile->tag & tag_mask) | (((GpuContext *)work->unk_000)->orderTag074 & addr_mask);
                next_link = work->unk_000;
                ((GpuContext *)next_link)->orderTag074 = (((GpuContext *)next_link)->orderTag074 & tag_mask)
                | (((u32)tile) & addr_mask);
            }
            draw_base = ((GpuContext *)work->unk_000);
            draw_mode = (S_80053A88_DRTPAGE *)draw_base->packetCursor;
            draw_base->packetCursor = (void *)(((u8 *)draw_mode) + 0xC);
            tpage = GetTPage(0, node->unk14, 0, 0);
            SetDrawMode(draw_mode, 0, 0, tpage & 0xFFFF, 0);
            if (!(node->unk16 & 2)) {
                draw_mode->tag = (draw_mode->tag & tag_mask) | (((GpuContext *)work->unk_000)->orderTag074 & addr_mask);
                next_link = work->unk_000;
                ((GpuContext *)next_link)->orderTag074 = (((GpuContext *)next_link)->orderTag074 & tag_mask)
                | (((u32)draw_mode) & addr_mask);
            }
            next_link = *((void **)(((u8 *)node) - 8));
            node = (S_80053A88_Node *)(((u8 *)next_link) + 0x20);
        }
    } while (next_link != 0);
    return 0;
}

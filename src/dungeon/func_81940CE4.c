#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

/* The effect point's record (the object header precedes it). */
typedef struct PointRecord {
    u8 pad_00[8];
    u32 color;          /* r/g/b word copied into the tile */
    u8 pad_0C[0x26];
    s16 brightness;     /* 0x80 = full */
} PointRecord;

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch800244E4 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad1C[4];
    u32 *ot;            /* ordering table */
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;          /* ordering table slot */
} Scratch800244E4;

/* Shaded tile primitive (code 0x6A, 3 words). */
typedef struct Packet800244E4 {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet800244E4;

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Projects linked points and queues shaded tiles with draw-mode packets. */
s32 func_800244E4(PointRecord *first_point, EntityRec *first_position)
{
    PointRecord *point = first_point;
    EntityRec *position = first_position;
    GameWork *render_state = &gameWork;
    GpuContext *render_ctx = (GpuContext *)render_state->unk_000;
    u8 *packet_start;
    Scratch800244E4 *scratch =
        (Scratch800244E4 *)0x1F800000;
    Packet800244E4 *tile;
    Packet800244E4 *draw_mode;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (Packet800244E4 *)scratch->cursor;
        scratch->x = position->x.w.i;
        scratch->y = position->y.w.i;
        scratch->z = position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)tile + 8,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * point->brightness;
            tile->b = (color_value / 128);

            ((u8 *)tile)[3] = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (Packet800244E4 *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        /* the preceding header's +0x18 holds the next node */
        next_node = (ObjectNodeHeader *)((ObjectNodeHeader *)point - 1)->unk_18;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->unk_08;
            continue;
        }

        break;
    }

    ((GpuContext *)render_state->unk_000)->packetCursor = scratch->cursor;
    return 0;
}

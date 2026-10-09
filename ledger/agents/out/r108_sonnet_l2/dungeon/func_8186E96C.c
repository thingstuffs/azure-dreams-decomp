#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Position the point is projected from: three 4-byte slots, only the second halfword of each is used. */
typedef struct PointPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    u16 pad_08;
    u16 z;
} PointPosition;

/* The effect point's record (the object header precedes it). */
typedef struct PointRecord {
    u8 pad_00[8];
    u32 color;          /* r/g/b/code word copied into the tile */
    u8 pad_0C[0x26];
    s16 brightness;     /* 0x100 = full */
} PointRecord;

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch8002416C {
    u16 x;
    u16 y;
    u16 z;
    u8 pad_06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad_1C[4];
    u32 *ot;            /* ordering table */
    u8 pad_24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad_98[0x28];
    u32 index;          /* ordering table slot */
} Scratch8002416C;

/* Shaded point primitive (code 0x6A, 3 words). */
typedef struct Packet8002416C {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet8002416C;

/* Retail 8186E96C (func_8002416C): projects each linked point and queues a brightness-scaled shaded point
 * followed by a draw-mode packet for it. */
s32 func_8002416C(PointRecord *start_node, PointPosition *start_coords)
{
    GpuContext **state_ptr;
    Scratch8002416C *scratch;
    GpuContext *render_state;
    GpuContext *final_state;
    Packet8002416C *packet;
    PointRecord *node;
    PointPosition *coords;
    ObjectNodeHeader *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (GpuContext **)&gameWork;
    render_state = *state_ptr;
    scratch = (Scratch8002416C *)0x1F800000;

    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;

    for (;;) {
        coord_x = coords->x;
        packet = (Packet8002416C *)scratch->cursor;
        scratch->x = coord_x;
        scratch->y = coords->y;
        scratch->z = coords->z;
        scratch->cursor = (u8 *)packet + 0xC;

        depth_index = func_80065420(scratch, (u8 *)packet + 8, &scratch->xy, &scratch->depth);
        scratch->index = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            Packet8002416C *mode_packet;

            *(u32 *)&packet->r = node->color;
            color_or_tpage = packet->r * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->r = color_or_tpage >> 8;

            color_or_tpage = packet->g * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->g = color_or_tpage >> 8;

            color_or_tpage = packet->b * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->b = color_or_tpage >> 8;
            ((u8 *)packet)[3] = 2;
            packet->code = 0x6A;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)packet & 0x00FFFFFF);

            mode_packet = (Packet8002416C *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            color_or_tpage = func_80066460(0, 1, 0, 0);
            func_80067F20(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        prev_entry = (ObjectNodeHeader *)((ObjectNodeHeader *)node - 1)->unk_18;
        node = (PointRecord *)(prev_entry + 1);
        if (prev_entry == 0) {
            break;
        }
        coords = prev_entry->unk_08;
    }

    final_state = *state_ptr;
    final_state->packetCursor = scratch->cursor;
    return 0;
}

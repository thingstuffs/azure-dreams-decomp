/* Selector 59, retail file [0x1990D98, 0x1990FE8); complete callable clone. */
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

extern u32 func_80065420();
extern s32 func_80066460();
extern s32 func_80067F20();

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
    u32 color;          /* r/g/b/code word copied into the packet */
    u8 pad_0C[0x26];
    s16 scale;          /* colour scale: numerator */
    s16 scale_max;      /* colour scale: denominator */
} PointRecord;

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch80024598 {
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
} Scratch80024598;

/* Shaded point primitive (code 0x6A, 3 words). */
typedef struct Packet80024598 {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet80024598;

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 func_80024598(PointRecord *record, PointPosition *position)
{
    GpuContext **state_ptr;
    Scratch80024598 *scratch;
    GpuContext *render_state;
    Packet80024598 *packet;
    Packet80024598 *mode_packet;
    ObjectNodeHeader *node;
    u8 blue;
    u32 depth_index;

    render_state = *(GpuContext **)&gameWork;
    state_ptr = (GpuContext **)&gameWork;
    scratch = (Scratch80024598 *)0x1F800000;
    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;
    do {
        packet = (Packet80024598 *)scratch->cursor;
        scratch->x = position->x;
        scratch->y = position->y;
        scratch->z = position->z;
        scratch->cursor = (u8 *)packet + 0xC;

        depth_index = func_80065420(scratch, (u8 *)packet + 8, &scratch->xy, &scratch->depth);
        scratch->index = depth_index;
        if (depth_index < 0x1E0U) {
            *(u32 *)&packet->r = record->color;
            packet->r = (packet->r * record->scale) / record->scale_max;
            packet->g = (packet->g * record->scale) / record->scale_max;
            blue = (packet->b * record->scale) / record->scale_max;
            ((u8 *)packet)[3] = 2;
            packet->code = 0x6A;
            packet->b = blue;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)packet & 0x00FFFFFF);

            mode_packet = (Packet80024598 *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            func_80067F20(mode_packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        node = (ObjectNodeHeader *)((ObjectNodeHeader *)record - 1)->unk_18;
        record = (PointRecord *)(node + 1);
        if (node == 0) {
            break;
        }
        position = node->unk_08;
    } while (1);
    (*state_ptr)->packetCursor = scratch->cursor;
    return 0;
}

#include "common.h"
#include "shared/dungeon_effect_views.h"
#include "shared/entity.h"
/* Selector 59, retail file [0x1990D98, 0x1990FE8); complete callable clone. */
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

extern u32 func_80065420();

/* Position the point is projected from: three 4-byte slots, only the second halfword of each is used. */

/* The effect point's record (the object header precedes it). */

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Bank1990800_1990d98_Scratch80024598 {
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
} Bank1990800_1990d98_Scratch80024598;

/* Shaded point primitive (code 0x6A, 3 words). */

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 project_scaled_colored_point(ScaledPointRecord *record, EntityRec *position)
{
    GpuContext **state_ptr;
    Bank1990800_1990d98_Scratch80024598 *scratch;
    GpuContext *render_state;
    PointPacket *packet;
    PointPacket *mode_packet;
    ObjectNodeHeader *node;
    u8 blue;
    u32 depth_index;

    render_state = *(GpuContext **)&g_game_work;
    state_ptr = (GpuContext **)&g_game_work;
    scratch = (Bank1990800_1990d98_Scratch80024598 *)0x1F800000;
    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;
    do {
        packet = (PointPacket *)scratch->cursor;
        scratch->x = (u16)position->x.w.i;
        scratch->y = (u16)position->y.w.i;
        scratch->z = (u16)position->z.w.i;
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

            mode_packet = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            func_80067F20(mode_packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        node = ((ObjectNodeHeader *)record - 1)->chain_next;
        record = (ScaledPointRecord *)(node + 1);
        if (node == 0) {
            break;
        }
        position = node->unk_08;
    } while (1);
    (*state_ptr)->packetCursor = scratch->cursor;
    return 0;
}


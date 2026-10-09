#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"



extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);


   /* state in func_800241EC */

typedef struct S_800241EC_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_800241EC_1;   /* scratch in func_800241EC */

typedef struct S_800241EC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800241EC_2;   /* input in func_800241EC */

typedef struct S_800241EC_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800241EC_3;   /* packet in func_800241EC */

typedef struct S_800241EC_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800241EC_4_pre;   /* the 0x8 bytes before node in func_800241EC, addressed as node[-1] */

typedef struct S_800241EC_4 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_800241EC_4;   /* node in func_800241EC */

typedef struct S_800241EC_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_800241EC_5;   /* previous in func_800241EC */

   /* final_state in func_800241EC */

typedef struct { u32 addr:24; u32 length:8; } PacketTag;

/* Project linked nodes and enqueue shaded point primitives with their draw modes. */
s32 func_800241EC(void *start_node, void *start_coords)
{
    u8 **state_ptr;
    u8 *scratch;
    u8 *render_state;
    u8 *final_state;
    u8 *packet_end;
    u8 *packet;
    u8 *node;
    u8 *coords;
    void *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (u8 **)((u8 *)(&gameWork));
    render_state = *(u8 **)((u8 *)(&gameWork));
    scratch = (u8 *)0x1F800000;

    *(u8 * *)(scratch + 0x18) = ((GpuContext *)render_state)->packetCursor;
    ((S_800241EC_1 *)scratch)->unk_20.p = render_state + 0xB0;

    for (;;) {
        coord_x = ((S_800241EC_2 *)coords)->unk_02;
        packet = *(u8 * *)(scratch + 0x18);
        ((S_800241EC_1 *)scratch)->unk_00 = coord_x;
        ((S_800241EC_1 *)scratch)->unk_02 = ((S_800241EC_2 *)coords)->unk_06;
        ((S_800241EC_1 *)scratch)->unk_04 = ((S_800241EC_2 *)coords)->unk_0A;
        *(u8 * *)(scratch + 0x18) = packet + 0xC;

        depth_index = func_80065420(scratch, packet + 8, scratch + 0x90,
                             scratch + 0x94);
        ((S_800241EC_1 *)scratch)->unk_C0 = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            s32 texture_depth;
            s32 blend_mode;
            u32 page_x;
            s32 opcode;
            u8 *mode_packet;

            ((S_800241EC_3 *)packet)->unk_04.at00.v = ((S_800241EC_4 *)node)->unk_08;
            color_or_tpage = ((S_800241EC_3 *)packet)->unk_04.at00u.v * ((S_800241EC_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((S_800241EC_3 *)packet)->unk_04.at00u.v = color_or_tpage >> 8;

            color_or_tpage = ((S_800241EC_3 *)packet)->unk_04.at01.v * ((S_800241EC_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((S_800241EC_3 *)packet)->unk_04.at01.v = color_or_tpage >> 8;

            color_or_tpage = ((S_800241EC_3 *)packet)->unk_04.at02.v * ((S_800241EC_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
                texture_depth = 0;
            } else {
                texture_depth = 0;
            }
            blend_mode = 1;
            ((S_800241EC_3 *)packet)->unk_04.at02.v = color_or_tpage >> 8;
            ((S_800241EC_3 *)packet)->unk_00.at03.v = 2;
            opcode = 0x6A;
            page_x = texture_depth;
            ((S_800241EC_3 *)packet)->unk_04.at03.v = opcode;

            ((PacketTag *)packet)->addr =
                ((PacketTag *)((u8 *)(((S_800241EC_1 *)scratch)->unk_20.p2) + (((S_800241EC_1 *)scratch)->unk_C0 * 4)))->addr;
            {
                u32 *ot_entry;
                u32 ot_tag;
                u32 packet_addr;

                ot_entry = (u32 *)(((S_800241EC_1 *)scratch)->unk_C0 << 2);
                ot_entry = (u32 *)((u32)ot_entry +
                                (u32)((S_800241EC_1 *)scratch)->unk_20.p2);
                ot_tag = *ot_entry;
                *ot_entry = ((u32)((ot_tag & 0xFF000000) | ((u32)((u32)packet & 0x00FFFFFF))));
            }

            mode_packet = *(u8 * *)(scratch + 0x18);
            ((S_800241EC_1 *)scratch)->unk_18 = mode_packet + 0xC;
            color_or_tpage = func_80066460(texture_depth, blend_mode, page_x, texture_depth);
            func_80067F20(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((PacketTag *)mode_packet)->addr =
                ((PacketTag *)((u8 *)(((S_800241EC_1 *)scratch)->unk_20.p2) + (((S_800241EC_1 *)scratch)->unk_C0 * 4)))->addr;
            mode_packet = (u8 *)((u32)mode_packet & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((S_800241EC_1 *)scratch)->unk_20.p2) + (((S_800241EC_1 *)scratch)->unk_C0 * 4))) =
                ((*(u32 *)((u8 *)(((S_800241EC_1 *)scratch)->unk_20.p2) + (((S_800241EC_1 *)scratch)->unk_C0 * 4))) & 0xFF000000) |
                (u32)mode_packet;
        }

        prev_entry = ((S_800241EC_4_pre *)node)[-1].unk_00;
        node = (u8 *)prev_entry + 0x20;
        if (prev_entry == 0) {
            break;
        }
        coords = ((S_800241EC_5 *)prev_entry)->unk_08;
    }

    final_state = *state_ptr;
    packet_end = ((S_800241EC_1 *)scratch)->unk_18;
    ((GpuContext *)final_state)->packetCursor = packet_end;
    return 0;
}

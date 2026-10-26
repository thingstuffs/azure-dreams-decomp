/* Builds colored gradient lines from linked nodes and inserts them in depth order. */
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_800BFFF4_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800BFFF4_0_pre;   /* the 0x8 bytes before node in draw_depth_sorted_gradient_lines, addressed as node[-1] */

typedef struct S_800BFFF4_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
} S_800BFFF4_0;   /* node in draw_depth_sorted_gradient_lines */


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct PacketTag { unsigned addr : 24; unsigned len : 8; u8 r0; u8 g0; u8 b0; u8 code; } PacketTag;
#define setaddr(packet, address) (((PacketTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) (setaddr((primitive), getaddr(ordering_table)), setaddr((ordering_table), (primitive)))
typedef union PackedColor { u32 word; struct { u8 r; u8 g; u8 b; u8 code; } channel; } PackedColor;
typedef struct LineG2 { u32 tag; PackedColor color0; s16 x0; s16 y0; PackedColor color1; s16 x1; s16 y1; } LineG2;

/* Writes the packed start and end colors into the line primitive. */
static __inline__ void init_line_colors(LineG2 *line, u32 color0, u32 color1) { line->color0.word = color0; line->color1.word = color1; }
s32 RotTransPers(void *, void *, void *, void *);
s32 GetTPage(s32, s32, s32, s32);
void SetSemiTrans(LineG2 *, s32);
void SetLineG2(LineG2 *);
void SetDrawMode(void *, s32, s32, s32, s32);

/* Draw depth-sorted gradient lines for the linked nodes. */
s32 draw_depth_sorted_gradient_lines(u8 *node)
{
    u16 endpoint[4];
    s32 projection_param;
    s32 projection_flags;
    GameWork *town;
    GpuContext *render;
    LineG2 *line;
    u8 *draw_mode;
    u8 *next_node;
    s16 start_depth;
    s32 mean_depth;
    s32 ot_offset;
    s32 zero;

    town = &g_game_work;
    do {
        line = (LineG2 *)((GpuContext *)town->draw_buffer)->packetCursor;
        ((GpuContext *)town->draw_buffer)->packetCursor = (u8 *)line + 0x14;
        init_line_colors(line, 0x202020, 0);
        SetLineG2(line);
        SetSemiTrans(line, 1);
        endpoint[0] = ((S_800BFFF4_0 *)node)->unk_1E;
        endpoint[1] = ((S_800BFFF4_0 *)node)->unk_22;
        endpoint[2] = ((S_800BFFF4_0 *)node)->unk_26;
        start_depth = RotTransPers(endpoint, &line->x0, &projection_param, &projection_flags);
        mean_depth = (start_depth + RotTransPers(node + 0xC, &line->x1, &projection_param, &projection_flags)) >> 1;
        zero = 0;
        if ((u16)mean_depth < 0x1E0U) {
            ot_offset = (s16)mean_depth * 4;
            addPrim((u8 *)(ot_offset + (long)((GpuContext *)town->draw_buffer)) + 0xB0, line);
            render = ((GpuContext *)town->draw_buffer);
            draw_mode = render->packetCursor;
            render->packetCursor = draw_mode + 0xC;
            SetDrawMode(draw_mode, 0, 0, GetTPage(zero, 1, zero, zero) & 0xFFFF, 0);
            addPrim((u8 *)(ot_offset + (long)((GpuContext *)town->draw_buffer)) + 0xB0, draw_mode);
        }
        next_node = ((S_800BFFF4_0_pre *)node)[-1].unk_00;
        if (next_node != 0) {
            node = next_node + 0x20;
            continue;
        }
        break;
    } while (1);
    return 0;
}

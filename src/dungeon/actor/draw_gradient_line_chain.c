/* Selector 49 bank (DUNGEON file 0x1954800 loaded at 0x80024000), retail
 * file [0x1954F40, 0x1955128).  The 488 retail bytes are identical, word for
 * word, to TOWN file 0x42894 (town row draw_depth_sorted_gradient_lines, src/town/func_800C2894.c):
 * the same source linked into a dungeon bank.  Evidence:
 * docs/evidence/r121_rem_opus.md. */
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "dungeon/actor.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"

typedef struct S_80024740_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
} S_80024740_0;   /* node in draw_gradient_line_chain */


typedef struct PacketTag { unsigned addr : 24; unsigned len : 8; u8 r0; u8 g0; u8 b0; u8 code; } PacketTag;
#define setaddr(packet, address) (((PacketTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) (setaddr((primitive), getaddr(ordering_table)), setaddr((ordering_table), (primitive)))
typedef union PackedColor { u32 word; struct { u8 r; u8 g; u8 b; u8 code; } channel; } PackedColor;
typedef struct LineG2 { u32 tag; PackedColor color0; s16 x0; s16 y0; PackedColor color1; s16 x1; s16 y1; } LineG2;

/* Writes the packed start and end colors into the line primitive. */
static __inline__ void init_line_colors(LineG2 *line, u32 color0, u32 color1) { line->color0.word = color0; line->color1.word = color1; }

/* Draw depth-sorted gradient lines for the linked nodes. */
s32 draw_gradient_line_chain(S_80024740_0 *node)
{
    SVECTOR endpoint;
    s32 projection_param;
    s32 projection_flags;
    GameWork *town;
    GpuContext *render;
    LineG2 *line;
    DR_MODE *draw_mode;
    ObjectNodeHeader *next_node;
    s16 start_depth;
    s32 mean_depth;
    s32 ot_offset;
    s32 zero;

    town = &g_game_work;
    do {
        line = ((GpuContext *)town->draw_buffer)->packetCursor;
        ((GpuContext *)town->draw_buffer)->packetCursor = (u8 *)line + 0x14;
        init_line_colors(line, 0x202020, 0);
        SetLineG2(line);
        SetSemiTrans(line, 1);
        endpoint.vx = node->unk_1E;
        endpoint.vy = node->unk_22;
        endpoint.vz = node->unk_26;
        start_depth = RotTransPers(&endpoint, (s32 *)&line->x0, &projection_param, &projection_flags);
        mean_depth = (start_depth + RotTransPers((u8 *)node + 0xC, (s32 *)&line->x1, &projection_param,
                                                 &projection_flags)) >> 1;
        zero = 0;
        if ((u16)mean_depth < 0x1E0U) {
            ot_offset = (s16)mean_depth * 4;
            addPrim((u8 *)(ot_offset + (long)((GpuContext *)town->draw_buffer)) + 0xB0, line);
            render = town->draw_buffer;
            draw_mode = render->packetCursor;
            render->packetCursor = draw_mode + 1;
            SetDrawMode(draw_mode, 0, 0, GetTPage(zero, 1, zero, zero) & 0xFFFF, 0);
            addPrim((u8 *)(ot_offset + (long)((GpuContext *)town->draw_buffer)) + 0xB0, draw_mode);
        }
        next_node = NODE_HEADER(node)->chain_next;
        if (next_node != 0) {
            node = NODE_BODY(next_node);
            continue;
        }
        break;
    } while (1);
    return 0;
}

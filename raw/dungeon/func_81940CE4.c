#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

   /* ctx in func_800244E4 */

typedef struct S_800244E4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800244E4_1;   /* input in func_800244E4 */

typedef struct S_800244E4_2 {
    u8 pad_00[0x3];
    u8 unk_03;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800244E4_2;   /* packet in func_800244E4 */

typedef struct S_800244E4_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800244E4_3_pre;   /* the 0x8 bytes before cur in func_800244E4, addressed as cur[-1] */

typedef struct S_800244E4_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_800244E4_3;   /* cur in func_800244E4 */

typedef struct S_800244E4_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800244E4_4;   /* next in func_800244E4 */

   /* final_ctx in func_800244E4 */


typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch800244E4;

typedef struct {
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
s32 func_800244E4(void *first_point, void *first_position)
{
    void *point = first_point;
    void *position = first_position;
    GameWork *render_state = &gameWork;
    u32 addr_mask = 0x00FFFFFF;
    u8 *render_ctx = *(u8 **)((u8 *)(&gameWork));
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch800244E4 *scratch =
        (Scratch800244E4 *)0x1F800000;
    Packet800244E4 *tile;
    Packet800244E4 *draw_mode;
    u8 *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    void *next_node;

    packet_start = ((GpuContext *)render_ctx)->packetCursor;
    scratch->ot = (u32 *)(render_ctx + 0xB0);
    scratch->cursor = packet_start;

    for (;;) {
        tile = *(Packet800244E4 **)&scratch->cursor;
        scratch->x = ((S_800244E4_1 *)position)->unk_02;
        scratch->y = ((S_800244E4_1 *)position)->unk_06;
        scratch->z = ((S_800244E4_1 *)position)->unk_0A;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)tile + 8,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            ((S_800244E4_2 *)tile)->unk_04.at00.v = ((S_800244E4_3 *)point)->unk_08;

            color_value = (s32)tile->r * ((S_800244E4_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * ((S_800244E4_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * ((S_800244E4_3 *)point)->unk_32;
            tile->b = (color_value / 128);

            ((S_800244E4_2 *)tile)->unk_03 = 2;
            ((S_800244E4_2 *)tile)->unk_04.at03.v = 0x6A;
            ((P_TAG *)&tile->tag)->addr = ((P_TAG *)&scratch->ot[scratch->index])->addr;
            ((P_TAG *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (Packet800244E4 *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            ((P_TAG *)&draw_mode->tag)->addr = ((P_TAG *)&scratch->ot[scratch->index])->addr;
            ((P_TAG *)&scratch->ot[scratch->index])->addr = (u32)((u32)draw_mode);
        }

        next_node = ((S_800244E4_3_pre *)point)[-1].unk_00;
        if (next_node != 0) {
            point = (u8 *)next_node + 0x20;
            position = ((S_800244E4_4 *)next_node)->unk_08;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->unk_000;
    ((GpuContext *)final_render_ctx)->packetCursor = scratch->cursor;
    return 0;
}

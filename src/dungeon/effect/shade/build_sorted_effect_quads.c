#include "common.h"
#include "dungeon/effect/shaded_quad_scratch.h"
#include "shared/game_work.h"
#include "dungeon/effect/shade.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"

typedef struct S_800259DC_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_800259DC_1_pre;   /* the 0x8 bytes before arg0 in build_sorted_effect_quads, addressed as arg0[-1] */

typedef struct S_800259DC_1 {
    u8 pad_00[0x34];
    s32 unk_34;
    u16 unk_38;
    u8 pad_3A[0x2];
    s32 unk_3C;
    u16 unk_40;
    u8 pad_42[0x2];
    s32 unk_44;
    u16 unk_48;
    u8 pad_4A[0x2];
    s32 unk_4C;
    u16 unk_50;
    u8 pad_52[0x2];
    s32 unk_54;
    s32 unk_58;
} S_800259DC_1;   /* arg0 in build_sorted_effect_quads */


typedef struct GlobalState {
    u8 pad[0x8D0];
    void *next;
} GlobalState;


/* Build and depth-sort quad primitives from the linked entries. */
s32 build_sorted_effect_quads(void *quad_entry) {
    GlobalState **state_table = ((GlobalState * *)(&g_game_work));
    PackedShadedQuadScratch *scratch = PACKED_SHADED_QUAD_SCRATCH;
    S_800259DC_1 *entry;
    POLY_G4 *packet;
    DR_MODE *mode_packet;
    u32 depth_index;
    s32 color_01;
    s32 color_23;
    s32 next_entry;
    s32 corner3_xy;
    GlobalState *render_state;

    render_state = state_table[0];
    /* BYTES: assigning the pointer member moves the ordering-table address calculation ahead of the packet cursor load. */
    (*(void **)((u8 *)scratch + 0x20)) = (u8 *)render_state + 0xB0;
    scratch->packet_cursor = render_state->next;
    do {
        entry = quad_entry;
        packet = scratch->packet_cursor;
        scratch->packet_cursor = packet + 1;
        scratch->vertices[0].xy = entry->unk_34;
        scratch->vertices[1].xy = entry->unk_3C;
        scratch->vertices[2].xy = entry->unk_44;
        corner3_xy = entry->unk_4C;
        scratch->vertices[0].z = entry->unk_38;
        scratch->vertices[1].z = entry->unk_40;
        scratch->vertices[2].z = entry->unk_48;
        scratch->vertices[3].xy = corner3_xy;
        scratch->vertices[3].z = entry->unk_50;
        depth_index = RotTransPers4((SVECTOR *)&scratch->vertices[0], (SVECTOR *)&scratch->vertices[1],
                              (SVECTOR *)&scratch->vertices[2], (SVECTOR *)&scratch->vertices[3],
                              (s32 *)&packet->x0, (s32 *)&packet->x1,
                              (s32 *)&packet->x2, (s32 *)&packet->x3,
                              &scratch->depth_cue, &scratch->gte_flag) - 8;
        scratch->ot_index = depth_index;
        if (depth_index < 0x1E0U) {
            color_01 = entry->unk_54;
            /* BYTES: Write the first packed color to the second vertex before the first vertex. Separate members split the word into byte stores. */
            *(s32 *)&packet->red1 = color_01;
            /* BYTES: Write the same packed color to the first vertex after the second vertex. Separate members split the word into byte stores. */
            *(s32 *)&packet->red0 = color_01;
            color_23 = entry->unk_58;
            /* BYTES: Write the second packed color to the fourth vertex before the third vertex. Separate members split the word into byte stores. */
            *(s32 *)&packet->red3 = color_23;
            /* BYTES: Write the same packed color to the third vertex after the fourth vertex. Separate members split the word into byte stores. */
            *(s32 *)&packet->red2 = color_23;
            SetPolyG4(packet);
            packet->code = packet->code | 2;
            AddPrim(scratch->ordering_table +
                          scratch->ot_index * 4, packet);
            mode_packet = scratch->packet_cursor;
            scratch->packet_cursor = mode_packet + 1;
            SetDrawMode(mode_packet, 0, 0,
                          (u16)GetTPage(0, 1, 0, 0), 0);
            AddPrim(scratch->ordering_table +
                          scratch->ot_index * 4, mode_packet);
        }
        next_entry = ((S_800259DC_1_pre *)quad_entry)[-1].unk_00;
        if (next_entry == 0) {
            break;
        }
        quad_entry = (void *)(next_entry + 0x20);
    } while (1);
    state_table[0]->next =
        scratch->packet_cursor;
    return 0;
}


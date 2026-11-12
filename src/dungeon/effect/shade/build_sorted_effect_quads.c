#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/shade.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"

typedef struct S_800259DC_0 {
    u8 pad_00[0x18];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x4C];
    void * unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    void * unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    void * unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    void * unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
} S_800259DC_0;   /* scratch in build_sorted_effect_quads */

typedef struct S_800259DC_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_800259DC_1_pre;   /* the 0x8 bytes before arg0 in build_sorted_effect_quads, addressed as arg0[-1] */

typedef struct S_800259DC_1 {
    u8 pad_00[0x34];
    void * unk_34;
    u16 unk_38;
    u8 pad_3A[0x2];
    void * unk_3C;
    u16 unk_40;
    u8 pad_42[0x2];
    void * unk_44;
    u16 unk_48;
    u8 pad_4A[0x2];
    void * unk_4C;
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
    S_800259DC_0 *scratch = (S_800259DC_0 *)0x1F800000;
    POLY_G4 *packet;
    DR_MODE *mode_packet;
    u32 depth_index;
    s32 color_01;
    s32 color_23;
    s32 next_entry;
    void *corner3_xy;
    GlobalState *render_state;

    render_state = state_table[0];
    (*(void * *)((u8 *)scratch + 0x20)) = (u8 *)render_state + 0xB0;
    scratch->unk_18 = render_state->next;
    do {
        packet = scratch->unk_18;
        scratch->unk_18 = packet + 1;
        scratch->unk_70 = ((S_800259DC_1 *)quad_entry)->unk_34;
        scratch->unk_78 = ((S_800259DC_1 *)quad_entry)->unk_3C;
        scratch->unk_80 = ((S_800259DC_1 *)quad_entry)->unk_44;
        corner3_xy = ((S_800259DC_1 *)quad_entry)->unk_4C;
        scratch->unk_74 = ((S_800259DC_1 *)quad_entry)->unk_38;
        scratch->unk_7C = ((S_800259DC_1 *)quad_entry)->unk_40;
        scratch->unk_84 = ((S_800259DC_1 *)quad_entry)->unk_48;
        scratch->unk_88 = corner3_xy;
        scratch->unk_8C = ((S_800259DC_1 *)quad_entry)->unk_50;
        depth_index = RotTransPers4((u8 *)scratch + 0x70, (u8 *)scratch + 0x78,
                              (u8 *)scratch + 0x80, (u8 *)scratch + 0x88,
                              (s32 *)&packet->x0, (s32 *)&packet->x1,
                              (s32 *)&packet->x2, (s32 *)&packet->x3,
                              (u8 *)scratch + 0x90, (u8 *)scratch + 0x94) - 8;
        scratch->unk_C0 = depth_index;
        if (depth_index < 0x1E0U) {
            color_01 = ((S_800259DC_1 *)quad_entry)->unk_54;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red1 = color_01;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red0 = color_01;
            color_23 = ((S_800259DC_1 *)quad_entry)->unk_58;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red3 = color_23;
            /* BYTES: retail stores each vertex colour word (red, green, blue and the next byte) with one sw; member stores compile to sb sequences */
            *(s32 *)&packet->red2 = color_23;
            SetPolyG4(packet);
            packet->code = packet->code | 2;
            AddPrim((u8 *)scratch->unk_20 +
                          (scratch->unk_C0 * 4), packet);
            mode_packet = scratch->unk_18;
            scratch->unk_18 = mode_packet + 1;
            SetDrawMode(mode_packet, 0, 0,
                          (u16)GetTPage(0, 1, 0, 0), 0);
            AddPrim((u8 *)scratch->unk_20 +
                          (scratch->unk_C0 * 4), mode_packet);
        }
        next_entry = ((S_800259DC_1_pre *)quad_entry)[-1].unk_00;
        if (next_entry == 0) {
            break;
        }
        quad_entry = (void *)(next_entry + 0x20);
    } while (1);
    state_table[0]->next =
        scratch->unk_18;
    return 0;
}


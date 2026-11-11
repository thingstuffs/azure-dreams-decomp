#include "shared/entity.h"
/* Textured quad batches (G00338). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800AB480. */
#include "dungeon/actor/textured_quad_batches_g00338.h"
#include "engine/graphics.h"
#include "dungeon/actor.h"

/* Transform and emit linked batches of quad primitives into the rendering buffer. */
s32 transform_linked_quad_batches(u8 *initial_batch, s32 initial_dispatch_arg, u8 *initial_params)
{
    u8 *batch = initial_batch;
    s32 dispatch_arg = initial_dispatch_arg;
    S_800B06F0_3 *params = (S_800B06F0_3 *)initial_params;
    u8 *transform = (u8 *)0x1F8000D0;
    GameWork *global_addr = &g_game_work;
    S_800B06F0_0 *scratch;
    S_800B06F0_7 *manager;
    u8 *initial_manager;
    S_800B06F0_5 *packet;
    u8 **primitive_list;
    u8 *texture_data;
    u8 *primitive;
    u32 depth;
    u32 global_value;
    s32 reverse_winding;
    s16 vertex_x;
    s16 vertex_y;
    s32 signed_flags;
    s32 primitive_flags;
    u8 *next_batch;
    u32 ot_entry_addr;
    s32 quad_extent;
    s32 hard_zero = 0;

    global_value = global_addr->view.projection_distance;
    initial_manager = g_game_work.draw_buffer;
    scratch = (S_800B06F0_0 *)0x1F800000;
    scratch->unk_EC = global_value;
    packet = (S_800B06F0_5 *)((S_800B06F0_1 *)initial_manager)->unk_8D0;
    scratch->unk_20 = initial_manager + 0xB0;

    for (;;) {
    quad_batch_callbacks[((S_800B06F0_2 *)batch)->unk_08 & 1](dispatch_arg, params, scratch);

    primitive_list = ((S_800B06F0_2 *)batch)->unk_00;
    depth = scratch->unk_C0.i;
    texture_data = ((S_800B06F0_2 *)batch)->unk_04;

    if (depth < 0x1E0U) {
        ot_entry_addr = depth * 4;
        ot_entry_addr += (u32)scratch->unk_20;
        scratch->unk_C0.p = (u8 *)ot_entry_addr;
        scratch->unk_B8 -= 0xA0;
        scratch->unk_BA -= 0x78;
        PushMatrix(depth);

        scratch->unk_100 = params->unk_16;
        scratch->unk_102 = params->unk_18;
        scratch->unk_104 = params->unk_1A;
        scratch->unk_E4 = params->unk_20;
        scratch->unk_E8 = params->unk_22;
        scratch->unk_30 = params->unk_1C;
        scratch->unk_34 = params->unk_1E;
        scratch->unk_38 = 0x1000;

        RotMatrix(&scratch->unk_100, transform);
        ScaleMatrix(transform, &scratch->unk_30);
        SetTransMatrix(transform);
        SetRotMatrix(transform);

        primitive = *primitive_list;
        while (primitive != 0) {
            scratch->unk_8C = 0;
            scratch->unk_84 = 0;
            scratch->unk_7C = 0;
            scratch->unk_74 = 0;

            primitive = (u8 *)((u32)primitive | 0x80000000U);

            if ((primitive[0] ^ params->unk_14) & 1) {
                vertex_x = -(s8)primitive[2] - params->unk_20;
                scratch->unk_80 = vertex_x;
                scratch->unk_70 = vertex_x;
                vertex_x -= primitive[0xA];
                scratch->unk_88 = vertex_x;
                scratch->unk_78 = vertex_x;
            } else {
                vertex_x = (s8)primitive[2] - params->unk_20;
                scratch->unk_80 = vertex_x;
                scratch->unk_70 = vertex_x;
                quad_extent = primitive[0xA];
                vertex_x = vertex_x + quad_extent;
                scratch->unk_88 = vertex_x;
                scratch->unk_78 = vertex_x;
            }

            if ((primitive[0] ^ params->unk_14) & 2) {
                vertex_y = -(s8)primitive[3] - params->unk_22;
                scratch->unk_7A = vertex_y;
                scratch->unk_72 = vertex_y;
                vertex_y -= primitive[0xB];
                scratch->unk_8A = vertex_y;
                scratch->unk_82 = vertex_y;
            } else {
                vertex_y = (s8)primitive[3] - params->unk_22;
                scratch->unk_7A = vertex_y;
                scratch->unk_72 = vertex_y;
                quad_extent = primitive[0xB];
                vertex_y = vertex_y + quad_extent;
                scratch->unk_8A = vertex_y;
                scratch->unk_82 = vertex_y;
            }

            RotTransPers4(
                &scratch->unk_70, &scratch->unk_78,
                &scratch->unk_80, &scratch->unk_88,
                &scratch->unk_F0, &scratch->unk_F4,
                &scratch->unk_F8, &scratch->unk_FC,
                &scratch->depth_cue, &scratch->gte_flag);

            signed_flags = ((S_800B06F0_4 *)primitive)->unk_00;
            primitive_flags = primitive[0];
            if ((signed_flags >= 0) && (primitive_flags & 8)) {
                reverse_winding = primitive_flags & 4;
                if (NormalClip(
                        scratch->unk_F0.at00.v,
                        scratch->unk_F4.at00.v,
                        scratch->unk_F8.at00.v, primitive_flags) <= 0
                            ? reverse_winding == 0 : reverse_winding != 0) {
                    if (primitive[1] == 0x2C) {
                        texture_data += 4;
                    }
                    primitive_list++;
                    primitive = *primitive_list;
                    continue;
                }
            }

            if (primitive[0] & 4) {
                swap_int_values(&scratch->unk_F0, &scratch->unk_F4);
                swap_int_values(&scratch->unk_F8, &scratch->unk_FC);
            }

            packet->unk_08 = scratch->unk_F0.at00u.v
                + scratch->unk_B8;
            packet->unk_0A = scratch->unk_F0.at02.v
                + scratch->unk_BA;
            packet->unk_10 = scratch->unk_F4.at00u.v
                + scratch->unk_B8;
            packet->unk_12 = scratch->unk_F4.at02.v
                + scratch->unk_BA;
            packet->unk_18 = scratch->unk_F8.at00u.v
                + scratch->unk_B8;
            packet->unk_1A = scratch->unk_F8.at02.v
                + scratch->unk_BA;
            packet->unk_20 = scratch->unk_FC + scratch->unk_B8;
            packet->unk_22 = scratch->unk_FE + scratch->unk_BA;

            if ((primitive[1] & 0xFC) == 0x2C) {
                packet = submit_textured_quad(scratch->unk_C0.i, (SpriteFrameState *)params, &primitive, packet);
                multiply_rgb_tint_saturated((u8 *)packet - 0x24, texture_data);
                if (primitive != 0) {
                    continue;
                }
                texture_data += 4;
            } else {
                {
                    OtSlot ot_entry = { scratch->unk_C0.i };


                    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_800AAF90). */
                    do {
                        packet = emit_gpu_packets(ot_entry.entry, (u8 *)params, &primitive, (u8 *)packet);
                    } while (0);
                }
                if (primitive != 0) {
                    continue;
                }
            }
            primitive_list++;
            primitive = *primitive_list;
        }
        PopMatrix();
    }

    next_batch = ((S_800B06F0_2_pre *)batch)[-1].unk_00;
    if (next_batch == 0) {
        break;
    }
    reverse_winding = next_batch + 0x20;
    batch = reverse_winding;
    primitive_list = ((S_800B06F0_6 *)next_batch)->unk_08;
    dispatch_arg = primitive_list;
    params = (S_800B06F0_3 *)((S_800B06F0_6 *)next_batch)->unk_0C;
    }
    manager = global_addr->draw_buffer;
    manager->unk_8D0 = (u8 *)packet;
    return hard_zero;
}

/* Fill and submit a textured quad, then advance the primitive and texture cursors. */
void *submit_textured_quad(s32 draw_context, SpriteFrameState *draw_settings, void **texture_cursor, void *primitive) {
    s32 submit_context;
    u32 texture_page;
    s8 u_end;
    s8 v_end;
    u8 u_start;
    u8 v_start;
    S_800B0BE0_3 *u_bounds;
    S_800B0BE0_4 *v_bounds;
    void *texture_entry;
    u16 page_override;

    ((S_800B0BE0_0 *)primitive)->unk_04 = (s32) draw_settings->color.word;
    SetPolyFT4(primitive);
    ((S_800B0BE0_0 *)primitive)->unk_0E = (u16) ((S_800B0BE0_2 *)(*texture_cursor))->unk_06;
    page_override = draw_settings->tpage_abr;
    if (page_override != 0) {
        texture_page = page_override + (((S_800B0BE0_2 *)(*texture_cursor))->unk_04 & 0xFF9F);
    } else {
        texture_page = ((S_800B0BE0_2 *)(*texture_cursor))->unk_04;
    }
    {
        S_800B0BE0_0 *packet = (S_800B0BE0_0 *)primitive;
        packet->unk_16 = (u16) texture_page;
        u_start = ((S_800B0BE0_2 *)(*texture_cursor))->unk_08;
        packet->unk_1C = u_start;
        packet->unk_0C = u_start;
        u_bounds = *texture_cursor;
        u_end = (u_bounds->unk_08 + u_bounds->unk_0A) - 1;
        packet->unk_24 = u_end;
        packet->unk_14 = u_end;
        v_start = ((S_800B0BE0_2 *)(*texture_cursor))->unk_09;
        packet->unk_15 = v_start;
        packet->unk_0D = v_start;
        v_bounds = *texture_cursor;
        submit_context = draw_context;

        v_end = (v_bounds->unk_09 + v_bounds->unk_0B) - 1;
        packet->unk_25 = v_end;
        packet->unk_1D = v_end;
    }
    AddPrim(submit_context, primitive);
    texture_entry = *texture_cursor;
    primitive += 0x28;
    if (((S_800B0BE0_5 *)texture_entry)->unk_00 < 0) {
        *texture_cursor = 0;
    } else {
        *texture_cursor = texture_entry + 0xC;
    }
    return primitive;
}

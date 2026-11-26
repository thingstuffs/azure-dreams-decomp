#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect/shade/row_quad_colors.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "shared/gpu_packets.h"

typedef struct Scratch {
    u8 pad0[0x18];
    void *current;
    u8 pad1c[4];
    u32 *table;
    u8 pad24[0x4c];
    u32 value70;
    u16 half74;
    u8 pad76[2];
    u32 value78;
    u16 half7c;
    u8 pad7e[2];
    u32 value80;
    u16 half84;
    u8 pad86[2];
    u32 value88;
    u16 half8c;
    u8 pad8e[2];
    u32 out90;
    u32 out94;
    u8 pad98[0x28];
    u32 index;
} Scratch;

typedef struct EmptyCallArg {
} EmptyCallArg;

extern s16 D_80026476;

extern u32 RotTransPers4(
    u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *,
    EmptyCallArg);

/* Builds shaded quads from adjacent vertex rows and adds them to the ordering table. */
s32 draw_adjacent_row_quads(void)
{
    s32 quad_index = 0;
    Scratch *scratch = (Scratch *)0x1F800000;
    GpuContext *state = g_game_work.draw_buffer;
    u8 *packet_start = state->packetCursor;
    SVECTOR *vertices;
    SVECTOR *vertex_record;

    scratch->table = &state->orderTag[GPU_ORDER_DEPTH_BASE];
    scratch->current = packet_start;

            /* This address is needed only by the loop's terminal writeback. */
    {
        GpuContext **state_slot = &g_game_work.draw_buffer;

        if (D_80026476 > 0) {
            vertices = particle_quad_vertices;
            vertex_record = vertices;

            do {
                POLY_G4 *quad;
                u32 *row_left;
                u32 *row_right;
                u32 *next_row_left;
                u32 *next_row_right;
                SVECTOR *next_row;
                u32 *next_right_ptr;
                u32 next_right_xy;
                s32 row_start;
                s32 next_row_index;
                u16 row_z;
                u16 next_row_z;
                EmptyCallArg late_stores;

                row_left = &scratch->value70;
                row_start = quad_index & ~0xF;
                quad = scratch->current;
                row_right = &scratch->value78;
                next_row_left = &scratch->value80;
                scratch->current = quad + 1;
                scratch->value70 = *(u32 *)vertex_record;
                scratch->value78 = *(u32 *)&vertices[row_start + ((quad_index + 1) & 0xF)];
                next_row = vertices + 16;
                next_right_ptr = (u32 *)(((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 8 + (unsigned long)next_row);
                scratch->value80 = *(u32 *)&next_row[quad_index];
                next_right_xy = *next_right_ptr;
                next_row_right = &scratch->value88;
                row_z = vertex_record->vz;
                scratch->half74 = row_z;
                scratch->half7c = row_z;
                next_row_index = quad_index + 16;
                next_row_z = vertices[next_row_index].vz;

                scratch->index = RotTransPers4(
                    row_left, row_right, next_row_left, next_row_right,
                    (u32 *)&quad->x0, (u32 *)&quad->x1,
                    (u32 *)&quad->x2, (u32 *)&quad->x3,
                    &scratch->out90, &scratch->out94,
                    (scratch->value88 = next_right_xy,
                     scratch->half84 = next_row_z,
                     scratch->half8c = next_row_z,
                     late_stores));
                scratch->index -= 8;

                if (scratch->index < 0x1E0U) {
                    if ((quad_index % 32) < 16) {
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red1 = row_quad_top_color;
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red0 = row_quad_top_color;
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red3 = row_quad_bottom_color;
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red2 = row_quad_bottom_color;
                    } else {
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red3 = row_quad_top_color;
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red2 = row_quad_top_color;
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red1 = row_quad_bottom_color;
                        /* BYTES: Each vertex RGB value and its following byte are stored together in one word. Separate members write the bytes individually. */
                        *(u32 *)&quad->red0 = row_quad_bottom_color;
                    }

                    SetPolyG4(quad);
                    quad->code |= 2;
                    AddPrim(scratch->table + scratch->index, quad);

                    {
                        DR_MODE *draw_mode = scratch->current;
                        scratch->current = draw_mode + 1;
                        SetDrawMode(draw_mode, 0, 0,
                                      (u16)GetTPage(0, 1, 0, 0), 0);
                        AddPrim(scratch->table + scratch->index,
                                      draw_mode);
                    }
                }

                vertex_record++;
                quad_index++;
            } while (quad_index < D_80026476);
        }
        (*state_slot)->packetCursor = scratch->current;
    }
    return 0;
}

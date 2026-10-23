#include "common.h"
#include "shared/game_work.h"

typedef struct Scratch {
    u8 pad0[0x18];
    u8 *current;
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

typedef struct Entry {
    u8 bytes[0x24];
} Entry;

typedef struct EmptyCallArg {
} EmptyCallArg;

extern s16 D_80026476;
extern u32 row_quad_top_color;
extern u32 row_quad_bottom_color;
extern u32 particle_quad_vertices[];

extern u32 RotTransPers4(
    u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *, u32 *,
    EmptyCallArg);
extern void SetPolyG4(Entry *);
extern void AddPrim(u32 *, Entry *);
extern u32 GetTPage(u32, u32, u32, u32);
extern void SetDrawMode(Entry *, u32, u32, u32, u32);

/* Builds shaded quads from adjacent vertex rows and adds them to the ordering table. */
s32 draw_adjacent_row_quads(void)
{
    s32 quad_index = 0;
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *state = g_game_work.draw_buffer;
    u8 *packet_start = *(u8 **)(state + 0x8D0);
    u32 *vertices;
    u8 *vertex_record;

    scratch->table = (u32 *)(state + 0xB0);
    scratch->current = packet_start;

            /* This address is needed only by the loop's terminal writeback. */
    {
        u8 **state_slot = &g_game_work.draw_buffer;

        if (D_80026476 > 0) {
            vertices = particle_quad_vertices;
            vertex_record = (u8 *)vertices;

            do {
                Entry *quad;
                u32 *row_left;
                u32 *row_right;
                u32 *next_row_left;
                u32 *next_row_right;
                u32 *next_row;
                u32 *next_right_ptr;
                u32 next_right_xy;
                s32 row_start;
                s32 next_row_index;
                u16 row_z;
                u16 next_row_z;
                EmptyCallArg late_stores;

                row_left = &scratch->value70;
                row_start = quad_index & ~0xF;
                quad = (Entry *)scratch->current;
                row_right = &scratch->value78;
                next_row_left = &scratch->value80;
                scratch->current = (u8 *)quad + 0x24;
                scratch->value70 = *(u32 *)vertex_record;
                scratch->value78 = vertices[
                    ((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 2];
                next_row = vertices + 0x20;
                next_right_ptr = (u32 *)(((u32)row_start + (u32)((quad_index + 1) & 0xF)) * 8 + (u32)next_row);
                scratch->value80 = next_row[quad_index * 2];
                next_right_xy = *next_right_ptr;
                next_row_right = &scratch->value88;
                row_z = *(u16 *)(vertex_record + 4);
                scratch->half74 = row_z;
                scratch->half7c = row_z;
                next_row_index = quad_index + 16;
                next_row_z = ((u16 *)vertices)[(next_row_index * 4) + 2];

                scratch->index = RotTransPers4(
                    row_left, row_right, next_row_left, next_row_right,
                    (u32 *)((u8 *)quad + 8), (u32 *)((u8 *)quad + 16),
                    (u32 *)((u8 *)quad + 24), (u32 *)((u8 *)quad + 32),
                    &scratch->out90, &scratch->out94,
                    (scratch->value88 = next_right_xy,
                     scratch->half84 = next_row_z,
                     scratch->half8c = next_row_z,
                     late_stores));
                scratch->index -= 8;

                if (scratch->index < 0x1E0U) {
                    if ((quad_index % 32) < 16) {
                        *(u32 *)((u8 *)quad + 12) = row_quad_top_color;
                        *(u32 *)((u8 *)quad + 4) = row_quad_top_color;
                        *(u32 *)((u8 *)quad + 28) = row_quad_bottom_color;
                        *(u32 *)((u8 *)quad + 20) = row_quad_bottom_color;
                    } else {
                        *(u32 *)((u8 *)quad + 28) = row_quad_top_color;
                        *(u32 *)((u8 *)quad + 20) = row_quad_top_color;
                        *(u32 *)((u8 *)quad + 12) = row_quad_bottom_color;
                        *(u32 *)((u8 *)quad + 4) = row_quad_bottom_color;
                    }

                    SetPolyG4(quad);
                    quad->bytes[7] |= 2;
                    AddPrim(scratch->table + scratch->index, quad);

                    {
                        u8 *draw_mode = scratch->current;
                        scratch->current = draw_mode + 0x0C;
                        SetDrawMode(draw_mode, 0, 0,
                                      (u16)GetTPage(0, 1, 0, 0), 0);
                        AddPrim(scratch->table + scratch->index,
                                      (Entry *)draw_mode);
                    }
                }

                vertex_record += 8;
                quad_index++;
            } while (quad_index < D_80026476);
        }
        *(u8 **)(*state_slot + 0x8D0) = scratch->current;
    }
    return 0;
}

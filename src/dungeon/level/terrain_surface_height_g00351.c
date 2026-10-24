/* Terrain surface height (G00351). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B771C. */
#include "dungeon/level/terrain_surface_height_g00351.h"

/* Finds the lowest surface height at (x, y) that meets the minimum height. */
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height) {
    Work *work = (Work *)0x1F800000;
    MapGrid *tables;
    Cell *cells;
    Vertex *vertices;
    Vertex *normals;
    s32 cell_x;
    s32 cell_y;
    Primitive *primitive;

    work->x = x & 0x3F;
    cell_x = (s32)((u32)(x & 0xFFFF) >> 6);
    work->y = y & 0x3F;
    work->limit = min_height;
    work->index = cell_x;
    tables = &g_game_work.map;
    vertices = ((Vertex *)tables->vertices);
    cells = ((Cell *)tables->cells);
    normals = ((Vertex *)tables->surface_planes);
    if (cell_x < 0) {
        work->index = 0;
        cell_y = y & 0xFFFF;
    } else if (cell_x < 0x40) {
        cell_y = y & 0xFFFF;
    } else {
        work->index = 0x3F;
        cell_y = y & 0xFFFF;
    }
    cell_y = (s32)((u32)cell_y >> 6);
    work->best = cell_y;
    if (cell_y < 0) {
        work->best = 0;
    } else if (cell_y >= 0x40) {
        work->best = 0x3F;
    }
    work->index += work->best << tables->shiftX;
    work->best = 0x400;
    {
        Cell *cell = (Cell *)(
            (unsigned long)((s16)work->index * sizeof(Cell)) +
            (unsigned long)cells);

        if (cell->first != 0) {
            work->offset = -cell->value;
            primitive = ((Primitive **)tables->cell_faces)[
                cells[(s16)*(u16 *)&work->index].first];
            while (normals[primitive->next].z < -2047) {
                if (!(primitive->flags & 1)) {
                    u16 local_x;
                    u16 local_y;
                    u16 vertex_index;
                    u16 p3_x;
                    u16 p3_y;

                    vertex_index = *(u16 *)&primitive->v0;
                    local_x = *(u16 *)&work->x;
                    local_y = *(u16 *)&work->y;
                    work->p0.word = *(u32 *)&vertices[vertex_index];
                    work->p0.half.x -= local_x;
                    work->p0.half.y -= local_y;
                    work->p1.word = *(u32 *)&vertices[primitive->v1];
                    work->p1.half.x -= local_x;
                    work->p1.half.y -= local_y;
                    work->p2.word = *(u32 *)&vertices[primitive->v3];
                    work->p2.half.x -= local_x;
                    work->p2.half.y -= local_y;
                    work->p3.word = *(u32 *)&vertices[primitive->v2];
                    p3_x = work->p3.half.x - local_x;
                    p3_y = work->p3.half.y - local_y;
                    work->p3.half.x = p3_x;
                    work->p3.half.y = p3_y;
                    if (are_quad_corner_turns_within_half_revolution((Work *)work) != 0) {
                        Vertex *normal = (Vertex *)(
                            (unsigned long)(primitive->next * sizeof(Vertex)) +
                            (unsigned long)normals);
                        Vertex *vertex = (Vertex *)(
                            (unsigned long)((*(u16 *)((u8 *)primitive + 0)) * sizeof(Vertex)) +
                            (unsigned long)vertices);
                        s32 delta_x = (s16)vertex->x - (s16)*(u16 *)&work->x;
                        s32 delta_y = (s16)vertex->y - (s16)*(u16 *)&work->y;
                        s32 x_term = (s16)normal->x * delta_x;
                        s32 y_term = (s16)normal->y * delta_y;
                        s32 z_term = (s16)normal->z * (s16)vertex->z;
                        s32 height = (x_term + y_term + z_term) / (s16)normal->z;
                        u16 raw_offset;
                        s32 height_limit;
                        s32 cell_height;

                        work->value = height;
                        raw_offset = work->offset;
                        height_limit = work->limit;
                        cell_height = height + (s16)raw_offset;
                        work->value = cell_height;
                        if (cell_height >= height_limit) {
                            if (cell_height < work->best) {
                                work->best = cell_height;
                            }
                        }
                    }
                }
                {
                    u8 kind = primitive->kind;
                    if ((kind & 0x0F) == 1) {
                        if (primitive->flags < 0) {
                            break;
                        }
                        if (kind & 0xF0) {
                            u32 next_offset = ((kind >> 4) * 3 * 8) + 24;
                            primitive = (Primitive *)((u8 *)primitive + next_offset);
                            continue;
                        }
                    }
                    primitive = (Primitive *)((u8 *)primitive + 24);
                }
            }
        }
    }

    {
        s32 best_height = (s16)work->best;
                 /* MATCH: keep best_height sign extension before the shared epilogue. */
        return best_height;
    }
}

/* True unless the quad's corner angles are laid out so that one of its successive turns exceeds half a revolution. */
s32 are_quad_corner_turns_within_half_revolution(S_800BCE7C_0 *poly) {
    s32 delta_3;
    s32 angle_1;
    s32 delta_1;
    s32 angle_2;
    s32 delta_2;
    s32 angle_3;
    s32 turn_1;
    s32 turn_2;
    s32 turn_3;

    if (poly->unk_154.at00.v == 0) {
        return 1;
    }
    if (poly->unk_160.at00.v == 0) {
        return 1;
    }
    poly->unk_164 = ratan2(poly->unk_154.at02.v, (s16) poly->unk_154.at00.v);
    angle_1 = ratan2(poly->unk_160.at02.v, (s16) poly->unk_160.at00.v);
    poly->unk_170 = angle_1;
    delta_1 = angle_1 - poly->unk_164;
    turn_1 = (0x1000 - delta_1) & 0xFFF;
    poly->unk_180 = turn_1;
    poly->unk_170 = delta_1;
    if (turn_1 >= 0x801) {
        return 0;
    }
    if (poly->unk_15C.at00.v == 0) {
        return 1;
    }
    angle_2 = ratan2(poly->unk_15C.at02.v, (s16) poly->unk_15C.at00.v);
    poly->unk_16C = angle_2;
    delta_2 = angle_2 - poly->unk_164;
    turn_2 = (poly->unk_170 - delta_2) & 0xFFF;
    poly->unk_17C = turn_2;
    poly->unk_16C = delta_2;
    if (turn_2 >= 0x801) {
        return 0;
    }
    if (poly->unk_158.at00.v == 0) {
        return 1;
    }
    angle_3 = ratan2(poly->unk_158.at02.v, (s16) poly->unk_158.at00.v);
    poly->unk_168 = angle_3;
    delta_3 = (angle_3 - poly->unk_164) & 0xFFF;
    poly->unk_168 = delta_3;
    if (delta_3 >= 0x801) {
        return 0;
    }
    turn_3 = (poly->unk_16C - delta_3) & 0xFFF;
    poly->unk_178 = turn_3;
    return turn_3 < 0x801;
}

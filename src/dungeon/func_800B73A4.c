#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vertex;

typedef struct {
    u16 first;
    s16 value;
    u16 pad;
} Cell;

typedef struct {
    u16 v0;
    u16 v1;
    u16 v2;
    u16 v3;
    u8 pad08[8];
    u16 next;
    u8 pad12[4];
    u8 kind;
    s8 flags;
} Primitive;

typedef union {
    u32 word;
    struct {
        u16 x;
        u16 y;
    } half;
} WorkPair;

typedef struct {
    u8 pad000[0x140];
    u16 x;
    u16 y;
    s32 value;
    s32 best;
    s32 limit;
    u16 index;
    s16 offset;
    WorkPair p0;
    WorkPair p1;
    WorkPair p2;
    WorkPair p3;
} Work;


extern s32 func_800BCE7C(Work *);

/* Finds the lowest surface height at (x, y) that meets the minimum height. */
s32 func_800BCB04(s32 x, s32 y, s16 min_height) {
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
    tables = &gameWork.map;
    vertices = ((Vertex *)tables->unk_08);
    cells = ((Cell *)tables->cells);
    normals = ((Vertex *)tables->unk_0C);
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
            primitive = ((Primitive **)tables->unk_04)[
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
                    if (func_800BCE7C((Work *)work) != 0) {
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

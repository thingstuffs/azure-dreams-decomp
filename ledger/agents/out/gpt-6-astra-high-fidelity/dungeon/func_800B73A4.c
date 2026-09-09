#include "common.h"

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
    volatile u16 x;
    volatile u16 y;
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

typedef struct {
    Cell *cells;
    Primitive **primitives;
    Vertex *vertices;
    Vertex *vertices2;
    u32 pad10;
    s16 shift;
} DungeonTables;

extern DungeonTables D_8008333C;

extern s32 func_800BCE7C(Work *);

s32 func_800BCB04(s32 arg0, s32 arg1, s16 arg2) {
    Work *work = (Work *)0x1F800000;
    DungeonTables *tables;
    Cell *cells;
    Vertex *vertices;
    Vertex *vertices2;
    s32 xblock;
    s32 yblock;
    Primitive *primitive;

    work->x = arg0 & 0x3F;
    xblock = (s32)((u32)(arg0 & 0xFFFF) >> 6);
    work->y = arg1 & 0x3F;
    work->limit = arg2;
    work->index = xblock;
    tables = &D_8008333C;
    vertices = tables->vertices;
    cells = tables->cells;
    vertices2 = tables->vertices2;
    if (xblock < 0) {
        work->index = 0;
        yblock = arg1 & 0xFFFF;
    } else if (xblock < 0x40) {
        yblock = arg1 & 0xFFFF;
    } else {
        work->index = 0x3F;
        yblock = arg1 & 0xFFFF;
    }
    yblock = (s32)((u32)yblock >> 6);
    work->best = yblock;
    if (yblock < 0) {
        work->best = 0;
    } else if (yblock >= 0x40) {
        work->best = 0x3F;
    }
    work->index += work->best << tables->shift;
    work->best = 0x400;
    {
        Cell *cell = (Cell *)(
            (unsigned long)((s16)work->index * sizeof(Cell)) +
            (unsigned long)cells);

        if (cell->first == 0) {
            goto done;
        }
        work->offset = -cell->value;
    }
    primitive = tables->primitives[
        cells[(s16)*(volatile u16 *)&work->index].first];
    goto next_primitive;

process_primitive:
    if (!(primitive->flags & 1)) {
        u16 work_x;
        u16 work_y;
        u16 vertex_index;
        u16 p3_x;
        u16 p3_y;

        vertex_index = *(volatile u16 *)&primitive->v0;
        work_x = *(volatile u16 *)&work->x;
        work_y = *(volatile u16 *)&work->y;
        work->p0.word = *(u32 *)&vertices[vertex_index];
        work->p0.half.x -= work_x;
        work->p0.half.y -= work_y;
        work->p1.word = *(u32 *)&vertices[primitive->v1];
        work->p1.half.x -= work_x;
        work->p1.half.y -= work_y;
        work->p2.word = *(u32 *)&vertices[primitive->v3];
        work->p2.half.x -= work_x;
        work->p2.half.y -= work_y;
        work->p3.word = *(u32 *)&vertices[primitive->v2];
        p3_x = work->p3.half.x - work_x;
        p3_y = work->p3.half.y - work_y;
        ASM_KEEP(work_x);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        work->p3.half.x = p3_x;
        work->p3.half.y = p3_y;
        if (func_800BCE7C((Work *)work) != 0) {
            register Vertex *b ASM_REG("$6") = (Vertex *)(
                (unsigned long)(primitive->next * sizeof(Vertex)) +
                (unsigned long)vertices2);
            register Vertex *a ASM_REG("$5") = (Vertex *)(
                (unsigned long)(primitive->v0 * sizeof(Vertex)) +
                (unsigned long)vertices);
            s32 n0 = (s16)a->x - (s16)*(volatile u16 *)&work->x;
            s32 n1 = (s16)a->y - (s16)*(volatile u16 *)&work->y;
            s32 n2 = (s16)b->x * n0;
            s32 n3 = (s16)b->y * n1;
            s32 n4 = (s16)b->z * (s16)a->z;
            s32 value = (n2 + n3 + n4) / (s16)b->z;
            u16 raw_offset = work->offset;
            s32 limit = work->limit;
            s32 adjusted = value + (s16)raw_offset;

            *(volatile s32 *)&work->value = value;
            work->value = adjusted;
            if (adjusted >= limit) {
                if (adjusted < work->best) {
                    work->best = adjusted;
                }
            }
        }
    }
    {
        u8 kind = primitive->kind;
        if ((kind & 0x0F) == 1) {
            if (primitive->flags < 0) {
                goto done;
            }
            if (kind & 0xF0) {
                u32 next_offset = ((kind >> 4) * 3 * 8) + 24;
                primitive = (Primitive *)((u8 *)primitive + next_offset);
                goto next_primitive;
            }
        }
        primitive = (Primitive *)((u8 *)primitive + 24);
next_primitive:
        if (vertices2[primitive->next].z < -2047) {
            goto process_primitive;
        }
    }

done:
    {
        s32 result = (s16)work->best;
        ASM_KEEP(result); /* MATCH: keep result sign extension before the shared epilogue. */
        return result;
    }
}

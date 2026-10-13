#include "shared/entity.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"

#include "common.h"


typedef struct S_800463EC_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 unk_16;
    s8 unk_17;
} S_800463EC_1;   /* face in func_800463EC */

typedef struct S_800463EC_2 {
    s32 unk_00;
    u16 unk_04;
} S_800463EC_2;   /* (u8 *)vertexTable + vertexIndex * 8 in func_800463EC */

typedef struct S_800463EC_3 {
    s32 unk_00;
} S_800463EC_3;   /* (u8 *)vertexTransfer in func_800463EC */

typedef struct S_800463EC_4 {
    u8 pad_00[0x7];
    u8 unk_07;
    s32 unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_14;   /* overlapping accesses */
    s32 unk_18;
    u16 unk_1C;
    u8 pad_1E[0x2];
    s32 unk_20;
    u16 unk_24;
} S_800463EC_4;   /* prim in func_800463EC */

typedef struct S_800463EC_5 {
    void * unk_00;
} S_800463EC_5;   /* globalBase in func_800463EC */


typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {
    u8 pad0[8];
    s32 meshIndex;
    u8 padC[4];
    u16 colour;
    u16 texture;
    u16 flags;
    s16 rotation[3];
    u16 scale[3];
} RenderObject;

typedef struct {
    s32 value;
    u16 depth;
    u16 pad;
} Vertex;

typedef struct ScratchVertex {
    s32 xy;
    u16 z;
    u16 pad;
} ScratchVertex;
typedef struct RenderScratch {
    u8 pad00[0x20];
    void *ordering_table;
    u8 pad24[0xC];
    s32 scale[3];
    u8 pad3C[4];
    s32 translation[3];
    u8 pad4C[0x24];
    ScratchVertex vertices[4];
    u8 pad90[0x30];
    s32 depth;
    u8 padC4[0x50];
    s32 clip;
} RenderScratch;

#define PPAD(base, type, field) (((type *)(base))->field)

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(MATRIX *m);
extern void TransMatrix(void *m, void *v);
extern void RotMatrix(void *r, void *m);
extern void ScaleMatrix(void *m, void *v);
extern void CompMatrix(void *m0, void *m1, void *m2);
extern void SetTransMatrix(void *m);
extern void SetRotMatrix(void *m);
extern s32 RotAverage4();
extern s32 NormalClip();
extern void NormalColorCol(void *a0, void *a1, void *a2);
extern void SetPolyFT4(void *p);
extern void AddPrim(void *ot, void *p);


/* Transform, light, and queue visible textured mesh quads for rendering. */
void func_800463EC(void *unused, u8 *position, RenderObject *object, s16 depth_bias)
{
    MATRIX view_matrix;
    u8 *render_globals;
    Vertex *vertex_table;
    u8 *normal_table;
    u8 *render_state;
    u8 *face;
    u8 *prim;
    u8 *scratch;
    u32 vertex_word;
    u16 index_b;
    u16 index_c;
    u16 vertex_index;
    unsigned long vertex_data;
    void *vertex_0;
    void *vertex_1;
    s32 clip_xy_0;
    s32 clip_xy_1;
    s32 clip_xy_2;
    s32 flip_flags;
    s32 depth_offset;
    u16 flags;
    u16 colour;
    u32 depth;

    render_globals = (u8 *)((void * *)(&gameWork));
    vertex_table = *(Vertex **)(render_globals + 0x1E4);
    normal_table = *(u8 **)(render_globals + 0x1E8);

    PushMatrix();

    vertex_word = *(u16 *)&object->scale[0];
    scratch = (u8 *)0x1F800000;

    ((RenderScratch *)scratch)->scale[0] = vertex_word;
    ((RenderScratch *)scratch)->scale[1] = object->scale[1];
    ((RenderScratch *)scratch)->scale[2] = object->scale[2];
    ((RenderScratch *)scratch)->translation[0] = ((Fixed1616 *)position)[0].w.i;
    ((RenderScratch *)scratch)->translation[1] = ((Fixed1616 *)position)[1].w.i;
    ((RenderScratch *)scratch)->translation[2] = ((Fixed1616 *)position)[2].w.i;

    ReadRotMatrix(&view_matrix);
    vertex_0 = (u8 *)scratch;
    vertex_0 = (void *)((unsigned long)vertex_0 | 0x50);
    vertex_1 = (u8 *)scratch;
    vertex_1 = (void *)((unsigned long)vertex_1 | 0x40);
    TransMatrix(vertex_0, vertex_1);
    vertex_0 = &object->rotation[0];
    vertex_1 = (u8 *)scratch;
    vertex_1 = (void *)((unsigned long)vertex_1 | 0x50);
    RotMatrix(vertex_0, vertex_1);

    if (object->flags & 1) {
        PPAD(scratch, RenderScratch, scale[0]) = -PPAD(scratch, RenderScratch, scale[0]);
    }
    if (object->flags & 2) {
        PPAD(scratch, RenderScratch, scale[1]) = -PPAD(scratch, RenderScratch, scale[1]);
    }

    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    CompMatrix(&view_matrix, (void *)0x1F800050, (void *)0x1F8000D0);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    depth_offset = depth_bias;
    render_state = gameWork.unk_000;
    ((RenderScratch *)scratch)->ordering_table = render_state + 0xB0;
    prim = *(u8 **)(render_state + 0x8D0);
    object->flags |= 0x8000;

    face = *(u8 **)(*(u8 **)(render_globals + 0x1E0) + object->meshIndex * 4);

    for (;;) {
        vertex_data = ((S_800463EC_2 *)((u8 *)vertex_table + ((S_800463EC_1 *)face)->unk_00 * 8))->unk_00;
        index_b = ((S_800463EC_1 *)face)->unk_02;
        ((RenderScratch *)scratch)->vertices[0].xy = vertex_data;
        vertex_data = ((S_800463EC_2 *)((u8 *)vertex_table + index_b * 8))->unk_00;
        index_c = ((S_800463EC_1 *)face)->unk_04;
        ((RenderScratch *)scratch)->vertices[1].xy = vertex_data;
        vertex_data = ((S_800463EC_1 *)face)->unk_06;
        vertex_data = (vertex_data << 3) + (unsigned long)vertex_table;
        ((RenderScratch *)scratch)->vertices[2].xy = ((S_800463EC_2 *)((u8 *)vertex_table + index_c * 8))->unk_00;
        vertex_data = ((S_800463EC_3 *)((u8 *)vertex_data))->unk_00;
        ((RenderScratch *)scratch)->vertices[0].z = ((S_800463EC_2 *)((u8 *)vertex_table + ((S_800463EC_1 *)face)->unk_00 * 8))->unk_04;
        ((RenderScratch *)scratch)->vertices[1].z = ((S_800463EC_2 *)((u8 *)vertex_table + ((S_800463EC_1 *)face)->unk_02 * 8))->unk_04;
        ((RenderScratch *)scratch)->vertices[2].z = ((S_800463EC_2 *)((u8 *)vertex_table + ((S_800463EC_1 *)face)->unk_04 * 8))->unk_04;
        vertex_index = ((S_800463EC_1 *)face)->unk_06;
        ((RenderScratch *)scratch)->vertices[3].xy = vertex_data;
        vertex_data = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_index * 8))->unk_04;
        ((RenderScratch *)scratch)->vertices[3].z = vertex_data;

        PPAD(scratch, RenderScratch, depth) = RotAverage4(
            &((RenderScratch *)scratch)->vertices[0],
            &((RenderScratch *)scratch)->vertices[1],
            &((RenderScratch *)scratch)->vertices[2],
            &((RenderScratch *)scratch)->vertices[3],
            prim + 8,
            prim + 0x10,
            prim + 0x18,
            prim + 0x20,
            scratch + 0x90,
            scratch + 0x94);

        flip_flags = object->flags & 3;
        switch (flip_flags) {
        case 0:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_08;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_10;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_18;
            PPAD(scratch, RenderScratch, clip) = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        case 1:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_10;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_08;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_20;
            PPAD(scratch, RenderScratch, clip) = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        case 2:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_20;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_18;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_10;
            PPAD(scratch, RenderScratch, clip) = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        default:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_18;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_20;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_08;
            PPAD(scratch, RenderScratch, clip) = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        }

        
        if (PPAD(scratch, RenderScratch, clip) > 0) {
            depth = PPAD(scratch, RenderScratch, depth) - depth_offset;
            PPAD(scratch, RenderScratch, depth) = depth;
            if (depth < 0x1E0U) {
                NormalColorCol(
                    normal_table + ((S_800463EC_1 *)face)->unk_10 * 8,
                    (u8 *)object + 0xC,
                    prim + 4);

                ((S_800463EC_4 *)prim)->unk_0C.at00.v = ((S_800463EC_1 *)face)->unk_08;
                ((S_800463EC_4 *)prim)->unk_0C.at02.v += object->texture;
                ((S_800463EC_4 *)prim)->unk_14.at00.v = ((S_800463EC_1 *)face)->unk_0C;

                colour = object->colour;
                if (colour != 0) {
                    ((S_800463EC_4 *)prim)->unk_14.at02.v = colour + (((S_800463EC_4 *)prim)->unk_14.at02.v & 0xFF9F);
                }

                ((S_800463EC_4 *)prim)->unk_1C = ((S_800463EC_1 *)face)->unk_12;
                ((S_800463EC_4 *)prim)->unk_24 = ((S_800463EC_1 *)face)->unk_14;
                SetPolyFT4(prim);

                flags = object->flags;
                if (flags & 8) {
                    if (flags & 4) {
                        ((S_800463EC_4 *)prim)->unk_07 |= 2;
                    }
                }

                AddPrim((u8 *)((RenderScratch *)scratch)->ordering_table + PPAD(scratch, RenderScratch, depth) * 4, prim);
                prim += 0x28;
                object->flags &= 0x7FFF;
            }
        }

        if (((S_800463EC_1 *)face)->unk_16 == 1 && ((S_800463EC_1 *)face)->unk_17 < 0) {
            break;
        }
        face += 0x18;
    }

    PopMatrix();
    *(u8 **)((u8 *)((S_800463EC_5 *)render_globals)->unk_00 + 0x8D0) = prim;
}

#include "common.h"

#include "common.h"
#include "records/Rec_D_80016000.h"


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

#define SPAD(base, type, offset) (*(volatile type *)((base) + (offset)))
#define SPAD_NV(base, type, offset) (*(type *)((base) + (offset)))

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

extern void *D_80083160[3];

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
    register volatile u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register u32 vertex_word ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    unsigned long vertex_data;
    register void *vertex_0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    void *vertex_1;
    void *vertex_2;
    void *vertex_3;
    s32 clip_xy_0;
    s32 clip_xy_1;
    s32 clip_xy_2;
    s32 flip_flags;
    s32 depth_offset;
    u16 flags;
    u16 colour;
    u32 depth;

    render_globals = (u8 *)D_80083160;
    vertex_table = *(Vertex **)(render_globals + 0x1E4);
    normal_table = *(u8 **)(render_globals + 0x1E8);

    PushMatrix();

    vertex_word = *(volatile u16 *)&object->scale[0];
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    scratch = (volatile u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

    SPAD_NV(scratch, s32, 0x30) = vertex_word;
    SPAD_NV(scratch, s32, 0x34) = object->scale[1];
    SPAD_NV(scratch, s32, 0x38) = object->scale[2];
    SPAD_NV(scratch, s32, 0x40) = ((Rec_D_80016000 *)position)->unk_00.at02_s16.v;
    SPAD_NV(scratch, s32, 0x44) = ((Rec_D_80016000 *)position)->unk_04.at02_s16.v;
    SPAD_NV(scratch, s32, 0x48) = ((Rec_D_80016000 *)position)->unk_08.at02_s16.v;

    ReadRotMatrix(&view_matrix);
    vertex_0 = (u8 *)scratch;
    ASM_KEEP_NV(vertex_0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    vertex_0 = (void *)((unsigned long)vertex_0 | 0x50);
    vertex_1 = (u8 *)scratch;
    ASM_KEEP_NV(vertex_1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    vertex_1 = (void *)((unsigned long)vertex_1 | 0x40);
    TransMatrix(vertex_0, vertex_1);
    vertex_0 = &object->rotation[0];
    vertex_1 = (u8 *)scratch;
    ASM_KEEP_NV(vertex_1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    vertex_1 = (void *)((unsigned long)vertex_1 | 0x50);
    RotMatrix(vertex_0, vertex_1);

    if (object->flags & 1) {
        SPAD(scratch, s32, 0x30) = -SPAD(scratch, s32, 0x30);
    }
    if (object->flags & 2) {
        SPAD(scratch, s32, 0x34) = -SPAD(scratch, s32, 0x34);
    }

    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    CompMatrix(&view_matrix, (void *)0x1F800050, (void *)0x1F8000D0);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    depth_offset = depth_bias;
    render_state = D_80083160[0];
    SPAD(scratch, void *, 0x20) = render_state + 0xB0;
    prim = *(u8 **)(render_state + 0x8D0);
    object->flags |= 0x8000;

    face = *(u8 **)(*(u8 **)(render_globals + 0x1E0) + object->meshIndex * 4);

    for (;;) {
        vertex_word = ((S_800463EC_1 *)face)->unk_00;
        vertex_data = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_00;
        vertex_word = ((S_800463EC_1 *)face)->unk_02;
        SPAD_NV(scratch, s32, 0x70) = vertex_data;
        vertex_data = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_00;
        vertex_word = ((S_800463EC_1 *)face)->unk_04;
        SPAD_NV(scratch, s32, 0x78) = vertex_data;
        vertex_data = ((S_800463EC_1 *)face)->unk_06;
        vertex_word = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_00;
        vertex_data = (vertex_data << 3) + (unsigned long)vertex_table;
        SPAD_NV(scratch, s32, 0x80) = vertex_word;
        vertex_word = ((S_800463EC_1 *)face)->unk_00;
        vertex_data = ((S_800463EC_3 *)((u8 *)vertex_data))->unk_00;
        vertex_word = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_04;
        SPAD_NV(scratch, u16, 0x74) = vertex_word;
        vertex_word = ((S_800463EC_1 *)face)->unk_02;
        vertex_word = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_04;
        vertex_0 = (u8 *)scratch + 0x70;
        SPAD_NV(scratch, u16, 0x7C) = vertex_word;
        vertex_word = ((S_800463EC_1 *)face)->unk_04;
        vertex_1 = (u8 *)scratch + 0x78;
        vertex_word = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_04;
        vertex_2 = (u8 *)scratch + 0x80;
        SPAD_NV(scratch, u16, 0x84) = vertex_word;
        vertex_word = ((S_800463EC_1 *)face)->unk_06;
        vertex_3 = (u8 *)scratch + 0x88;
        SPAD_NV(scratch, s32, 0x88) = vertex_data;
        vertex_data = ((S_800463EC_2 *)((u8 *)vertex_table + vertex_word * 8))->unk_04;
        SPAD_NV(scratch, u16, 0x8C) = vertex_data;
        ASM_JALDELAY_PIN(vertex_data);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

        SPAD(scratch, s32, 0xC0) = RotAverage4(
            vertex_0,
            vertex_1,
            vertex_2,
            vertex_3,
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
            break;
        case 1:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_10;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_08;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_20;
            break;
        case 2:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_20;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_18;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_10;
            break;
        default:
            clip_xy_0 = ((S_800463EC_4 *)prim)->unk_18;
            clip_xy_1 = ((S_800463EC_4 *)prim)->unk_20;
            clip_xy_2 = ((S_800463EC_4 *)prim)->unk_08;
            break;
        }

        SPAD(scratch, s32, 0x114) = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
        if (SPAD(scratch, s32, 0x114) > 0) {
            depth = SPAD(scratch, s32, 0xC0) - depth_offset;
            SPAD(scratch, s32, 0xC0) = depth;
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

                AddPrim((u8 *)SPAD(scratch, void *, 0x20) + SPAD(scratch, s32, 0xC0) * 4, prim);
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

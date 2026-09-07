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

void func_800463EC(void *arg0, u8 *arg1, RenderObject *arg2, s16 arg3)
{
    MATRIX matrix;
    u8 *globalBase;
    Vertex *vertexTable;
    u8 *textureTable;
    u8 *root;
    u8 *face;
    u8 *prim;
    register volatile u8 *scratch ASM_REG("$18");   /* MATCH pin: slus-diff */
    register u32 vertexIndex ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    unsigned long vertexTransfer;
    register void *rotVertex0 ASM_REG("$4");   /* MATCH pin: slus-diff */
    void *rotVertex1;
    void *rotVertex2;
    void *rotVertex3;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 kind;
    s32 depthOffset;
    u16 flags;
    u16 colour;
    u32 depth;

    globalBase = (u8 *)D_80083160;
    vertexTable = *(Vertex **)(globalBase + 0x1E4);
    textureTable = *(u8 **)(globalBase + 0x1E8);

    PushMatrix();

    vertexIndex = *(volatile u16 *)&arg2->scale[0];
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    scratch = (volatile u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* MATCH pin: slus-diff */

    SPAD_NV(scratch, s32, 0x30) = vertexIndex;
    SPAD_NV(scratch, s32, 0x34) = arg2->scale[1];
    SPAD_NV(scratch, s32, 0x38) = arg2->scale[2];
    SPAD_NV(scratch, s32, 0x40) = ((Rec_D_80016000 *)arg1)->unk_00.at02_s16.v;
    SPAD_NV(scratch, s32, 0x44) = ((Rec_D_80016000 *)arg1)->unk_04.at02_s16.v;
    SPAD_NV(scratch, s32, 0x48) = ((Rec_D_80016000 *)arg1)->unk_08.at02_s16.v;

    ReadRotMatrix(&matrix);
    rotVertex0 = (u8 *)scratch;
    ASM_KEEP_NV(rotVertex0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    rotVertex0 = (void *)((unsigned long)rotVertex0 | 0x50);
    rotVertex1 = (u8 *)scratch;
    ASM_KEEP_NV(rotVertex1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    rotVertex1 = (void *)((unsigned long)rotVertex1 | 0x40);
    TransMatrix(rotVertex0, rotVertex1);
    rotVertex0 = &arg2->rotation[0];
    rotVertex1 = (u8 *)scratch;
    ASM_KEEP_NV(rotVertex1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    rotVertex1 = (void *)((unsigned long)rotVertex1 | 0x50);
    RotMatrix(rotVertex0, rotVertex1);

    if (arg2->flags & 1) {
        SPAD(scratch, s32, 0x30) = -SPAD(scratch, s32, 0x30);
    }
    if (arg2->flags & 2) {
        SPAD(scratch, s32, 0x34) = -SPAD(scratch, s32, 0x34);
    }

    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    CompMatrix(&matrix, (void *)0x1F800050, (void *)0x1F8000D0);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    depthOffset = arg3;
    root = D_80083160[0];
    SPAD(scratch, void *, 0x20) = root + 0xB0;
    prim = *(u8 **)(root + 0x8D0);
    arg2->flags |= 0x8000;

    face = *(u8 **)(*(u8 **)(globalBase + 0x1E0) + arg2->meshIndex * 4);

    for (;;) {
        vertexIndex = ((S_800463EC_1 *)face)->unk_00;
        vertexTransfer = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_00;
        vertexIndex = ((S_800463EC_1 *)face)->unk_02;
        SPAD_NV(scratch, s32, 0x70) = vertexTransfer;
        vertexTransfer = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_00;
        vertexIndex = ((S_800463EC_1 *)face)->unk_04;
        SPAD_NV(scratch, s32, 0x78) = vertexTransfer;
        vertexTransfer = ((S_800463EC_1 *)face)->unk_06;
        vertexIndex = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_00;
        vertexTransfer = (vertexTransfer << 3) + (unsigned long)vertexTable;
        SPAD_NV(scratch, s32, 0x80) = vertexIndex;
        vertexIndex = ((S_800463EC_1 *)face)->unk_00;
        vertexTransfer = ((S_800463EC_3 *)((u8 *)vertexTransfer))->unk_00;
        vertexIndex = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_04;
        SPAD_NV(scratch, u16, 0x74) = vertexIndex;
        vertexIndex = ((S_800463EC_1 *)face)->unk_02;
        vertexIndex = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_04;
        rotVertex0 = (u8 *)scratch + 0x70;
        SPAD_NV(scratch, u16, 0x7C) = vertexIndex;
        vertexIndex = ((S_800463EC_1 *)face)->unk_04;
        rotVertex1 = (u8 *)scratch + 0x78;
        vertexIndex = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_04;
        rotVertex2 = (u8 *)scratch + 0x80;
        SPAD_NV(scratch, u16, 0x84) = vertexIndex;
        vertexIndex = ((S_800463EC_1 *)face)->unk_06;
        rotVertex3 = (u8 *)scratch + 0x88;
        SPAD_NV(scratch, s32, 0x88) = vertexTransfer;
        vertexTransfer = ((S_800463EC_2 *)((u8 *)vertexTable + vertexIndex * 8))->unk_04;
        SPAD_NV(scratch, u16, 0x8C) = vertexTransfer;
        ASM_JALDELAY_PIN(vertexTransfer);   /* MATCH pin: slus-diff */

        SPAD(scratch, s32, 0xC0) = RotAverage4(
            rotVertex0,
            rotVertex1,
            rotVertex2,
            rotVertex3,
            prim + 8,
            prim + 0x10,
            prim + 0x18,
            prim + 0x20,
            scratch + 0x90,
            scratch + 0x94);

        kind = arg2->flags & 3;
        switch (kind) {
        case 0:
            a0 = ((S_800463EC_4 *)prim)->unk_08;
            a1 = ((S_800463EC_4 *)prim)->unk_10;
            a2 = ((S_800463EC_4 *)prim)->unk_18;
            break;
        case 1:
            a0 = ((S_800463EC_4 *)prim)->unk_10;
            a1 = ((S_800463EC_4 *)prim)->unk_08;
            a2 = ((S_800463EC_4 *)prim)->unk_20;
            break;
        case 2:
            a0 = ((S_800463EC_4 *)prim)->unk_20;
            a1 = ((S_800463EC_4 *)prim)->unk_18;
            a2 = ((S_800463EC_4 *)prim)->unk_10;
            break;
        default:
            a0 = ((S_800463EC_4 *)prim)->unk_18;
            a1 = ((S_800463EC_4 *)prim)->unk_20;
            a2 = ((S_800463EC_4 *)prim)->unk_08;
            break;
        }

        SPAD(scratch, s32, 0x114) = NormalClip(a0, a1, a2);
        if (SPAD(scratch, s32, 0x114) > 0) {
            depth = SPAD(scratch, s32, 0xC0) - depthOffset;
            SPAD(scratch, s32, 0xC0) = depth;
            if (depth < 0x1E0U) {
                NormalColorCol(
                    textureTable + ((S_800463EC_1 *)face)->unk_10 * 8,
                    (u8 *)arg2 + 0xC,
                    prim + 4);

                ((S_800463EC_4 *)prim)->unk_0C.at00.v = ((S_800463EC_1 *)face)->unk_08;
                ((S_800463EC_4 *)prim)->unk_0C.at02.v += arg2->texture;
                ((S_800463EC_4 *)prim)->unk_14.at00.v = ((S_800463EC_1 *)face)->unk_0C;

                colour = arg2->colour;
                if (colour != 0) {
                    ((S_800463EC_4 *)prim)->unk_14.at02.v = colour + (((S_800463EC_4 *)prim)->unk_14.at02.v & 0xFF9F);
                }

                ((S_800463EC_4 *)prim)->unk_1C = ((S_800463EC_1 *)face)->unk_12;
                ((S_800463EC_4 *)prim)->unk_24 = ((S_800463EC_1 *)face)->unk_14;
                SetPolyFT4(prim);

                flags = arg2->flags;
                if (flags & 8) {
                    if (flags & 4) {
                        ((S_800463EC_4 *)prim)->unk_07 |= 2;
                    }
                }

                AddPrim((u8 *)SPAD(scratch, void *, 0x20) + SPAD(scratch, s32, 0xC0) * 4, prim);
                prim += 0x28;
                arg2->flags &= 0x7FFF;
            }
        }

        if (((S_800463EC_1 *)face)->unk_16 == 1 && ((S_800463EC_1 *)face)->unk_17 < 0) {
            break;
        }
        face += 0x18;
    }

    PopMatrix();
    *(u8 **)((u8 *)((S_800463EC_5 *)globalBase)->unk_00 + 0x8D0) = prim;
}

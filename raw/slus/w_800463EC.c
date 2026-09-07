#include "common.h"

#include "common.h"

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

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))
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
    register volatile u8 *scratch ASM_REG("$18");
    register u32 vertexIndex ASM_REG("$2");
    register unsigned long vertexTransfer ASM_REG("$3");
    register void *rotVertex0 ASM_REG("$4");
    register void *rotVertex1 ASM_REG("$5");
    register void *rotVertex2 ASM_REG("$6");
    register void *rotVertex3 ASM_REG("$7");
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
    ASM_MEM_BARRIER();
    scratch = (volatile u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);

    SPAD_NV(scratch, s32, 0x30) = vertexIndex;
    SPAD_NV(scratch, s32, 0x34) = arg2->scale[1];
    SPAD_NV(scratch, s32, 0x38) = arg2->scale[2];
    SPAD_NV(scratch, s32, 0x40) = FIELD(arg1, s16, 2);
    SPAD_NV(scratch, s32, 0x44) = FIELD(arg1, s16, 6);
    SPAD_NV(scratch, s32, 0x48) = FIELD(arg1, s16, 0xA);

    ReadRotMatrix(&matrix);
    rotVertex0 = (u8 *)scratch;
    ASM_KEEP_NV(rotVertex0);
    rotVertex0 = (void *)((unsigned long)rotVertex0 | 0x50);
    rotVertex1 = (u8 *)scratch;
    ASM_KEEP_NV(rotVertex1);
    rotVertex1 = (void *)((unsigned long)rotVertex1 | 0x40);
    TransMatrix(rotVertex0, rotVertex1);
    rotVertex0 = &arg2->rotation[0];
    ASM_KEEP_NV(rotVertex0);
    rotVertex1 = (u8 *)scratch;
    ASM_KEEP_NV(rotVertex1);
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
        vertexIndex = FIELD(face, u16, 0);
        vertexTransfer = FIELD((u8 *)vertexTable + vertexIndex * 8, s32, 0);
        vertexIndex = FIELD(face, u16, 2);
        SPAD_NV(scratch, s32, 0x70) = vertexTransfer;
        vertexTransfer = FIELD((u8 *)vertexTable + vertexIndex * 8, s32, 0);
        vertexIndex = FIELD(face, u16, 4);
        SPAD_NV(scratch, s32, 0x78) = vertexTransfer;
        vertexTransfer = FIELD(face, u16, 6);
        vertexIndex = FIELD((u8 *)vertexTable + vertexIndex * 8, s32, 0);
        vertexTransfer = (vertexTransfer << 3) + (unsigned long)vertexTable;
        SPAD_NV(scratch, s32, 0x80) = vertexIndex;
        vertexIndex = FIELD(face, u16, 0);
        vertexTransfer = FIELD((u8 *)vertexTransfer, s32, 0);
        vertexIndex = FIELD((u8 *)vertexTable + vertexIndex * 8, u16, 4);
        SPAD_NV(scratch, u16, 0x74) = vertexIndex;
        vertexIndex = FIELD(face, u16, 2);
        vertexIndex = FIELD((u8 *)vertexTable + vertexIndex * 8, u16, 4);
        rotVertex0 = (u8 *)scratch + 0x70;
        SPAD_NV(scratch, u16, 0x7C) = vertexIndex;
        vertexIndex = FIELD(face, u16, 4);
        rotVertex1 = (u8 *)scratch + 0x78;
        vertexIndex = FIELD((u8 *)vertexTable + vertexIndex * 8, u16, 4);
        rotVertex2 = (u8 *)scratch + 0x80;
        SPAD_NV(scratch, u16, 0x84) = vertexIndex;
        vertexIndex = FIELD(face, u16, 6);
        rotVertex3 = (u8 *)scratch + 0x88;
        SPAD_NV(scratch, s32, 0x88) = vertexTransfer;
        vertexTransfer = FIELD((u8 *)vertexTable + vertexIndex * 8, u16, 4);
        SPAD_NV(scratch, u16, 0x8C) = vertexTransfer;
        ASM_JALDELAY_PIN(vertexTransfer);

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
            a0 = FIELD(prim, s32, 8);
            a1 = FIELD(prim, s32, 0x10);
            a2 = FIELD(prim, s32, 0x18);
            break;
        case 1:
            a0 = FIELD(prim, s32, 0x10);
            a1 = FIELD(prim, s32, 8);
            a2 = FIELD(prim, s32, 0x20);
            break;
        case 2:
            a0 = FIELD(prim, s32, 0x20);
            a1 = FIELD(prim, s32, 0x18);
            a2 = FIELD(prim, s32, 0x10);
            break;
        default:
            a0 = FIELD(prim, s32, 0x18);
            a1 = FIELD(prim, s32, 0x20);
            a2 = FIELD(prim, s32, 8);
            break;
        }

        SPAD(scratch, s32, 0x114) = NormalClip(a0, a1, a2);
        if (SPAD(scratch, s32, 0x114) > 0) {
            depth = SPAD(scratch, s32, 0xC0) - depthOffset;
            SPAD(scratch, s32, 0xC0) = depth;
            if (depth < 0x1E0U) {
                NormalColorCol(
                    textureTable + FIELD(face, u16, 0x10) * 8,
                    (u8 *)arg2 + 0xC,
                    prim + 4);

                FIELD(prim, s32, 0xC) = FIELD(face, s32, 8);
                FIELD(prim, u16, 0xE) += arg2->texture;
                FIELD(prim, s32, 0x14) = FIELD(face, s32, 0xC);

                colour = arg2->colour;
                if (colour != 0) {
                    FIELD(prim, u16, 0x16) = colour + (FIELD(prim, u16, 0x16) & 0xFF9F);
                }

                FIELD(prim, u16, 0x1C) = FIELD(face, u16, 0x12);
                FIELD(prim, u16, 0x24) = FIELD(face, u16, 0x14);
                SetPolyFT4(prim);

                flags = arg2->flags;
                if (flags & 8) {
                    if (flags & 4) {
                        FIELD(prim, u8, 7) |= 2;
                    }
                }

                AddPrim((u8 *)SPAD(scratch, void *, 0x20) + SPAD(scratch, s32, 0xC0) * 4, prim);
                prim += 0x28;
                arg2->flags &= 0x7FFF;
            }
        }

        if (FIELD(face, u8, 0x16) == 1 && FIELD(face, s8, 0x17) < 0) {
            break;
        }
        face += 0x18;
    }

    PopMatrix();
    *(u8 **)((u8 *)FIELD(globalBase, void *, 0) + 0x8D0) = prim;
}

#include "common.h"

typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct S_8002E5E8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

typedef struct S_8004F330_Node {
    s32 unk0;
    S_8002E5D8 *unk4;
    S_8002E5E8 *unk8;
    s32 unkC;
} S_8004F330_Node;

typedef struct S_8004F330_Entity {
    u8 pad0[0x204];
    S_8002E5E8 hdr;
    u8 pad1[0x220 - 0x210];
    S_8004F330_Node *ptrArray[7];
    S_8004F330_Node nodeArray[7];
    S_8002E5D8 bodyArray[7];
} S_8004F330_Entity;

void func_8004F330(S_8004F330_Entity *a0, s32 a1)
{
    register S_8004F330_Entity *self ASM_REG("$11") = a0;
    register s32 i ASM_REG("$7");
    register u8 *bodyBase ASM_REG("$6");
    register u8 *ptrBase ASM_REG("$8");
    register s32 nodeOff ASM_REG("$9");
    register s32 bodyOff ASM_REG("$10");
    register S_8002E5E8 *hdr ASM_REG("$14");
    register u8 *srcHi ASM_REG("$13");
    register S_8002E5D8 *src ASM_REG("$12");
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;

    ASM_USE(self);
    if (a1 > 0) {
        i = 0;
        srcHi = (u8 *)0x80030000;
        ASM_KEEP(srcHi);
        src = (S_8002E5D8 *)(srcHi - 0x1A28);
        hdr = &self->hdr;
        bodyOff = 0x2AC;
        bodyBase = (u8 *)self;
        nodeOff = 0x23C;
        ptrBase = (u8 *)self;
        do {
            register S_8002E5D8 *body ASM_REG("$4");

            body = (S_8002E5D8 *)((u8 *)self + bodyOff);
            bodyOff += 0x10;
            tmp0 = *(s32 *)(srcHi - 0x1A28);
            *(S_8004F330_Node **)(ptrBase + 0x220) =
                (S_8004F330_Node *)((u8 *)self + nodeOff);
            *(s32 *)(bodyBase + 0x2AC) = tmp0;
            tmp1 = src->unk4;
            nodeOff += 0x10;
            *(s32 *)(bodyBase + 0x2B0) = tmp1;
            tmp2 = src->unk8;
            ptrBase += 4;
            *(s32 *)(bodyBase + 0x2B4) = tmp2;
            tmp3 = src->unkC;
            i += 1;
            *(S_8002E5D8 **)(bodyBase + 0x240) = body;
            *(S_8002E5E8 **)(bodyBase + 0x244) = hdr;
            *(s32 *)(bodyBase + 0x2B8) = tmp3;
            bodyBase += 0x10;
        } while (i < a1);
    }

    self->hdr.unk0 = D_8002E5E8.unk0;
    self->hdr.unk4 = D_8002E5E8.unk4;
    self->hdr.unk8 = D_8002E5E8.unk8;
}

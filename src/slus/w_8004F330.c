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

void func_8004F330(S_8004F330_Entity *entity, s32 node_count)
{
    s32 i;
    s32 w0;

    for (i = 0; i < node_count; i++) {
        w0 = D_8002E5D8.unk0;
        entity->ptrArray[i] = &entity->nodeArray[i];
        entity->bodyArray[i].unk0 = w0;
        entity->bodyArray[i].unk4 = D_8002E5D8.unk4;
        entity->bodyArray[i].unk8 = D_8002E5D8.unk8;
        entity->bodyArray[i].unkC = D_8002E5D8.unkC;
        entity->nodeArray[i].unk4 = &entity->bodyArray[i];
        entity->nodeArray[i].unk8 = &entity->hdr;
    }
    entity->hdr.unk0 = D_8002E5E8.unk0;
    entity->hdr.unk4 = D_8002E5E8.unk4;
    entity->hdr.unk8 = D_8002E5E8.unk8;
}

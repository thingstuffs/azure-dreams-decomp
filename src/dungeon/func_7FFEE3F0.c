#include "common.h"

extern u32 D_8008BC58[];
extern s8 D_800CFC70[];
extern s32 D_800CFC7C[];

typedef struct SubStruct {
    u8 pad0[8];
    u16 unk8;
} SubStruct;

typedef struct Actor {
    SubStruct *sub;
    u8 pad4[0x64 - 4];
    s16 unk64;
    s16 unk66;
    void *unk68;
    s32 unk6C;
} Actor;

/* Advance the actor's signed counter, resetting it and loading indexed state when positive. */
void func_8008BB50(Actor *actor) {
    SubStruct *sub = actor->sub;

    sub->unk8 += 0x200;
    if ((s16)actor->sub->unk8 > 0) {
        actor->sub->unk8 = 0;
        actor->unk68 = D_8008BC58;
        actor->unk64 = D_800CFC70[actor->unk66];
        actor->unk6C = D_800CFC7C[actor->unk66];
    }
}

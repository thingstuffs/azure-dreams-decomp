#include "common.h"

extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern void *D_800CFC7C[];

typedef struct {
    u16 pad0[5];
    u16 unkA;
} SubStruct;

typedef struct {
    SubStruct *sub;
    u8 pad4[96];
    s16 unk64;
    s16 unk66;
    void *unk68;
    void *unk6C;
} MainStruct;

void func_8008BACC(MainStruct *arg0) {
    arg0->sub->unkA -= 0x200;
    if ((s16)arg0->sub->unkA < 0) {
        arg0->sub->unkA = 0;
        arg0->unk68 = D_8008BC58;
        arg0->unk64 = (s8)D_800CFC70[arg0->unk66];
        arg0->unk6C = D_800CFC7C[arg0->unk66];
    }
}

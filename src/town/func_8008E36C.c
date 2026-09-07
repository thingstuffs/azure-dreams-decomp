#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
} Func8008E36CInner;

typedef struct {
    Func8008E36CInner* inner;
    u8 pad4[0x60];
    s16 unk64;
    s16 index;
    void* unk68;
    void* unk6C;
} Func8008E36CArg;

extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern void* D_800CFC7C[];

void func_8008BACC(Func8008E36CArg* arg0) {
    arg0->inner->unkA -= 0x200;
    if (arg0->inner->unkA < 0) {
        arg0->inner->unkA = 0;
        arg0->unk68 = D_8008BC58;
        arg0->unk64 = (s8)D_800CFC70[arg0->index];
        arg0->unk6C = D_800CFC7C[arg0->index];
    }
}

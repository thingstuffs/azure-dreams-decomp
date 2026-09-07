#include "common.h"

typedef struct Child {
    u8 unk00[0x22];
    s16 unk22;
    u8 unk24[2];
    u8 unk26;
    u8 unk27;
    u8 unk28[0x58];
    u32 unk80;
} Child;

typedef struct Object Object;

struct Object {
    u8 unk00[0x4d];
    u8 unk4d;
    u8 unk4e[0x16];
    s16 unk64;
    u8 unk66[2];
    void (*unk68)(Object *);
    u8 unk6c[8];
    Child *child;
};

extern u8 D_80082040[9];
extern u8 D_80082538[9];
extern void func_80037030(void *, void *, Object *, s32, s16, u32);
extern void func_80036574(Object *);

void func_800364EC(Object *arg0) {
    s16 value;

    value = arg0->child->unk22 - (arg0->child->unk26 - 1);
    arg0->unk4d = arg0->child->unk27;
    func_80037030(D_80082538, D_80082040, arg0, 1, value,
                  arg0->child->unk80);
    arg0->unk64 = 0x5a;
    arg0->unk68 = func_80036574;
}

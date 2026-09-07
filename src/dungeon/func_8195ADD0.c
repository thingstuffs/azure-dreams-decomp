#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    void *unk8;
    s32 unkC;
} Inner;

typedef struct {
    s32 unk0;
    s8 unk4;
    s8 unk5;
    s8 pad6[2];
    Inner *unk8;
    s8 padC[8];
    u16 unk14;
} Object;

void func_8195ADD0(Object *arg0, s16 arg1) {
    s32 base;
    arg0->unk4 = (s8)arg1;
    arg0->unk5 = 0;
    base = arg0->unk8->unkC;
    arg0->unk14 &= 0x9FFF;
    arg0->unk0 = base + arg1 * 0x18;
}

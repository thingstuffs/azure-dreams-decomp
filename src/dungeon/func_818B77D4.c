#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} Inner818B77D4;

typedef struct {
    u8 pad0[8];
    void *unk8;
    u8 padC[4];
    void *unk10;
    u8 pad14[12];
    Inner818B77D4 unk20;
} Obj818B77D4;

typedef struct {
    s32 unk0;
    u8 pad4[14];
    u16 unk12;
    u8 pad14[4];
    s32 unk18;
} Arg0818B77D4;

typedef struct {
    s32 words[6];
} Arg1818B77D4;

extern Obj818B77D4 *func_8003FC64();
extern s32 rand(void);
extern void func_8004491C(Obj818B77D4 *, void *);
extern u8 D_800242FC[12];
extern u8 D_80024A64[12];

void func_818B77D4(Arg0818B77D4 *arg0, Arg1818B77D4 *arg1) {
    Obj818B77D4 *obj;
    Inner818B77D4 *inner;
    u16 sourceValue;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->unk10 = D_800242FC;
        inner = &obj->unk20;
        inner->unk0 = arg0->unk0;
        inner->unk6 = 0;
        sourceValue = arg0->unk12;
        inner->unkA = 0x30;
        inner->unk8 = sourceValue;
        inner->unkC = rand() % 0x1000;
        inner->unkE = rand() % 0x1000;
        inner->unk10 = arg0->unk18;
        *(Arg1818B77D4 *)obj->unk8 = *arg1;
        func_8004491C(obj, D_80024A64);
    }
}

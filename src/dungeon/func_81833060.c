#include "common.h"

typedef struct StructInner {
    s8 pad0[0x52];
    u16 unk52;
} StructInner;

typedef struct StructA0 {
    StructInner *inner;
} StructA0;

typedef struct StructA2 {
    u8 pad0[0x14];
    u16 unk14;
    u8 pad16[0x1C - 0x14 - 2];
    u16 unk1C;
    u16 unk1E;
} StructA2;

typedef struct {
    s32 v;
    s32 pad[2];
} D_800814A0_t;

extern D_800814A0_t D_800814A0;
extern void func_800478B8(void *arg0);

void func_81833060(StructA0 *arg0, void *arg1, StructA2 *arg2) {
    u16 val;

    val = arg2->unk1E - 0x80;
    arg2->unk1E = val;
    arg2->unk1C = val;
    arg0->inner->unk52 |= 0x8000;
    func_800478B8(arg2);
    if (arg2->unk14 & 0x6000) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0.v |= 0x8000;
    }
}

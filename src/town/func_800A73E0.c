#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_800A73E0;

extern S_800A73E0 D_80083780;
extern S_800A73E0 D_80100D98;
extern u8 D_800A4F4C[];
extern void func_800A4CE8(void *, s32);

/* Copy the default state and initialize the supplied control block. */
void func_800A4B40(void *control) {
    S_800A73E0 *src = &D_80083780;
    S_800A73E0 *dst = &D_80100D98;
    s32 value;

    D_80100D98.unk0 = D_80083780.unk0;
    value = src->unk4;
    dst->unk8 = src->unk8;
    dst->unk4 = value;
    *(void **)((u8 *)control + 0x24) = D_800A4F4C;
    *(s32 *)((u8 *)control + 0x30) = 0;
    func_800A4CE8(control, value);
}

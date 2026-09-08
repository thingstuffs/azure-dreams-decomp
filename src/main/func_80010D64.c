#include "common.h"

extern s32 func_8004DA74(void *, void *, s32);
extern s16 D_80027F7C;
extern s16 D_800282B0;

typedef struct {
    void *unk0;
    struct {
        s8 pad[8];
        s16 unk8;
        s16 unkA;
    } *unk4;
} UnkTarget;

/* Initialize data pointers and layout values for three targets. */
void func_80023D64(void *context) {
    UnkTarget *target;

    target = *(UnkTarget **)((u8 *)context + 0x274);
    target->unk4->unk8 = 0xFA;
    target->unk4->unkA = 0x10;
    target->unk0 = &D_80027F7C;

    target = *(UnkTarget **)((u8 *)context + 0x268);
    target->unk0 = (void *) func_8004DA74((u8 *)context + 0xA4, &D_800282B0, 1);
    target->unk4->unk8 = 0x178;
    target->unk4->unkA = 0x90;

    target = *(UnkTarget **)((u8 *)context + 0x27C);
    target->unk0 = (u8 *)context + 0x1AC;
    target->unk4->unk8 = 0x10C;
    target->unk4->unkA = 0x18;
}

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

void func_80023D64(void *arg0) {
    UnkTarget *temp;

    temp = *(UnkTarget **)((u8 *)arg0 + 0x274);
    temp->unk4->unk8 = 0xFA;
    temp->unk4->unkA = 0x10;
    temp->unk0 = &D_80027F7C;

    temp = *(UnkTarget **)((u8 *)arg0 + 0x268);
    temp->unk0 = (void *) func_8004DA74((u8 *)arg0 + 0xA4, &D_800282B0, 1);
    temp->unk4->unk8 = 0x178;
    temp->unk4->unkA = 0x90;

    temp = *(UnkTarget **)((u8 *)arg0 + 0x27C);
    temp->unk0 = (u8 *)arg0 + 0x1AC;
    temp->unk4->unk8 = 0x10C;
    temp->unk4->unkA = 0x18;
}

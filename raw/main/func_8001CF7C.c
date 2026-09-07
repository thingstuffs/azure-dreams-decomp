#include "common.h"

extern s32 func_80051B50(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80051520(void *arg0, s32 *arg1, s32 arg2);
extern void func_80051804(s32 arg0, s32 arg1, s32 *arg2);
extern void func_80051900(s32 *arg0);
extern s32 D_80084158;
extern s32 D_804005EC;

typedef struct {
    u8 pad8[8];
    s16 unk8;
    s16 unkA;
} SubStruct2;

typedef struct {
    void *unk0;
    SubStruct2 *unk4;
} SubStruct;

typedef struct {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x80 - 0x24];
} BigEntry;

extern BigEntry D_8009DDE4[];

void func_8001CF7C(u8 *arg0) {
    SubStruct *temp;
    s32 sp10;

    temp = *(SubStruct **)(arg0 + 0x1EC);
    temp->unk4->unk8 = 0x70;
    temp->unk4->unkA = 0x10;
    temp->unk0 = (void *) &D_80084158;

    temp = *(SubStruct **)(arg0 + 0x1DC);
    temp->unk0 = (void *) func_80051B50(arg0 + 8, (*(s32 *)arg0 << 7) + (s32) &D_8009DDE4[0], 1);
    temp->unk4->unk8 = 0xF0;
    temp->unk4->unkA = 0x91;

    temp = *(SubStruct **)(arg0 + 0x1E0);
    temp->unk0 = (void *) func_80051B50(arg0 + 0x50, (s32) &D_804005EC, 1);
    temp->unk4->unk8 = 0x160;
    temp->unk4->unkA = 0x91;

    temp = *(SubStruct **)(arg0 + 0x1E8);
    func_80051804(D_8009DDE4[*(s32 *)arg0].unk20, 4, &sp10);
    func_80051900(&sp10);
    temp->unk0 = (void *) func_80051520(arg0 + 0x80, &sp10, 1);
    temp->unk4->unk8 = 0x13F;
    temp->unk4->unkA = 0x91;

    temp = *(SubStruct **)(arg0 + 0x1F4);
    temp->unk0 = (void *) (arg0 + 0xB0);
    temp->unk4->unk8 = 0xAE;
    temp->unk4->unkA = 0x18;
}

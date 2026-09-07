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

/* Sets up display element content and positions for the selected entry. */
void func_8001CF7C(u8 *screen) {
    SubStruct *element;
    s32 formatted_value;

    element = *(SubStruct **)(screen + 0x1EC);
    element->unk4->unk8 = 0x70;
    element->unk4->unkA = 0x10;
    element->unk0 = (void *) &D_80084158;

    element = *(SubStruct **)(screen + 0x1DC);
    element->unk0 = (void *) func_80051B50(screen + 8, (*(s32 *)screen << 7) + (s32) &D_8009DDE4[0], 1);
    element->unk4->unk8 = 0xF0;
    element->unk4->unkA = 0x91;

    element = *(SubStruct **)(screen + 0x1E0);
    element->unk0 = (void *) func_80051B50(screen + 0x50, (s32) &D_804005EC, 1);
    element->unk4->unk8 = 0x160;
    element->unk4->unkA = 0x91;

    element = *(SubStruct **)(screen + 0x1E8);
    func_80051804(D_8009DDE4[*(s32 *)screen].unk20, 4, &formatted_value);
    func_80051900(&formatted_value);
    element->unk0 = (void *) func_80051520(screen + 0x80, &formatted_value, 1);
    element->unk4->unk8 = 0x13F;
    element->unk4->unkA = 0x91;

    element = *(SubStruct **)(screen + 0x1F4);
    element->unk0 = (void *) (screen + 0xB0);
    element->unk4->unk8 = 0xAE;
    element->unk4->unkA = 0x18;
}

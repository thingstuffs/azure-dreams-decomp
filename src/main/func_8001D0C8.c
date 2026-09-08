#include "common.h"

extern s32 func_80051B50(void *arg0, void *arg1, s32 arg2);
extern s32 D_80084110;
extern s32 D_804005F0;

typedef struct {
    u8 pad8[8];
    s16 unk8;
    s16 unkA;
} SubStruct2;

typedef struct {
    void *unk0;
    SubStruct2 *unk4;
} SubStruct;

/* Initializes three object entries with data pointers and attribute values. */
void func_8001D0C8(u8 *object) {
    SubStruct *entry;

    entry = *(SubStruct **)(object + 0x1F0);
    entry->unk4->unk8 = 0x100;
    entry->unk4->unkA = 0x10;
    entry->unk0 = (void *) &D_80084110;

    entry = *(SubStruct **)(object + 0x1E4);
    entry->unk0 = (void *) func_80051B50(object + 0x5C, &D_804005F0, 1);
    entry->unk4->unk8 = 0x181;
    entry->unk4->unkA = 0x91;

    entry = *(SubStruct **)(object + 0x1F8);
    entry->unk0 = (void *) (object + 0x128);
    entry->unk4->unk8 = 0x112;
    entry->unk4->unkA = 0x18;
}

#include "common.h"

typedef struct SubStruct {
    u8 pad0[8];
    u16 unk8;
} SubStruct;

typedef struct MainStruct {
    SubStruct *sub;
    u8 pad4[0x60];
    s16 unk64;
    s16 unk66;
    void *unk68;
    s32 unk6c;
} MainStruct;

extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern s32 D_800CFC7C[];

/* Decrease the substructure value, clamping it to zero and resetting state when negative. */
void func_8008BBD4(MainStruct *object) {
    object->sub->unk8 -= 0x200;
    if ((s16)object->sub->unk8 < 0) {
        object->sub->unk8 = 0;
        object->unk68 = D_8008BC58;
        object->unk64 = (s8)D_800CFC70[object->unk66];
        object->unk6c = D_800CFC7C[object->unk66];
    }
}

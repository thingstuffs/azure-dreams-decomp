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

/* Selects a 24-byte entry and resets the object state and flags. */
void func_8195ADD0(Object *object, s16 entry_index) {
    s32 entry_base;
    object->unk4 = (s8)entry_index;
    object->unk5 = 0;
    entry_base = object->unk8->unkC;
    object->unk14 &= 0x9FFF;
    object->unk0 = entry_base + entry_index * 0x18;
}

#include "common.h"

typedef struct SubStruct8001D8F8 {
    s8 unk0[8];
    s16 unk8;
    s16 unkA;
} SubStruct8001D8F8;

typedef struct Entry8001D8F8 {
    void *unk0;
    SubStruct8001D8F8 *unk4;
} Entry8001D8F8;

typedef struct Owner8001D8F8 {
    s8 pad0[0x220];
    Entry8001D8F8 **unk220;
} Owner8001D8F8;

/* Initialize seven entries with layout values and pointers into their owner. */
void func_8001D8F8(Owner8001D8F8 *owner) {
    Entry8001D8F8 *entry;
    void *shared_data;

    entry = owner->unk220[0];
    entry->unk4->unk8 = 6;
    entry->unk4->unkA = 0x10;
    entry->unk0 = (s8 *) owner + 8;

    entry = owner->unk220[5];
    entry->unk4->unk8 = 0;
    entry->unk4->unkA = 0;
    entry->unk0 = (s8 *) owner + 0x80;

    entry = owner->unk220[6];
    entry->unk4->unk8 = 0x68;
    entry->unk4->unkA = 0;
    entry->unk0 = (s8 *) owner + 0xF8;

    entry = owner->unk220[1];
    entry->unk4->unk8 = 0xA0;
    shared_data = (s8 *) owner + 0x170;
    entry->unk4->unkA = 0x70;
    entry->unk0 = shared_data;

    entry = owner->unk220[2];
    entry->unk4->unk8 = 0;
    entry->unk4->unkA = 0x70;
    entry->unk0 = shared_data;

    entry = owner->unk220[3];
    entry->unk4->unk8 = 0xA0;
    entry->unk4->unkA = 0;
    entry->unk0 = shared_data;

    entry = owner->unk220[4];
    entry->unk4->unk8 = 0;
    entry->unk4->unkA = 0;
    entry->unk0 = shared_data;
}

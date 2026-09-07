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

void func_8001D8F8(Owner8001D8F8 *arg0) {
    Entry8001D8F8 *e;
    void *v1;

    e = arg0->unk220[0];
    e->unk4->unk8 = 6;
    e->unk4->unkA = 0x10;
    e->unk0 = (s8 *) arg0 + 8;

    e = arg0->unk220[5];
    e->unk4->unk8 = 0;
    e->unk4->unkA = 0;
    e->unk0 = (s8 *) arg0 + 0x80;

    e = arg0->unk220[6];
    e->unk4->unk8 = 0x68;
    e->unk4->unkA = 0;
    e->unk0 = (s8 *) arg0 + 0xF8;

    e = arg0->unk220[1];
    e->unk4->unk8 = 0xA0;
    v1 = (s8 *) arg0 + 0x170;
    e->unk4->unkA = 0x70;
    e->unk0 = v1;

    e = arg0->unk220[2];
    e->unk4->unk8 = 0;
    e->unk4->unkA = 0x70;
    e->unk0 = v1;

    e = arg0->unk220[3];
    e->unk4->unk8 = 0xA0;
    e->unk4->unkA = 0;
    e->unk0 = v1;

    e = arg0->unk220[4];
    e->unk4->unk8 = 0;
    e->unk4->unkA = 0;
    e->unk0 = v1;
}

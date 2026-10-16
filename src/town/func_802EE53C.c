#include "common.h"

extern void *func_80404DEC(void *, s32, s32);
extern u8 D_800841DC[], D_8008423C[], D_8008429C[];
typedef struct { u8 tag[8]; s16 x,y; } Primitive;
typedef struct { void *active; Primitive *primitive; } Entry;
typedef struct { s32 flags; u8 storage[0xB04]; Entry *item[4]; } Work;
void func_8040553C(Work *work) {
    void *storage = work->storage;
    Entry *item;
    func_80404DEC(storage, 0xF8, 0x48);
    item = work->item[3];
    item->primitive->x = 0xA0; item->primitive->y = 0xB0; item->active = storage;
    item = work->item[0];
    item->primitive->x = 0x60; item->primitive->y = 0x88; item->active = D_800841DC;
    item = work->item[1];
    item->primitive->x = 0xD0; item->primitive->y = 0x88; item->active = D_8008423C;
    item = work->item[2];
    item->primitive->x = 0x20; item->primitive->y = 0x88; item->active = D_8008429C;
}

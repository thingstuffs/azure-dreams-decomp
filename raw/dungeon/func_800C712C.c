#include "common.h"

typedef struct CoordBlock {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} CoordBlock;

typedef struct DescBlock {
    u8 pad0[6];
    s16 pre6;
    void *page;
    u8 padC[4];
    s16 size;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    u16 copy;
    u16 mode;
} DescBlock;

typedef struct TailBlock {
    u8 pad0[2];
    s16 kind;
    s16 value;
    s16 arg;
} TailBlock;

typedef struct ObjectBlock {
    u8 pad0[8];
    CoordBlock *coords;
    DescBlock *desc;
    void *resource;
} ObjectBlock;

extern s32 D_80045C34[3];
extern u8 D_800CC744[];
extern u8 D_800E03D4[];

extern ObjectBlock *func_8003FC64(s32 arg0);
extern void func_8004491C(ObjectBlock *obj, s32 *table);

ObjectBlock *func_800CC88C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    ObjectBlock *obj;
    TailBlock *tail;
    CoordBlock *coords;
    DescBlock *desc;

    obj = func_8003FC64(2);
    if (obj != 0) {
    obj->resource = D_800CC744;
    func_8004491C(obj, D_80045C34);
    coords = obj->coords;
    coords->x = (s16)(((arg0 << 16) >> 10) + 0x20);
    coords->y = (s16)(((arg1 << 16) >> 10) + 0x20);
    coords->z = arg2;
    desc = obj->desc;
    desc->page = D_800E03D4;
    desc->flags |= 0xC;
    desc->mode = (arg4 << 16) != 0 ? 0x6000 : 0x3000;
    desc->copy = desc->mode;
    desc->size = (arg4 << 16) != 0 ? 0x60 : 0x20;
    desc->pre6 = 0x20;
    tail = (TailBlock *)((u8 *)obj + 0x20);
    tail->value = arg3;
    tail->kind = 4;
    tail->arg = arg4;
    }
    return obj;
}

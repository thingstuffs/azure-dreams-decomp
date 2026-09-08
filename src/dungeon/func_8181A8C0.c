#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
} D8181A8C0Header;

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fa;
} D8181A8C0Vector;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[4];
    u8 fc;
    u8 fd;
    u8 fe;
    u8 padf;
    s16 f10;
    s16 f12;
    u16 f14;
    u8 pad16[6];
    s16 f1c;
    s16 f1e;
} D8181A8C0Asset;

typedef struct {
    u8 pad0[8];
    D8181A8C0Vector *field8;
    D8181A8C0Asset *fieldc;
    void *field10;
} D8181A8C0Object;

extern u8 D_80045340[];
extern u8 D_800DE870[9];
void *func_8003FC64(s32);
M2C_UNK func_8004491C(void *, void *);
void func_8003DB94(void *, void *, s32);
extern M2C_UNK D_8002404C;

/* Creates and initializes an object at an offset from the supplied origin. */
void func_8181A8C0(void *unused_context, void *origin, s32 unused_id, s16 offset_x, s16 offset_y, s16 offset_z) {
    D8181A8C0Asset *asset;
    D8181A8C0Object *object;
    s32 asset_param;
    s32 setup_mode;
    D8181A8C0Header *header;
    D8181A8C0Vector *position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        header = (D8181A8C0Header *)((u8 *)object + 0x20);
        header->f2 = 1;
        header->f4 = 1;
        object->field10 = &D_8002404C;
        func_8004491C(object, D_80045340);
        asset_param = 0x60;
        setup_mode = 2;
        asset = object->fieldc;
        asset->f10 = asset_param;
        asset->f6 = 0;
        asset->f14 = (s16) (asset->f14 | 0xC);
        position = object->field8;
        position->f2 = offset_x;
        position->f6 = (s16) offset_y;
        position->fa = (s16) offset_z;
        position->f2 += *(u16 *)((u8 *)origin + 2);
        position->f6 += *(u16 *)((u8 *)origin + 6);
        position->fa += *(u16 *)((u8 *)origin + 0xA);
        asset = object->fieldc;
        asset->f1e = 0x400;
        asset->f1c = 0x400;
        asset->fe = 0x80;
        asset->fd = 0x80;
        asset->fc = 0x80;
        asset->f12 = 0x7DCF;
        asset->f14 = (u16) (asset->f14 | 0x100);
        func_8003DB94(asset, D_800DE870, setup_mode);
    }
}

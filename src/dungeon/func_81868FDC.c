#include "common.h"

typedef struct {
    u8 pad0[8];
    void *dst;
    void *sprite;
    void *callback;
    u8 pad14[12];
    s32 value;
} Object;

typedef struct {
    u8 pad0[12];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    u16 flags10;
    s16 angle;
    u16 flags14;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} Sprite;

extern Object *func_8003FC64(s32);
extern void func_8003DB94(Sprite *, void *, s32);
extern void func_8004491C(Object *, void *);
extern u8 D_80024730[];
extern u8 D_80025368[];
extern u8 D_80045340[];

void func_81868FDC(s32 arg0, void *arg1) {
    Object *obj;
    Sprite *sprite;
    u16 *dst;
    u16 *src;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_80024730;
        sprite = obj->sprite;
        obj->value = arg0;
        sprite->b = 0x80;
        sprite->g = 0x80;
        sprite->r = 0x80;
        func_8003DB94(sprite, D_80025368, 0);
        sprite->scale_y = 0x4000;
        sprite->scale_x = 0x4000;
        sprite->angle = 0x7E0B;
        sprite->flags10 |= 0x60;
        sprite->flags14 |= 0x10C;
        func_8004491C(obj, D_80045340);
        dst = obj->dst;
        src = arg1;
        dst[1] = src[1];
        dst[3] = src[3];
        dst[5] = src[5];
    }
}

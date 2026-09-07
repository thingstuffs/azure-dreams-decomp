#include "common.h"

typedef struct Sprite {
    u8 pad0[6];
    s16 field6;
    u8 pad8[4];
    u8 colorC;
    u8 colorD;
    u8 colorE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 scale1C;
    s16 scale1E;
} Sprite;

typedef struct Object {
    u8 pad0[8];
    void *position;
    Sprite *sprite;
    void *callback;
} Object;

extern void func_8003DB94(Sprite *, void *, s32);
extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, void *);
extern u8 D_80045340;
extern u8 D_800DE870[];
extern u8 D_80165580;

void func_801655EC(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *call_data;
    Object *obj;
    Sprite *sprite;
    s32 word_08;
    u16 x;
    u16 y;
    u16 z;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = &D_80165580;
        func_8004491C(obj, &D_80045340);
        sprite = obj->sprite;
        sprite->field10 = 0x20;
        sprite->field6 = 6;
        sprite->flags14 |= 0xC;
        {
            register void *position ASM_REG("$3");

            position = obj->position;
            *(s32 *)((u8 *)position + 0) = *(s32 *)((u8 *)arg0 + 0);
#ifndef NON_MATCHING
            call_data = (u8 *)0x800E0000;
            ASM_KEEP(call_data);
            call_data -= 0x1790;
#else
            call_data = D_800DE870;
#endif
            *(volatile s32 *)((u8 *)position + 4) = *(s32 *)((u8 *)arg0 + 4);
            x = *(u16 *)((u8 *)position + 2);
            word_08 = *(s32 *)((u8 *)arg0 + 8);
            *(u16 *)((u8 *)position + 2) = (u16)(x + arg1);
            y = *(u16 *)((u8 *)position + 6);
            *(s32 *)((u8 *)position + 8) = word_08;
            z = *(u16 *)((u8 *)position + 0xA);
            *(u16 *)((u8 *)position + 6) = (u16)(y + arg2);
            *(u16 *)((u8 *)position + 0xA) = (u16)(z + arg3);
        }
        sprite = obj->sprite;
        sprite->scale1E = 0x800;
        sprite->scale1C = 0x800;
        sprite->colorE = 0x80;
        sprite->colorD = 0x80;
        sprite->colorC = 0x80;
        func_8003DB94(sprite, call_data, 0);
    }
}

/* MECHANISM: Four live arguments plus the allocated object produce the 0x28 frame and s1-s4/s0 save order.
   The volatile word-4 copy with held x/word_08/y/z locals gives retail's destination dependencies and scratch roles.
   A scoped v1 destination and kept 0x800e page carrier split the call-data address across both copy stores. */

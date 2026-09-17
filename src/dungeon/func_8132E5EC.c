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

extern void func_8003DB94(Sprite *, void *, s16);
extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, void *);
extern u8 D_80045340;
extern u8 D_800DE870[];
extern u8 D_80165580;

void func_801655EC(void *source_position, s32 x_offset, s32 y_offset, s32 z_offset) {
    Object *obj;
    Sprite *sprite;
    s32 z_fixed;
    u16 x;
    u16 y;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = &D_80165580;
        func_8004491C(obj, &D_80045340);
        sprite = obj->sprite;
        sprite->field10 = 0x20;
        sprite->field6 = 6;
        sprite->flags14 |= 0xC;
        {
            void *position;

            position = obj->position;
            *(s32 *)((u8 *)position + 0) = *(s32 *)((u8 *)source_position + 0);
            *(volatile s32 *)((u8 *)position + 4) = *(s32 *)((u8 *)source_position + 4);
            x = *(u16 *)((u8 *)position + 2);
            z_fixed = *(s32 *)((u8 *)source_position + 8);
            *(u16 *)((u8 *)position + 2) = (u16)(x + x_offset);
            y = *(u16 *)((u8 *)position + 6);
            *(s32 *)((u8 *)position + 8) = z_fixed;
            z_fixed = *(u16 *)((u8 *)position + 0xA) + z_offset;
            *(u16 *)((u8 *)position + 6) = (u16)(y + y_offset);
            *(u16 *)((u8 *)position + 0xA) = (u16)z_fixed;
        }
        sprite = obj->sprite;
        sprite->scale1E = 0x800;
        sprite->scale1C = 0x800;
        sprite->colorE = 0x80;
        sprite->colorD = 0x80;
        sprite->colorC = 0x80;
        func_8003DB94(sprite, D_800DE870, 0);
    }
}

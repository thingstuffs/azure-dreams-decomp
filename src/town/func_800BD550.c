#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BACB0_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BACB0_0_pre;   /* the 0x10 bytes before arg0 in func_800BACB0, addressed as arg0[-1] */

typedef struct S_800BACB0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800BACB0_1;   /* particlePrim in func_800BACB0 */



typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
} Position;

typedef struct Primitive {
    u8 pad0[8];
    void *image;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 angle;
    s16 scaleX;
    s16 scaleY;
    s16 scaleZ;
} Primitive;

typedef struct Core {
    u8 pad0[0x66];
    u16 angle;
    u8 pad68[0x2F];
    s8 index;
    s32 value;
    struct Core *parent;
} Core;

typedef struct Object {
    u8 pad0[8];
    Position *position;
    Primitive *primitive;
    void *update;
} Object;

extern Object *func_8003FD64();
extern void func_8004491C();
extern s32 rand(void);
extern void func_8008F104(Core *, Position *, void *);

extern u8 D_80045C34[];
extern u8 D_80046398[];
extern u8 D_80083160[];
extern u8 D_800B9CB8[];
extern u8 D_800B9EDC[];
extern u8 D_800B9F74[];
extern u8 D_800BA8C4[];
extern void *D_800D1BCC[];
extern u8 D_800F8A1C[];
extern u8 D_800F8A28[];

void func_800BACB0(Core *arg0, Position *arg1)
{
    s32 value;
    s32 quotient;
    s32 i;
    s32 childValue;
    s32 childY0;
    s32 childY1;
    s32 childY2;
    s32 childY3;
    u8 childBlue;
    Object *obj;
    Core *core;
    void *parent;
    Primitive *particlePrim;
    Primitive *texturePrim;
    Position *position;

    ((S_800BACB0_0_pre *)arg0)[-1].unk_00 = D_800B9CB8;
    quotient = rand();
    value = quotient;
    quotient >>= 12;
    if (value < 0) {
        quotient = (value + 0xFFF) >> 12;
    }

    quotient <<= 12;
    quotient = value - quotient;
    arg0->angle = quotient;
    arg0->index = 0;
    ASM_KEEP(quotient);   /* MATCH pin: load-bearing for the whole function shape */
    i = 0;
    do {
        obj = func_8003FD64(0x136, (u8 *)arg0 - 0x20);
        if (obj != NULL) {
            obj->update = D_800BA8C4;
            func_8004491C(obj, D_80046398);
            childValue = arg0->value;
            core = (Core *)((u8 *)obj + 0x20);
            core->parent = arg0;
            core->angle = 0;
            core->index = i;
            core->value = childValue;
            particlePrim = obj->primitive;
            particlePrim->scaleX = 0x1000;
            particlePrim->scaleY = 0x1000;
            particlePrim->scaleZ = 0xAAA;
            particlePrim->red = D_80083160[0xA8];
            particlePrim->green = D_80083160[0xA9];
            childBlue = D_80083160[0xAA];
            ((S_800BACB0_1 *)particlePrim)->unk_08 = i + 0xA;
            particlePrim->blue = childBlue;
            position = obj->position;
            position->x = arg1->x;
            childY0 = arg1->y;
            position->z = 0;
            position->y = childY0;
            func_8008F104(core, position, D_800D1BCC[i]);
        }
        i += 1;
    } while (i < 4);

    i = 0;
    do {
        obj = func_8003FD64(0x36, (u8 *)arg0 - 0x20);
        if (obj != NULL) {
            obj->update = D_800B9EDC;
            func_8004491C(obj, D_80045C34);
            childValue = arg0->value;
            core = (Core *)((u8 *)obj + 0x20);
            core->parent = arg0;
            core->index = i;
            core->value = childValue;
            texturePrim = obj->primitive;
            texturePrim->image = D_800F8A1C;
            texturePrim->blue = 0x80;
            texturePrim->green = 0x80;
            texturePrim->red = 0x80;
            texturePrim->unk16 = 0x370;
            texturePrim->unk18 = 0;
            texturePrim->angle = arg0->angle + (i << 10);
            texturePrim->scaleY = 0x1000;
            texturePrim->scaleX = 0x1000;
            position = obj->position;
            position->x = arg1->x;
            childY1 = arg1->y;
            position->z = 0xFF2C0000;
            childY1 += 0x200000;
            position->y = childY1;
        }
        i += 1;
    } while (i < 4);

    parent = (u8 *)arg0 - 0x20;
    obj = func_8003FD64(0x36, parent);
    if (obj != NULL) {
        obj->update = D_800B9EDC;
        func_8004491C(obj, D_80045C34);
        childValue = arg0->value;
        core = (Core *)((u8 *)obj + 0x20);
        core->parent = arg0;
        core->value = childValue;
        texturePrim = obj->primitive;
        texturePrim->image = D_800F8A28;
        texturePrim->blue = 0x80;
        texturePrim->green = 0x80;
        texturePrim->red = 0x80;
        texturePrim->unk16 = 0x370;
        texturePrim->unk18 = 0;
        texturePrim->angle = arg0->angle;
        texturePrim->scaleY = 0x1000;
        texturePrim->scaleX = 0x1000;
        position = obj->position;
        position->x = arg1->x;
        childY2 = arg1->y;
        position->z = 0xFF2C0000;
        childY2 += 0x200000;
        position->y = childY2;
    }

    obj = func_8003FD64(0x136, parent);
    if (obj != NULL) {
        obj->update = D_800B9F74;
        func_8004491C(obj, D_80046398);
        childValue = arg0->value;
        core = (Core *)((u8 *)obj + 0x20);
        core->parent = arg0;
        core->value = childValue;
        particlePrim = obj->primitive;
        particlePrim->scaleX = 0x1000;
        particlePrim->scaleY = 0x1000;
        particlePrim->scaleZ = 0x1000;
        particlePrim->angle = arg0->angle;
        particlePrim->red = D_80083160[0xA8];
        particlePrim->green = D_80083160[0xA9];
        particlePrim->blue = D_80083160[0xAA];
        position = obj->position;
        ((S_800BACB0_1 *)particlePrim)->unk_08 = 9;
        position->x = arg1->x;
        childY3 = arg1->y;
        position->z = 0;
        position->y = childY3;
    }
}

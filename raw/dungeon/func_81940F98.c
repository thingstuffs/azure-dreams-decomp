#include "common.h"

typedef struct Data {
    u16 pad0;
    u16 x;
    u16 pad4;
    u16 y;
    u16 pad8;
    u16 z;
} Data;

typedef struct Object {
    u8 pad0[8];
    Data *data;
    u8 padC[4];
    void *callback;
} Object;

extern Object *func_8003FD64();
extern s32 rand(void);
extern void func_8004491C(Object *, void *, Data *);
extern u8 D_800244E4[];
extern u8 D_80024734[];

void func_80024798(Object *arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    register Object *base ASM_REG("$17") = arg0;
    register s32 xoff ASM_REG("$18") = arg4;
    register s32 yoff ASM_REG("$19") = arg5;
    register s32 zoff ASM_REG("$20") = arg6;
    register s32 held_arg1 ASM_REG("$21") = arg1;
    register s32 held_arg2 ASM_REG("$23") = arg2;
    register s32 held_arg3 ASM_REG("$22") = arg3;
    Object *obj;
    Data *data;
    u8 *sub;
    s32 random;

    obj = func_8003FD64(0x211, base);
    if (obj != 0) {
        obj->callback = D_80024734;
        random = rand();
        obj->data->x =
            base->data->x +
            (random & 0xF) + (xoff - 8);
        random = rand();
        obj->data->y =
            base->data->y +
            (random & 0xF) + (yoff - 8);
        sub = (u8 *)obj + 0x20;
        random = rand();
        data = obj->data;
        data->z =
            base->data->z +
            (random & 0x1F) + (zoff - 0x10);
        *(s16 *)(sub + 0x14) = held_arg1;
        *(s16 *)(sub + 0x32) = held_arg3;
        func_8004491C(obj, D_800244E4, data);
        *(s32 *)(sub + 8) = held_arg2;
        ASM_KEEP(base);
        ASM_KEEP(held_arg1);
        ASM_KEEP(held_arg2);
        ASM_KEEP(held_arg3);
        ASM_KEEP(xoff);
        ASM_KEEP(yoff);
        ASM_KEEP(zoff);
    }
}

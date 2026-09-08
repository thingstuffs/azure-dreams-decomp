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
    Object *base = arg0;
    s32 xoff = arg4;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 yoff = arg5;
    s32 zoff = arg6;
    s32 held_arg1 = arg1;
    register s32 held_arg2 ASM_REG("$23") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 held_arg3 ASM_REG("$22") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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
        ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(xoff);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(yoff);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(zoff);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    }
}

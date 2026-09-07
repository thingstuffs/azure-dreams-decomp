#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64();
extern u8 D_80174AD4[9];
extern u8 D_80175F90[9];

void func_80174DA0(void *arg0, s32 arg1, u8 *arg2)
{
    void *obj;
    void *dst;
    void *aux;
    void *tail;
    void *p8;
    u16 value;

    obj = func_8003FD64(0x12, arg0);
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = D_80174AD4;
        dst = FIELD(obj, void *, 8);

        value = FIELD(FIELD(arg0, void *, 8), u16, 2);
        FIELD(dst, u16, 0xE) = value;
        FIELD(dst, u16, 2) = value;

        value = FIELD(FIELD(arg0, void *, 8), u16, 6);
        FIELD(dst, u16, 0x12) = value;
        FIELD(dst, u16, 6) = value;

        value = FIELD(FIELD(arg0, void *, 8), u16, 0xA);
        FIELD(dst, u16, 0x16) = value;
        FIELD(dst, u16, 0xA) = value;

        aux = FIELD(obj, void *, 0xC);
        FIELD(aux, void *, 8) = D_80175F90;
        FIELD(aux, s16, 0x1E) = 0x1000;
        FIELD(aux, s16, 0x1C) = 0x1000;
        FIELD(aux, s32, 0xC) = 0;
        FIELD(aux, s16, 6) = 8;

        p8 = FIELD(arg0, void *, 8);
        tail = (u8 *)obj + 0x20;
        FIELD(tail, s32, 0xC) = arg1;
        FIELD(tail, u8 *, 0x10) = arg2;
        FIELD(tail, void *, 0x1C) = p8;
        FIELD(tail, u8, 0x16) = *arg2;
        FIELD(obj, s32, 0x20) = 0x40;
        FIELD(tail, s32, 4) = 0;
    }
}

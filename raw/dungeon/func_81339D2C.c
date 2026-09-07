#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern u8 D_80083780[];
extern u8 D_80170BB0[];
extern u8 D_80173B88[];

void func_80170D2C(s32 unused, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register s32 n ASM_REG("$4");
    register s32 denom ASM_REG("$3");
    s32 qz;
    s32 qy;
    register s32 qx ASM_REG("$6");
    register s32 num ASM_REG("$2");
    s32 x;
    s32 y;
    s32 z;
    u8 *obj;
    u8 *work;
    u8 *prim;
    u8 *packet;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        work = obj + 0x20;
        FIELD(work, s16, 0x18) = arg1;
        FIELD(obj, void *, 0x10) = D_80170BB0;
        func_8004491C(obj, &D_80045340);
        packet = FIELD(obj, u8 *, 0xC);
        FIELD(packet, s16, 0x10) = 0x20;
        FIELD(packet, s16, 6) = 0;
        FIELD(packet, u16, 0x14) |= 0xC;
        prim = FIELD(obj, u8 *, 8);
        FIELD(prim, s32, 0) = FIELD(D_80083780, s32, 0);
        FIELD(prim, s32, 4) = FIELD(D_80083780, s32, 4);
        ASM_SCHED_BARRIER();
        FIELD(prim, s32, 8) = FIELD(D_80083780, s32, 8);
        FIELD(prim, u16, 2) += arg2;
        FIELD(prim, u16, 6) += arg3;
        FIELD(prim, u16, 0xA) += arg4;
        FIELD(work, u16, 0x1C) = FIELD(D_80083780, u16, 2);
        FIELD(work, u16, 0x1E) = FIELD(D_80083780, u16, 6);
        ASM_SCHED_BARRIER();
        num = arg1 << 16;
        n = num >> 16;
        ASM_SCHED_BARRIER();
        FIELD(work, u16, 0x20) = FIELD(D_80083780, u16, 0xA);
        denom = n;
        ASM_SCHED_BARRIER();
        num = -(arg2 << 16);
        if (n < 0) {
            denom = n + 7;
        }
        denom >>= 3;
        qx = num / denom;
        FIELD(work, volatile s32, 0x5C) = qx / 2;
        ASM_SCHED_BARRIER();
        qy = -(arg3 << 16) / denom;
        FIELD(work, volatile s32, 0x60) = qy / 2;
        ASM_SCHED_BARRIER();
        qz = -(arg4 << 16) / denom;
        FIELD(work, volatile s32, 0x64) = qz / 2;
        ASM_KEEP(n);
        x = qx;
        if (x < 0) x += 3;
        FIELD(work, s32, 0x68) = x >> 2;
        ASM_KEEP(qx);
        y = qy;
        if (y < 0) y += 3;
        FIELD(work, s32, 0x6C) = y >> 2;
        z = qz;
        if (z < 0) z += 3;
        FIELD(work, s32, 0x70) = z >> 2;
        packet = FIELD(obj, u8 *, 0xC);
        FIELD(packet, s16, 0x1E) = 0x1000;
        FIELD(packet, s16, 0x1C) = 0x1000;
        FIELD(packet, s8, 0xE) = 0;
        FIELD(packet, s8, 0xD) = 0;
        FIELD(packet, s8, 0xC) = 0;
        __builtin_memcpy(obj + 0x48, D_80173B88, 12);
        FIELD(packet, void *, 8) = obj + 0x48;
    }
}

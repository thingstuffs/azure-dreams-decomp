#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_8008F074(void *arg0, void *arg1, void *arg2);

extern u8 D_80046398[];
extern u8 D_800BF4CC[];
extern u8 D_800D2348[];
extern s32 D_800D2360;
extern s32 D_800814A0;

void func_800BF654(void *arg0)
{
    void *obj;
    void *part;
    void *setup;
    s32 *packet;

    obj = func_8003FC64(0x136);
    if (obj != NULL) {
        func_8004491C(obj, D_80046398);
        FIELD(obj, void *, 0x10) = D_800BF4CC;
        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x1C) = 0x1000;
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x20) = 0x1000;
        FIELD(part, s32, 0xC) = 0x808080;
        setup = (u8 *)obj + 0x20;
        FIELD(part, s16, 0x1A) = 0;
        FIELD(part, s32, 8) = 0x60;
        packet = FIELD(obj, s32 *, 8);
        packet[0] = 0x05400000;
        packet[1] = 0x02300000;
        packet[2] = 0;
        FIELD(setup, s32, 0x48) = D_800D2360;
        func_8008F074(setup, packet, D_800D2348);
    }
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    ASM_SCHED_BARRIER();
}

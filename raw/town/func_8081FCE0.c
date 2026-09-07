#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80020224[];
extern u8 D_80022768[];
extern u8 D_80023404[];
extern u8 D_80023DE0[];
extern u8 D_80023EB0[];
extern u8 D_8002415C[];
extern u8 D_80024470[];
extern u8 D_800244A0[];
extern s32 D_80024628[];
extern u8 D_80024640[];
extern u8 D_80024680[];
extern u8 D_800246E0[];
extern u8 D_80046398[];

extern void func_80022290();
extern void func_80033B9C();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8004E9E4();
extern void func_8006733C();
extern void func_8008F104();

void func_800224E0(void)
{
    s16 rect[4];
    s32 i;
    register s32 value ASM_REG("$2");
    u8 *obj;
    u8 *parent;
    u8 *slot;
    u8 *callback;
    u8 *prim;
    u8 *draw;
    u8 *callback_slot;
    u8 *tbl;
    u32 color;
    u8 *cbt;

    parent = NULL;
    callback = D_80020224;
    func_8004E9E4();
    D_80024628[0] = 0;
    func_80022290(D_800246E0);
    func_80033B9C(0xA4);

    obj = func_8003FC64(0x32);
    if (obj != NULL) {
        parent = obj + 0x20;
        prim = FIELD(obj, u8 *, 8);
        FIELD(obj, void *, 0x10) = D_80022768;
        FIELD(prim, s32, 0) = 0x04600000;
        FIELD(prim, s32, 4) = 0x03600000;
        FIELD(parent, void *, 0x48) = callback;
        func_8008F104(parent, prim, D_80024470);
    }

    i = 2;
    tbl = D_80023404;
    slot = parent + 8;
    do {
        obj = func_8003FC64(2);
        FIELD(slot, void *, 0x4C) = obj;
        if (obj != NULL) {
            FIELD(obj, void *, 0x10) = tbl;
            FIELD(obj, s16, 0x28) = i;
            FIELD(obj, void *, 0x20) = parent;
        }
        i--;
        slot -= 4;
    } while (i >= 0);

    obj = func_8003FC64(0x136);
    if (obj != NULL) {
        func_8004491C(obj, D_80046398);
        color = 0x00808080;
        cbt = obj + 0x28;
        ASM_SCHED_BARRIER();
        FIELD(obj, void *, 0x10) = D_80023DE0;
        ASM_SCHED_BARRIER();
        value = 0x1000;
        ASM_KEEP(value);
        prim = FIELD(obj, u8 *, 8);
        draw = FIELD(obj, u8 *, 0xC);
        FIELD(obj, void *, 0x20) = parent;
        FIELD(draw, s16, 0x1C) = value;
        FIELD(draw, s16, 0x1E) = value;
        FIELD(draw, s16, 0x20) = value;
        FIELD(draw, s32, 8) = 0x2C;
        FIELD(draw, s16, 0x12) = 0;
        FIELD(draw, s16, 0x14) = 0;
        FIELD(draw, s16, 0x10) = 0;
        FIELD(draw, s16, 0x16) = 0;
        FIELD(draw, s16, 0x18) = 0;
        FIELD(draw, s16, 0x1A) = 0;
        FIELD(draw, s32, 0) = 0;
        FIELD(draw, u8, 4) = 0;
        FIELD(draw, u8, 5) = 0;
        FIELD(draw, s32, 0xC) = color;
        FIELD(prim, s32, 0) = 0x04400000;
        FIELD(prim, s32, 4) = 0x02C00000;
        callback_slot = obj + 0x20;
        FIELD(prim, s32, 8) = 0;
        FIELD(callback_slot, void * volatile, 0x50) = callback;
        func_8008F104(cbt, FIELD(obj, u8 *, 8), D_800244A0);
    }

    i = 4;
    do {
        obj = func_8003FC64(0x100);
        if (obj != NULL) {
            func_8004491C(obj, D_8002415C);
            FIELD(obj, void *, 0x20) = parent;
            FIELD(obj, void *, 0x10) = D_80023EB0;
            obj += 0x20;
            FIELD(obj, s16, 0x22) = i;
            switch (i) {
            case 0:
                value = 1;
                FIELD(obj, s16, 0x20) = value;
                break;
            case 1:
                value = 2;
                FIELD(obj, s16, 0x20) = value;
                break;
            case 2:
                value = 3;
                FIELD(obj, s16, 0x20) = value;
                break;
            case 3:
            case 4:
            default:
                break;
            }
        }
        i--;
    } while (i >= 0);

    rect[0] = 0x40;
    rect[1] = 0x1D0;
    rect[2] = 0x20;
    rect[3] = 1;
    func_8006733C(rect, D_80024640);
    rect[0] = 0xC0;
    rect[1] = 0x1F8;
    rect[2] = 0x30;
    rect[3] = 1;
    func_8006733C(rect, D_80024680);
}

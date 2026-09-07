#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern s32 D_80027164;
extern s32 D_80028874;
extern s32 D_80045340;
extern s32 D_80083498;
extern u8 D_800DDC40[];

void *func_80027368(s16 arg0, s16 arg1, s16 arg2, void *arg3)
{
    void *object;
    void *part;
    void *sprite;
    void *work;

    object = func_8003FD64(0x12, &D_80083498);
    if (object != 0) {
        FIELD(object, void *, 0x10) = &D_80027164;
        func_8004491C(object, &D_80045340);
        part = FIELD(object, void *, 8);
        FIELD(part, s16, 2) = arg0;
        FIELD(part, s16, 6) = arg1;
        FIELD(part, s16, 0xA) =
            arg2 - (D_800DDC40[FIELD(arg3, u8, 0x13)] >> 1);
        sprite = FIELD(object, void *, 0xC);
        FIELD(sprite, void *, 8) = &D_80028874;
        FIELD(sprite, s16, 0x1E) = 0x1000;
        FIELD(sprite, s16, 0x1C) = 0x1000;
        work = (u8 *)object + 0x20;
        FIELD(work, void *, 4) = arg3;
        FIELD(work, s16, 0x66) = 0x10;
    }
    return object;
}

/* MECHANISM: Four call-live arguments naturally occupy s1-s4 while the
   allocated object occupies s0; three distinct subrecord locals separate
   the a0 and v1 lifetimes while preserving the retail access widths. */

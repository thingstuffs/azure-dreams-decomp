#include "common.h"

typedef struct SixWords {
    s32 word[6];
} SixWords;

extern s32 func_80024804();
extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 func_800647A0();
extern s16 func_80065F90();
extern s32 rand();

extern u8 D_80024C0C[];
extern s32 D_80045340;
extern u8 D_800DE39C[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void *func_80024E80(void *arg0, void *arg1) {
    void *obj;
    void *work;
    void *control;
    void *points;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 i;
    u8 *slot;
    s32 random;

    obj = func_8003FD64(0x212, (u8 *)arg0 - 0x20);
    if (obj != 0) {

    FIELD(obj, void *, 0x10) = D_80024C0C;
    work = (u8 *)obj + 0x20;
    FIELD(obj, s32, 0x20) = FIELD(arg0, s32, 0);
    FIELD(work, s16, 4) = 0;

    control = FIELD(obj, void *, 0xC);
    FIELD(control, u8, 0xE) = 0x80;
    FIELD(control, u8, 0xD) = 0x80;
    FIELD(control, u8, 0xC) = 0x80;
    FIELD(control, s16, 0x12) = 0x7DCF;
    FIELD(control, void *, 8) = D_800DE39C;
    FIELD(control, u16, 0x14) |= 0x100;

    random = rand();
    FIELD(control, s16, 0x1A) = random % 0x1000;
    FIELD(control, s16, 0x1E) = 0x400;
    FIELD(control, s16, 0x1C) = 0x400;

    func_8004491C(obj, &D_80045340);

    points = FIELD(obj, void *, 8);
    *(SixWords *)points = *(SixWords *)arg1;
    FIELD(points, s32, 0xC) = FIELD(arg0, s32, 0x20);
    FIELD(points, s32, 0x10) = FIELD(arg0, s32, 0x24);
    FIELD(points, s32, 0x14) = FIELD(arg0, s32, 0x28);

    dx = FIELD(arg0, s32, 0x20) - FIELD(arg1, s32, 0);
    dy = FIELD(arg0, s32, 0x24) - FIELD(arg1, s32, 4);
    dz = FIELD(arg0, s32, 0x28) - FIELD(arg1, s32, 8);

    FIELD(work, s16, 0xE) = func_80065F90(
        func_800647A0((((dx >> 12) * (dx >> 12)) +
                       ((dy >> 12) * (dy >> 12))) << 4),
        dz >> 4);
    FIELD(work, s16, 0x10) = func_80065F90(dx >> 4, dy >> 4);

    if (dx < 0) {
        FIELD(work, s16, 0x12) = 1;
    }

    i = 0;
    slot = work;
    do {
        FIELD(slot, s32, 0x14) = func_80024804(work, points, (s16)i);
        i++;
        slot += 4;
    } while (i < 3);

        return obj;
    }
    return 0;
}

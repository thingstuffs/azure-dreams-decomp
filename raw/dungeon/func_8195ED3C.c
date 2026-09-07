#include "common.h"

#define NULL 0
#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern s32 func_800B835C(void *, void *, s32, s32);
extern s32 D_80024388;
extern s32 D_80027380;
extern s32 D_800273B0;
extern s32 D_800DF334;

void *func_8195ED3C(void *arg0, s32 arg1)
{
    s32 rect[2];
    s32 common;
    void *obj;
    void *part;
    void *result;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        common = 0x200020;
        rect[1] = common;
        func_800B835C(&D_800DF334, rect, 1, 0);
        rect[0] = 0x01000360;
        rect[1] = common;
        func_800B835C(&D_80027380, rect, 1, 0);
        part = FIELD(obj, void *, 8);
        FIELD(obj, void *, 0x10) = &D_80024388;
        FIELD(part, u16, 2) = FIELD(arg0, u16, 2);
        FIELD(part, u16, 6) = FIELD(arg0, u16, 6);
        FIELD(part, u16, 0xA) = FIELD(arg0, u16, 0xA);
        part = FIELD(obj, void *, 0xC);
        FIELD(part, void *, 8) = &D_800273B0;
        FIELD(part, s16, 0x1E) = 0xC00;
        FIELD(part, s16, 0x1C) = 0xC00;
        FIELD(obj, s32, 0x2C) = arg1 - 0x20;
    }
    result = NULL;
    if (obj != NULL) {
        result = (u8 *)obj + 0x20;
    }
    return result;
}

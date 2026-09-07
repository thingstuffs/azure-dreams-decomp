#include "common.h"

#define NULL 0
#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern s32 func_800B835C(void *, void *, s32, s32);
extern s32 D_8002432C;
extern s32 D_800269D4;
extern s32 D_800269FC;
extern s32 D_800DF31C;

void *func_800244EC(void *arg0, s32 arg1)
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
        func_800B835C(&D_800DF31C, rect, 1, 0);
        rect[0] = 0x01200340;
        rect[1] = common;
        func_800B835C(&D_800269D4, rect, 1, 0);
        part = FIELD(obj, void *, 8);
        FIELD(obj, void *, 0x10) = &D_8002432C;
        FIELD(part, u16, 2) = FIELD(arg0, u16, 2);
        FIELD(part, u16, 6) = FIELD(arg0, u16, 6);
        FIELD(part, u16, 0xA) = FIELD(arg0, u16, 0xA);
        part = FIELD(obj, void *, 0xC);
        FIELD(part, void *, 8) = &D_800269FC;
        FIELD(part, s16, 0x1E) = 0xC00;
        FIELD(part, s16, 0x1C) = 0xC00;
        FIELD(obj, s32, 0x28) = arg1 - 0x20;
    }
    result = NULL;
    if (obj != NULL) {
        result = (u8 *)obj + 0x20;
    }
    return result;
}

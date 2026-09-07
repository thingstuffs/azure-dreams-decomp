#include "common.h"

typedef struct {
    u8 unk0[0xC];
    s32 unkC;
    s32 unk10;
} TownObject;

extern void func_80096D58();
extern s32 func_80096E08(TownObject *, void *);
extern s32 func_80096E9C(TownObject *, void *);

s32 func_80096FF4(TownObject *arg0) {
    void *arg1;
    s32 result;

    func_80096D58();
    arg1 = (u8 *)arg0 + 4;
    result = func_80096E08(arg0, arg1);
    result |= func_80096E9C(arg0, arg1);
    if (result & 0x11) {
        arg0->unkC = 0;
    }
    if (result & 0x1100) {
        arg0->unk10 = 0;
    }
    return result;
}

#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32 arg0, void *arg1);
extern s32 func_800AEF5C(void *arg0, s32 arg1);
extern void *func_800AEB9C(void *arg0);
extern void func_800AEEF0(void *arg0, void *arg1, s32 arg2, s32 arg3,
                         s32 arg4, s32 arg5, s32 arg6);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_8004B248(void *arg0);
extern void func_8004CAA0(void);
extern void func_800AE630(void);
extern void func_800AF0B4(void) __attribute__((noreturn));

extern s32 D_800814A0[3];

void *func_800AEFD8(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                    s32 arg4, s32 arg5)
{
    void *object;
    void *payload;

    object = func_8003FD64(0, arg0);
    if (object != 0) {
        payload = (u8 *)object + 0x20;
        if (func_800AEF5C(payload, 0x1A) != 0) {
            FIELD(object, void *, 0x0C) = (u8 *)object + 0xE8;
            FIELD(payload, void *, 0xD4) =
                func_800AEB9C(FIELD(payload, void *, 0xD8));
            func_800AEEF0(payload, arg0, arg3, arg4, arg1, arg2, arg5);
            func_8004491C(object, func_8004CAA0);
            FIELD(object, void *, 0x10) = func_800AE630;
            func_800AF0B4();
        } else {
            func_8004B248((u8 *)object + 0xFC);
            FIELD(object, u16, 0x1E) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            object = 0;
        }
    }
    return object;
}

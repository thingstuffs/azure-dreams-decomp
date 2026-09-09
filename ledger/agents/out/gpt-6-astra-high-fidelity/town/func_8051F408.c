#include "common.h"

extern s32 func_800162F8(void *, s32, s32);
extern void func_80017A8C(s16, s16, s16);
extern void func_80018A64(s32);
extern s32 func_80018B5C(s32);

extern u8 D_80019DBC[];
extern u8 D_8001CA40[];
extern u8 D_8001CD7B[];
extern u8 D_8001D244[];

u8 *func_80016C08(void *arg0, s32 arg1, s32 arg2) {
    void *pos;

    if (func_800162F8(arg0, arg1, arg2) != 0) {
        return D_8001D244;
    }

    pos = *(void **)((u8 *)arg0 + 0x14);
    func_80017A8C(*(s16 *)pos, *(s16 *)((u8 *)pos + 2), *(s16 *)((u8 *)pos + 4));

    if (func_80018B5C(0x5C1) == 0) {
        func_80018A64(0x5C1);
        return D_80019DBC;
    }

    pos = *(void **)((u8 *)arg0 + 0x14);
    if (func_80018B5C(*(s16 *)((u8 *)pos + 2)) == 0) {
        return D_8001CA40;
    }

    return D_8001CD7B;
}

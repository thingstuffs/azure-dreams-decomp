#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern void func_807007D0(void) __attribute__((noreturn));
extern s32 func_8070090C();

s32 func_808B2F58(s32 arg0)
{
    void *temp_v1;

    if ((func_8070021C(1) != 0) &&
        (*FIELD(*(void **)0xA0700F5C, s32 *, 8) > 0)) {
        func_807002A4(1);
        temp_v1 = *(void **)0xA0700F40;
        FIELD(temp_v1, u8, 0xE) = FIELD(temp_v1, u8, 0xE);
        func_8070090C();
        func_807007D0();
    }
    func_807002D4(1);
    return arg0;
}

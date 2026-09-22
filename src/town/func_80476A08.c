#include "common.h"

extern s32 func_80017620();
extern s32 func_8001796C();
extern void func_80018B24();
extern s32 func_800198D0();

extern s32 D_800170B4;
extern s32 D_80019BB0;
extern s32 D_80019BB4;
extern u8 *D_80019BBC;

/* Shop slot fill: take the next entry (or the default record) into slot arg1 and redraw. */
s32 func_80017A08(void *owner, s32 slot_index)
{
    s32 value;

    D_80019BB0 = 3;
    if (func_800198D0(0x1389) == 0) {
        return 1;
    }

    value = func_8001796C();
    if (value != 0) {
        *(s32 *)((u8 *)*(void **)((u8 *)owner + 0x10) + slot_index * 0x10 + 8) =
            func_80017620(value);
    } else {
        *(s32 *)((u8 *)*(void **)((u8 *)owner + 0x10) + slot_index * 0x10 + 8) =
            (s32)&D_800170B4;
    }

    D_80019BBC[5] = value;
    D_80019BB4 = value;
    func_80018B24(owner, slot_index);
    return 0;
}

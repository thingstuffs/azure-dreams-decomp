#include "common.h"


typedef void (*Callback)(s32, s32);

typedef struct S_8001686C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001686C_0;   /* D_80016000 in func_8001686C */


extern void func_80018B58();
extern void func_80018BD0();
extern s32 func_80018C50();
extern void *D_80016000;

s32 func_8001686C(void)
{
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);

    if (func_80018C50(0x679) != 0 &&
        func_80018C50(0x67A) == 0 &&
        func_80018C50(0xFAF) != 0) {
        func_80018B58(0x67D);
        return 1;
    }

    (*(Callback *)((u8 *)(((S_8001686C_0 *)D_80016000)->unk_20) + 0x2F8))(0x10, 0x200);
    return 0;
}

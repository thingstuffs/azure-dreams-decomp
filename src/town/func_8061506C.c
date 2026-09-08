#include "common.h"
#include "records/Rec_D_80016000.h"


typedef void (*Callback)(s32, s32);



extern void func_80018B58();
extern void func_80018BD0();
extern s32 func_80018C50();
extern void *D_80016000;

/* Updates event state and checks completion conditions, invoking a callback if unmet. */
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

    (*(Callback *)((u8 *)(((Rec_D_80016000 *)D_80016000)->unk_20) + 0x2F8))(0x10, 0x200);
    return 0;
}

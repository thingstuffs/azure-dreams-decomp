#include "common.h"

extern s32 func_80017E00(s32, s32);
extern void func_800181C8(void *, void *, s32, s32);
extern void func_80018B58(s32);
extern s32 func_80018C50(s32);

extern s8 D_80016000[];
extern s32 D_80018EAC;
extern s32 D_80018EC4;
extern s32 D_8001925C;

/* Update flag 0x681 when triggered and dispatch the corresponding record. */
void func_800166A4(s32 dispatch_context, s32 unused, s32 dispatch_arg)
{
    s8 *callback_table;

    if (func_80017E00(1, 8) != 0) {
        callback_table = *(s8 **)D_80016000;
        callback_table = *(s8 **)(callback_table + 0x20);
        (*(void (**)(s32))(callback_table + 0x78))(0);
        func_80018B58(0x681);
    } else {
        if (func_80018C50(0x681) == 0) {
            func_800181C8(&D_80018EAC, &D_8001925C, dispatch_context, dispatch_arg);
            return;
        }
    }

    func_800181C8(&D_80018EC4, &D_8001925C, dispatch_context, dispatch_arg);
}

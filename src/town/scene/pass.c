#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern s32 func_80017E00(s32, s32);
extern void func_800181C8(void *, void *, s32, s32);
extern void func_80018B58(s32);
extern s32 func_80018C50(s32);

extern s32 D_80018EAC;
extern s32 D_80018EC4;
extern s32 scene_request_context;

/* Update flag 0x681 when triggered and dispatch the corresponding record. */
void pass_2(s32 dispatch_context, s32 unused, s32 dispatch_arg)
{
    s8 *callback_table;

    if (func_80017E00(1, 8) != 0) {
        callback_table = *(s8 **)((s8 *)(&town_scene_root));
        callback_table = *(s8 **)(callback_table + 0x20);
        (*(void (**)(s32))(callback_table + 0x78))(0);
        func_80018B58(F_sbs16_pad07);
    } else {
        if (func_80018C50(F_sbs16_pad07) == 0) {
            func_800181C8(&D_80018EAC, &scene_request_context, dispatch_context, dispatch_arg);
            return;
        }
    }

    func_800181C8(&D_80018EC4, &scene_request_context, dispatch_context, dispatch_arg);
}

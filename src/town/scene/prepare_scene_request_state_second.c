#include "common.h"

extern s16 D_80018AEA;
extern s32 D_80018B00;
extern s32 D_80019A30;
extern s32 D_80019ACC;

extern void func_80017B3C(void *, s32);
extern s32 invoke_system_callback_21_c(void *, s32, s32);
extern void call_helper_with_fixed_id_0x118a(s32);
extern s32 func_8001894C(s32);

/* Prepare request state and select a result buffer based on status checks. */
void *prepare_scene_request_state(s32 request_id, s32 unused, s32 request_value)
{
    void *request_state = &D_80018B00;

    func_80017B3C(request_state, request_id);
    if (((func_8001894C(D_80018AEA) == 0) &&
         (invoke_system_callback_21_c(request_state, request_id, request_value) == 0)) ||
        (func_8001894C(0x50C) == 0)) {
        call_helper_with_fixed_id_0x118a(0x50C);
        return &D_80019ACC;
    }
    return &D_80019A30;
}

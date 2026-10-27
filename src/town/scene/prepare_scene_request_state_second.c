#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern s16 scene_request_flag_id;
extern s32 D_80018B00;
extern s32 D_80019A30;
extern s32 D_80019ACC;

extern void func_80017B3C(void *, void *, s32);
extern s32 func_80017F8C(void *entry_table, void *context, s32 entry_key); /* placed copy of resolve_entry_flag */
extern void func_80018854(s32); /* placed copy of set_script_flag_bit */

/* Prepare request state and select a result buffer based on status checks. */
void *prepare_scene_request_state(void *request_id, s32 unused, s32 request_value)
{
    void *request_state = &D_80018B00;

    func_80017B3C(request_state, request_id, request_value);
    if (((func_8001894C(scene_request_flag_id) == 0) &&
         (func_80017F8C(request_state, request_id, request_value) == 0)) ||
        (func_8001894C(F_sbs07_pad21) == 0)) {
        func_80018854(F_sbs07_pad21);
        return &D_80019ACC;
    }
    return &D_80019A30;
}

#include "common.h"

extern s32 func_800352FC(void *, void *, s32, s32);
extern void tcame_chase_fix(s32 *arg0);
extern s32 D_80113208[];
extern u8 D_800C321C[];

/* Set camera chase data and the object handler when the request succeeds. */
void func_800C5064(void *object, void *chase_data, s32 request_param, s32 check_param) {
    s32 *chase_fix;
    s32 second_value;

    if (func_800352FC(object, chase_data, request_param, check_param) != 0) {
        D_80113208[0] = ((s32 *)chase_data)[0];
        second_value = ((s32 *)chase_data)[1];
        chase_fix = D_80113208;
        chase_fix[2] = 0;
        chase_fix[1] = second_value;
        tcame_chase_fix(chase_fix);
        *(void **)((s8 *)object - 0x10) = D_800C321C;
    }
}

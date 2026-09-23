#include "common.h"

extern u8 *func_80019DFC();
extern s32 func_8001ADE0(s32);
extern s32 D_8001BB6C;
extern s32 D_8001C354;
extern u8 D_8001F8B5[];


/* Return the dispatch result, overriding it when the 0x1390 check succeeds. */
u8 *func_80017694(s32 dispatch_arg, s32 unused, s32 dispatch_option) {
    u8 *result;
    s32 first_arg = dispatch_arg;
    s32 fourth_arg = dispatch_option;


    result = func_80019DFC(&D_8001BB6C, &D_8001C354, first_arg, fourth_arg);
    if (func_8001ADE0(0x1390) != 0) {
        return D_8001F8B5;
    }
    return result;
}

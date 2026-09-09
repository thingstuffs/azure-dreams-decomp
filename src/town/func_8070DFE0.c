#include "common.h"

extern void *D_80016020[43];
extern void *D_8001B16C[];
extern char D_8001B14C[];
extern char D_8001B8CC[];
extern char D_8001B9E0[];
extern char D_800206CC[];
extern char D_8001C6D0[];

extern void *func_80016CE4(s32, s32);
extern void *func_80016D18(void);
extern void *func_80016E48(s32);
extern s32 func_8001A64C(s32);
extern void func_8001A554(s32);

/* Select event response data and set flags when using fallback responses. */
void *func_80016FE0(s32 handler_arg_a, s32 handler_arg_b, s32 selector)
{
    void *response;
    u32 case_index;
    static void *const case_labels[] = {
        &&case_19, &&case_18, &&case_52, &&case_12, &&case_default
    };

    case_index = selector - 12;
    if (case_index >= 43) {
        goto case_default;
    }
    goto *D_80016020[case_index];

case_19:
    response = func_80016CE4(handler_arg_a, handler_arg_b);
    D_8001B16C[0] = response;
    if (response != 0) {
        return response;
    }
    if (func_8001A64C(0x92C) == 0) {
        func_8001A554(0x92C);
        return D_8001B8CC;
    }
    return D_8001B9E0;

case_18:
    response = func_80016D18();
    D_8001B16C[0] = response;
    if (response != 0) {
        return response;
    }
    if (func_8001A64C(0xAC) == 0) {
        func_8001A554(0xAC);
    }
    func_8001A554(0x943);
    return D_800206CC;

case_52:
    {
        register s32 reward_selector ASM_REG("$6") = selector;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(reward_selector);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        return func_80016E48(reward_selector);
    }

case_12:
    return D_8001C6D0;

case_default:
    return D_8001B14C;
}

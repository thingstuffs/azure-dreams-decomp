#include "common.h"

extern s32 func_8001894C(s16);
extern void func_80018854(s16);
extern s32 func_80017C7C(s32, s32);
extern void func_80017BA0(void *, s32);

extern u8 D_8001AADC[16];
extern u8 D_8001ADE7[16];
extern u8 D_8001AE39[16];

/* Checks prerequisites, conditionally performs an action, and returns its response. */
void *func_80016698(void *object, s32 action_arg) {
    void *response;

    if (func_8001894C(*(s16 *)((u8 *)object + 0x18)) == 0) {
        func_80018854(*(s16 *)((u8 *)object + 0x18));
        return D_8001AADC;
    }
    if (func_80017C7C(13, 5) == 0) {
        response = D_8001ADE7;
        goto done;
    }
    func_80017BA0(object, action_arg);
    response = D_8001AE39;
done:
    return response;
}

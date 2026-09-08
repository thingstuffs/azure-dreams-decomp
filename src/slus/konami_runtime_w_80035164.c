#include "common.h"

#include "common.h"

extern void func_80034F88(void *arg0, s32 arg1);
extern s32 func_80034FD0(void *arg0);
extern void func_800350D4(void *arg0);
extern void func_80037D9C(void *arg0, s32 arg1);

/* Updates the runtime selector, clearing active objects when needed, and resets its state. */
void func_80035164(void *controller, s32 reset_value, s32 requested_selector)
{
    s32 selector;

    if (func_80034FD0(controller) != 0) {
        if (*(u8 *)controller != 0) {
            func_800350D4(controller);
            func_80037D9C(controller, (u8)requested_selector);
        } else {
            selector = requested_selector & 0xFF;
            if (*((u8 *)controller + 2) == selector) {
                goto finish;
            }
            func_800350D4(controller);
            func_80037D9C(controller, selector);
        }
    } else {
        func_80037D9C(controller, (u8)requested_selector);
    }
finish:
    func_80034F88(controller, reset_value);
}

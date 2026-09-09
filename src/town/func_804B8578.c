#include "common.h"

extern void func_80017BA0(s32, s32);
extern void func_80018854(s32 arg0);
extern s32 func_8001894C(s32 arg0);

extern u8 D_80019950[];
extern u8 D_80019A10[];

/* Select a data array based on flag 0x507, setting the flag on first use. */
void *func_80016D78(s32 first_input, s32 second_input) {
    void *result;

    func_80017BA0(first_input, second_input);
    if (func_8001894C(0x507) != 0) {
        goto nonzero;
    }
    func_80018854(0x507);
    result = D_80019950;
    goto done;

nonzero:
    result = D_80019A10;

done:
    return result;
}

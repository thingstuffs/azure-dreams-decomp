#include "common.h"

extern void func_80019BC0(void);
extern void func_8001ACE8(s32 arg0);
extern u8 D_8001DCD4[];
extern u8 D_8001DD86[];
extern u8 D_8001DDA1[];

/* Dispatch the selected action and return its associated data pointer. */
void *func_80017EE4(s32 unused_1, s32 unused_2, s32 action) {
#ifndef NON_MATCHING
    void *result;

    if (action == 1) {
        func_8001ACE8(0xD7A);
        result = D_8001DCD4;
        goto done;
    }
    if (action == 3) {
        goto action_three;
    }
    result = D_8001DD86;
    goto done;
action_three:
    func_80019BC0();
    result = D_8001DDA1;
done:
    return result;
#else
    if (action == 1) {
        func_8001ACE8(0xD7A);
        return D_8001DCD4;
    } else {
        if (action != 3) {
            return D_8001DD86;
        } else {
            func_80019BC0();
            return D_8001DDA1;
        }
    }
#endif
}

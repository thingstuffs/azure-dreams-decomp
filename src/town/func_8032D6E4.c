#include "common.h"

extern void func_80019BC0(void);
extern void func_8001ACE8(s32 bit_index);
extern u8 D_8001DCD4[];
extern u8 D_8001DD86[];
extern u8 D_8001DDA1[];

/* Dispatch the selected action and return its associated data pointer. */
void *func_80017EE4(s32 unused_1, s32 unused_2, s32 action) {
    void *result;

    if (action == 1) {
        func_8001ACE8(0xD7A);
        result = D_8001DCD4;
    } else if (action != 3) {
        result = D_8001DD86;
    } else {
        func_80019BC0();
        result = D_8001DDA1;
    }
    return result;
}

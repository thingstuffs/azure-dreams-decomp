#include "common.h"

extern s32 func_80021FF0(s32, s32, s32);
extern void func_80023004(void *);
extern void func_8002519C(s32);
extern void func_80020984(void);

extern s32 D_8002593C;
extern s32 D_800251A4;
extern s32 D_80024F7C;

/* Select a state pointer from the operation result and clear the trailing word. */
void func_80025230(s8 *state) {
    s32 *next_state;
    s32 result;
    s8 *owner;

    result = func_80021FF0(*(s32 *)(state + 0x28), 0x80010000, 1);
    owner = state - 0x20;
    if (result == 0) {
        next_state = &D_8002593C;
        *(s32 **)(state + 0x34) = next_state;
        func_80023004(owner);
#ifndef NON_MATCHING
        next_state = (s32 *)0x80020000;
        __asm__ __volatile__("" : "=r"(next_state) : "0"(next_state));
        next_state = (s32 *)((u8 *)next_state + 0x4F7C);
#else
        next_state = &D_80024F7C;
#endif
    } else {
        func_8002519C(0x80010000);
        next_state = &D_800251A4;
    }
    *(s32 **)(state - 0x10) = next_state;
    func_80020984();
    *(s32 *)(state + 0x40) = 0;
}

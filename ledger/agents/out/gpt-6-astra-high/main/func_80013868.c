#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *func_8003FC64(s32 a0);
extern s32 func_80026728(void *a0, s32 a1);
extern void func_8002223C(void);
extern void func_800220DC(void);
extern s32 func_8004F418(void *a0, s32 a1);
extern s32 func_80024D58(void *a0, s32 a1, s32 a2);
extern s32 func_80027364(void *a0);
extern s32 D_800267C0[];

/* Allocate an object and initialize its state and dispatch table. */
void *func_80026868(s32 init_value, s32 state_value)
{
    void *object;
    register void *state ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */

    object = func_8003FC64(0);
    state = (u8 *)object + 0x20;
    if (object != NULL) {
        *(s32 *)((u8 *)state + 0x24) = state_value;
        func_80026728(state, init_value);
        func_8002223C();
        func_800220DC();
        *(s32 *)((u8 *)object + 0x20) = func_8004F418(object, 0);
        *(s32 *)((u8 *)state + 4) = func_80024D58(object, *(s32 *)((u8 *)state + 0x2C), 3);
        *(s32 *)((u8 *)state + 8) = func_80027364(object);
        *(s32 *)((u8 *)state + 0x28) = 0;
        *(void **)((u8 *)object + 0x10) = D_800267C0;
    }
    return object;
}

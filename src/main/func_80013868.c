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

void *func_80026868(s32 arg0, s32 arg1)
{
    void *temp_v0;
    register void *temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8003FC64(0);
    temp_s0 = (u8 *)temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        *(s32 *)((u8 *)temp_s0 + 0x24) = arg1;
        func_80026728(temp_s0, arg0);
        func_8002223C();
        func_800220DC();
        *(s32 *)((u8 *)temp_v0 + 0x20) = func_8004F418(temp_v0, 0);
        *(s32 *)((u8 *)temp_s0 + 4) = func_80024D58(temp_v0, *(s32 *)((u8 *)temp_s0 + 0x2C), 3);
        *(s32 *)((u8 *)temp_s0 + 8) = func_80027364(temp_v0);
        *(s32 *)((u8 *)temp_s0 + 0x28) = 0;
        *(void **)((u8 *)temp_v0 + 0x10) = D_800267C0;
    }
    return temp_v0;
}

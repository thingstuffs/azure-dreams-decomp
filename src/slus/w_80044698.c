#include "common.h"

extern s32 func_80053EF0(s32 a0);
extern s16 func_80053DA8(s32 a0);
extern void func_80044618(s32 a0);
extern s32 VSync(s32 mode);

extern u16 D_80080B00;

/* Main frame-pump loop: polls pad/state via func_80053EF0(1); returns once it
 * reports 0. On the first nonzero poll, if the reported value isn't 3, fires
 * func_80053DA8(0xC1) once. Each iteration calls func_80044618(2), waits on
 * VSync(1), extracts a 9-bit field from the result, and stores it into
 * D_80080B00 whenever it changes. */
void func_80044698(void)
{
    s32 flag = 0;
    s32 v1;
    register s32 v0 ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    for (;;)
    {
        v1 = func_80053EF0(1);
        if (v1 == 0)
        {
            return;
        }

        v0 = flag;
        if (v0 == 0)
        {
            flag = 1;
            if (v1 != 3)
            {
                func_80053DA8(0xC1);
            }
        }

        func_80044618(2);

        v0 = (u32)VSync(1) >> 8;
        v0 = v0 & 0x1FF;
        if ((u32)v0 != D_80080B00)
        {
            D_80080B00 = (u16)v0;
        }
    }
}

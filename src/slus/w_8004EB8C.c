#include "common.h"

/* func_8003E4FC(kind, callback, arg) - registers a callback in some table */
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);
extern void func_8003E140(u8 *a0);
extern u8 D_80071644;

/* summary: resets *a0 and re-registers two callbacks (a "clear" reset for a0's slot,
   plus func_8003E140 as a fallback/default handler bound to a0). */
void func_8004EB8C(u8 *a0)
{
    *a0 = 0;
    func_8003E4FC(6, &D_80071644, 0);
    func_8003E4FC(0xFF, func_8003E140, a0);
}

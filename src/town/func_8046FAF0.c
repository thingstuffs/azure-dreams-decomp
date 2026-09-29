#include "shared/record_ptrs.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
extern M2C_UNK func_80018F74();
extern s32 func_800196F4();
extern s32 func_8001979C();
/* Invoke the callback for a match, or process a valid fallback lookup result. */
void func_80016AF0(void)
{
    s32 lookup_result;

    if (func_800196F4(0xD, 3) != 0) {
        (*((M2C_UNK (**)(M2C_UNK))
            (((s8 *) (*((void **) (((s8 *) D_80016000) + 0x20)))) + 0x78)))(0);
        return;
    }
    lookup_result = func_8001979C(0xD, 3);
    if (lookup_result != (-1)) {
        func_80018F74(lookup_result);
    }
}

#include "common.h"

extern void *D_80016000[];
extern s32 func_80018668(s32);
extern void func_80018570(s32);

s32 func_804802BC(void)
{
    if ((*(s32 (**)(s32))(*(void **)((u8 *)D_80016000[0] + 0x20) + 0x2D4))(0) == 0) {
        if (func_80018668(0xA6) == 0) {
            func_80018570(0xA6);
            return 1;
        }
    }
    return 0;
}

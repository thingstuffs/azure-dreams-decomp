#include "common.h"

typedef s32 (*Callback)(s32);

extern void *D_80016000[];
extern void func_80018570(s32);
extern s32 func_80018668(s32);

/* Triggers 0xA7 when the state callback returns one and 0xA7 is inactive. */
s32 func_80480318(void) {
    if ((*(Callback *)((u8 *)*(void **)((u8 *)D_80016000[0] + 0x20) + 0x2D4))(0) != 1) {
        return 0;
    }
    if (func_80018668(0xA7) != 0) {
        return 0;
    }
    func_80018570(0xA7);
    return 1;
}

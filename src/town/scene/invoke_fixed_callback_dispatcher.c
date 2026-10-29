#include "common.h"
#include "town/scene.h"

typedef void (*OsetCallback)(u8 *base, s32 bits, s32 count);

extern void func_8001770C(u8 *base, s32 bits, s32 count);
extern u8 D_80017850[];
extern s32 func_80016C58(OsetCallback callback, u8 *base, s32 bits, s32 count);

/* Invokes the callback dispatcher with the fixed data, bits, and count. */
void invoke_fixed_callback_dispatcher(s32 bits, s32 unused, s32 count)
{
    (void)unused;
    func_80016C58(func_8001770C, D_80017850, bits, count);
}

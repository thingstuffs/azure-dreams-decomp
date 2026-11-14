#include "common.h"
#include "town/scene.h"
#include "town/scene/motion.h"

typedef void (*OsetCallback)(u8 *base, s32 bits, s32 count);

extern void func_8001770C(u8 *base, s32 bits, s32 count);
extern u8 D_80017850[];

/* Invokes the callback dispatcher with the fixed data, bits, and count. */
void lookup_fixed_entry_position(s32 bits, s32 unused, s32 count)
{
    (void)unused;
    apply_entry_position(func_8001770C, D_80017850, bits, count);
}

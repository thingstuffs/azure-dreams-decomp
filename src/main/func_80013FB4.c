#include "common.h"

/* Sets bit 0x8000 in the object's flags and the global flags. */
void func_80026FB4(void *object) {
    u8 *object_bytes = object;
    s32 *global_base;
    u16 object_flags;
    s32 global_flags;

    global_base = (s32 *)0x80080000;
    asm volatile("" : "=r"(global_base) : "0"(global_base));
    object_flags = *(u16 *)(object_bytes + 0x1E);
    global_flags = global_base[0x528];
    object_flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)(object_bytes + 0x1E) = object_flags;
    global_base[0x528] = global_flags;
}

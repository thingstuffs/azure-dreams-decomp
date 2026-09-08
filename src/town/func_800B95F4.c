#include "common.h"

extern void func_800B6CCC(s16 a, s16 b, void *c, void *d);

/* Set the object data pointer and initialize its coordinate-based data. */
void func_800B6D54(void *object) {
    *(void **)((u8 *)object + 0xE0) = (void *)0x8002B800;
    func_800B6CCC(*(s16 *)((u8 *)object + 8), *(s16 *)((u8 *)object + 0xA),
                  (u8 *)object + 0xD8, (void *)0x8002B800);
}

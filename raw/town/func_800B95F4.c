#include "common.h"

extern void func_800B6CCC(s16 a, s16 b, void *c, void *d);

void func_800B6D54(void *arg0) {
    *(void **)((u8 *)arg0 + 0xE0) = (void *)0x8002B800;
    func_800B6CCC(*(s16 *)((u8 *)arg0 + 8), *(s16 *)((u8 *)arg0 + 0xA),
                  (u8 *)arg0 + 0xD8, (void *)0x8002B800);
}

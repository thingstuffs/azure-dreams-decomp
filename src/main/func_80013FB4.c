#include "common.h"

#include "shared/object_flags.h"
void func_80026FB4(void *object) {
    u16 of = *(u16 *)((char *)object + 0x1E);
    int gf = objectFlagBlock.flags;
    *(u16 *)((char *)object + 0x1E) = of | 0x8000;
    objectFlagBlock.flags = gf | 0x8000;
}

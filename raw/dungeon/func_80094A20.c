#include "common.h"

extern void func_8009A028(void *arg0);
extern void func_8009A204(void) __attribute__((noreturn));

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

s32 func_8009A180(void *arg0, void *arg1) {
    register u32 carrier ASM_REG("$4");
    register s32 result ASM_REG("$2");
    s32 flags;
    s32 link;
    void *node;
    u32 mask;

    if (arg0 == arg1) {
        result = 0;
        flags = FIELD(arg1, s32, 0x1C);
        ASM_KEEP(result);
        ASM_KEEP(flags);
        carrier = 0x80000000;
        ASM_KEEP(carrier);
        FIELD(arg1, s32, 0x1C) = flags | carrier;
        func_8009A204();
    }

    mask = 0x80000000;
    result = FIELD(arg0, s32, 0x1C);
    if (result >= 0) {
        ASM_KEEP(mask);
        result |= mask;
        ASM_KEEP(result);
        FIELD(arg0, s32, 0x1C) = result;
        carrier = (u32)arg0;
        func_8009A028((void *)carrier);

        link = FIELD(arg1, s32, 0x5C);
        FIELD(arg0, s32, 0x5C) = link;
        ASM_KEEP(link);
        node = (void *)(link + 0x20);
        ASM_KEEP(node);
        carrier = (u32)FIELD(node, void *, 0x58);
        ASM_KEEP(carrier);
        result = 1;
        ASM_KEEP(result);
        FIELD(arg0, void *, 0x58) = (void *)carrier;
        carrier = (u32)((u8 *)arg0 - 0x20);
        ASM_KEEP(carrier);
        FIELD(node, void *, 0x58) = (void *)carrier;
        FIELD(arg1, void *, 0x5C) = (void *)carrier;
        func_8009A204();
    }

    return 0;
}

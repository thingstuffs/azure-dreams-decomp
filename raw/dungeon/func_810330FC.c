#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800A41F0(void *);

void *func_801748FC(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register u8 *current ASM_REG("$16");
    register u8 *result ASM_REG("$17");
    register s32 coordinate ASM_REG("$18");
    register u8 *sentinel ASM_REG("$19");
    register s32 lower ASM_REG("$20");
    register s32 filter2 ASM_REG("$21");
    register s32 filter1 ASM_REG("$22");
    register s32 scratch ASM_REG("$2");
    u8 *object;
    s16 height;

    current = arg0;
    ASM_KEEP_NV(current);
    sentinel = current;
    ASM_KEEP_NV(sentinel);
    filter1 = arg1;
    ASM_KEEP_NV(filter1);
    scratch = FIELD(current, s32, 0x5C);
    ASM_KEEP_NV(current);
    current = (u8 *)scratch + 0x20;
    if (current != sentinel) {
        filter2 = arg2;
        scratch = arg3 << 0x10;
        coordinate = scratch >> 0x10;
        lower = coordinate - 0x20;
        do {
            object = FIELD(current, u8 *, -0x14);
            result = current - 0x20;
            if ((FIELD(object, u8, 0x24) == (filter1 & 0xFFFF)) &&
                (FIELD(object, u8, 0x25) == (filter2 & 0xFFFF)) &&
                (height = FIELD(current, s16, 0x88),
                 height <= coordinate + 0x20) &&
                (height >= lower) &&
                ((u32)(FIELD(current, u8, 0x13) - 0x33) >= 4U)) {
                scratch = func_800A41F0(current);
                scratch <<= 0x10;
                if (scratch != 0) {
                    return result;
                }
            }
            scratch = FIELD(current, s32, 0x5C);
            ASM_KEEP_NV(filter1);
            ASM_KEEP_NV(filter2);
            ASM_KEEP_NV(current);
            current = (u8 *)scratch + 0x20;
        } while (current != sentinel);
    }

    return 0;
}

/* MECHANISM: A current/sentinel copy split plus nonempty-arm filter and coordinate lifetimes
   reproduce the 0x30 frame, s0-s6 save set, and do/while CFG. A shared pinned v0 scratch
   preserves link-load/cast roles; destructive <<= keeps the call-result shift in v0. */

#include "common.h"

typedef struct { void *p; } PagePtr;
extern PagePtr D_80083160;
extern u8 D_801C9E40[16];

extern void func_80024094(void *, s32, void *, s32);
extern void func_80067E2C(void *, void *);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80024A5C(volatile s32 arg0, void *arg1, void *arg2, u16 arg3, s32 arg4)
{
    u16 pos[2];
    u16 flag;
    s32 y;
    s32 y2;
    u8 *packet;
    register u8 *pbase ASM_REG("$18");
    register s32 arg4p ASM_REG("$23");
    u32 hi_mask;
    u8 *work;
    u8 *ot;
    void *ctx;
    void *ctx2;
    register s32 shifted ASM_REG("$16");
    void *call_pos;
    s32 call_arg0;
    void *call_ot;
    s32 call_arg4;

    ctx = D_80083160.p;
    work = arg2;
    packet = FIELD(ctx, u8 *, 0x8D0);
    shifted = ctx != (void *)D_801C9E40;
    FIELD(ctx, u8 *, 0x8D0) = packet + 0xC;
    arg4p = arg4;
    flag = arg3;
    func_80067E2C(packet, D_80083160.p);
    hi_mask = 0xFF000000U;

    FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & hi_mask) |
                            (FIELD(ctx, u32, 0x8B0) & 0x00FFFFFFU);
    FIELD(ctx, u32, 0x8B0) = (FIELD(ctx, u32, 0x8B0) & hi_mask) |
                             ((u32)packet & 0x00FFFFFFU);

    pos[0] = FIELD(work, u16, 0);
    pbase = (u8 *)&D_80083160;
    y = FIELD(work, s16, 2);
    work = (u8 *)ctx + 0x8B0;
    ot = work;
    if (shifted != 0) {
        y -= 0xE0;
    }
    call_pos = pos;
    call_arg4 = (s32)((u32)arg4p << 16);
    call_ot = ot;
    ASM_KEEP_NV(call_pos);
    ASM_KEEP_NV(call_ot);
    call_arg0 = arg0;
    call_arg4 >>= 16;
    pos[1] = y;
    func_80024094(call_pos, call_arg0, call_ot, call_arg4);

    if (flag != 0) {
        u8 *packet2;

        ctx2 = D_80083160.p;
        packet2 = FIELD(ctx2, u8 *, 0x8D0);
        FIELD(ctx2, u8 *, 0x8D0) = packet2 + 0x10;
        FIELD(packet2, u32, 4) = 0x60000000;
        FIELD(packet2, s8, 3) = 3;
        FIELD(packet2, u16, 8) = FIELD(arg1, u16, 0);
        y2 = FIELD(arg1, s16, 2);
        if (shifted != 0) {
            y2 -= 0xE0;
        }
        FIELD(packet2, s16, 0xA) = y2;
        FIELD(packet2, s32, 0xC) = FIELD(arg1, s32, 4);
        FIELD(packet2, u32, 0) = (FIELD(packet2, u32, 0) & hi_mask) |
                                 (FIELD(ot, u32, 0) & 0x00FFFFFFU);
        FIELD(ot, u32, 0) = (FIELD(ot, u32, 0) & hi_mask) |
                            ((u32)packet2 & 0x00FFFFFFU);
    }

    ctx2 = FIELD(pbase, void *, 0);
    packet = FIELD(ctx2, u8 *, 0x8D0);
    FIELD(ctx2, u8 *, 0x8D0) = packet + 0xC;
    func_80067E2C(packet, arg1);
    FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & 0xFF000000U) |
                            (FIELD(ot, u32, 0) & 0x00FFFFFFU);
    FIELD(ot, u32, 0) = (FIELD(ot, u32, 0) & 0xFF000000U) |
                        ((u32)packet & 0x00FFFFFFU);
}

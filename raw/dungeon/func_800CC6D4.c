#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern u16 D_80083462;
extern EntityCallback D_800E21C0[];

extern void func_800478B8(void *arg0);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern void func_800D1F60();
extern void func_800D1FEC();
extern void func_800D2004();
extern void func_800D2084();
extern void func_800D20B8();

void func_800D1E34(void *arg0, void *arg1, void *arg2)
{
    register void *obj ASM_REG("$17") = arg0;
    register void *pos ASM_REG("$18") = arg1;
    register void *ent ASM_REG("$19") = arg2;
    register void *work ASM_REG("$16") = obj;
    EntityCallback callback;
    s16 floor;
    u16 flags;
    u16 globalFlags = D_80083462;

    if (globalFlags & 0x2000) {
        FIELD(work, u8, 0x71) &= 0x7F;
        func_800D20B8();
        return;
    }

    ASM_KEEP(obj);
    ASM_KEEP(pos);
    ASM_KEEP(ent);
    ASM_KEEP(work);

    callback = FIELD(work, EntityCallback, 0x8C);
    if (callback != 0) {
        callback(work, pos, ent, work);
    }
    D_800E21C0[FIELD(work, u8, 0x9A)](work, pos, ent, work);

    flags = FIELD(ent, u16, 0x14);
    if (!(flags & 0x8000)) {
        if (!(flags & 0x40)) {
            func_800478B8(ent);
        }
    }

    FIELD(pos, s32, 0) += FIELD(pos, s32, 0xC);
    FIELD(pos, s32, 4) += FIELD(pos, s32, 0x10);

    if (FIELD(obj, u16, 0x98) & 8) {
        FIELD(obj, u8, 0x9D) = 0;
        func_800D1F60();
        return;
    }

    FIELD(pos, s32, 0x14) += FIELD(obj, s8, 0x9D) * 0x14000;
    FIELD(obj, volatile u8, 0x9D)++;
    FIELD(obj, s32, 0x90) += FIELD(pos, s32, 0x14);

    if (!(FIELD(obj, volatile u16, 0x98) & 4)) {
        floor = func_800BCB04(FIELD(pos, u16, 2), FIELD(pos, u16, 6),
                              (s16)(FIELD(work, u16, 0x88) - 0x20));
        if (floor < 0x200) {
            if (FIELD(obj, s16, 0x92) + FIELD(work, s16, 0x88) < floor) {
                (void)FIELD(obj, volatile u16, 0x98);
                func_800D2004();
                return;
            }
            if (floor >= FIELD(work, s16, 0x88)) {
                FIELD(obj, s32, 0x90) = 0;
                func_800D1FEC();
                return;
            }

            FIELD(obj, s16, 0x92) = floor - FIELD(work, u16, 0x88);
            FIELD(pos, s32, 0x14) = 0;
            FIELD(work, u32, 0x1C) |= 0x08000000;
            FIELD(obj, u8, 0x9D) = 0;

            if (FIELD(work, u32, 0x1C) & 0x40000000) {
                FIELD(work, u32, 0x1C) &= ~0x40000000;
                floor = func_800BCB04(
                    (FIELD(ent, u8, 0x24) << 6) | 0x20,
                    (FIELD(ent, u8, 0x25) << 6) | 0x20,
                    (s16)(FIELD(work, u16, 0x88) - 0x20));
                FIELD(obj, u16, 0x92) += FIELD(work, u16, 0x88) - floor;
                FIELD(work, u16, 0x88) = floor;
                func_800D2084();
                return;
            }
            goto finish;
        }
    }

    FIELD(work, u32, 0x1C) &= ~0x08000000;

finish:
    FIELD(pos, u16, 0xA) = FIELD(work, u16, 0x88) + FIELD(obj, u16, 0x92);
    FIELD(ent, u16, 0x14) |= 0x40;
    FIELD(work, u32, 0x1C) |= 0x200;
}

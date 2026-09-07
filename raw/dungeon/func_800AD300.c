#include "common.h"

extern s32 func_80042900(void *, s32);
extern s8 func_8009FB34(u8, u8);
extern s32 func_800A03C4(void *, u8, u8);
extern s32 func_800A1C58(void *);
extern s32 func_800A2C34(s32);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_800ACB98();
extern void func_800B2C44(void);
extern void func_800B318C(void *, s32, void *, void *);
extern u16 D_80083460[];
extern u16 D_80083462;

void func_800B2A60(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3)
{
    register u8 *obj ASM_REG("$16") = arg0;
    register u8 *entity ASM_REG("$17");
    register s32 context ASM_REG("$19") = arg1;
    register u8 *pos ASM_REG("$18") = arg2;
    u16 *flags = D_80083460;
    register u8 *call_a0 ASM_REG("$4") = arg0;

    ASM_KEEP(obj);
    ASM_KEEP(pos);
    ASM_KEEP(context);

    if (!(flags[1] & 0x1000)) {
        entity = arg3;
        ASM_KEEP(entity);
        if (*(u8 *)(entity + 0x25) == 0) {
            ASM_KEEP(call_a0);
            *(s8 *)(obj + 0xAD) = 0;
            func_800ACB98(call_a0);
            func_800B2C44();
            return;
        }

        if ((func_80042900(entity, 1) << 16) == 0) {
            if (!(flags[1] & 0x2000)) {
                if (*(s32 *)(entity + 0x1C) & 0x100) {
                    func_800AA258(obj, context, pos, entity);
                    func_800B2C44();
                    return;
                }

                if (*(u8 *)(obj + 0x9A) != 0xE) {
                    *(u8 *)(obj + 0x9A) = 0xE;
                }
                *(u16 *)(obj + 0x98) &= 0xFFF3;

                if ((*(s16 *)(entity + 0x64) != 0) &&
                    (func_800AA6B4(obj, context, pos, 0) != 0)) {
                    return;
                }

                if (*(s32 *)(entity + 0x1C) & 0x80000) {
                    func_800AA888(obj, context, pos, entity);
                    func_800B318C(obj, context, pos, entity);
                    func_800B2C44();
                    return;
                }

                if ((func_800A1C58(entity) << 16) != 0) {
                    goto fail;
                }
            }

            *(s8 *)(pos + 0x26) = func_8009FB34(*(u8 *)(pos + 0x24),
                                                *(u8 *)(pos + 0x25));
            if (*(s8 *)(entity + 0x6D) <= 0) {
                goto done;
            }
            if (D_80083462 & 0x1000) {
                goto done;
            }
            if ((func_800A2C34(0) << 16) != 0) {
                goto done;
            }
            if (func_800A03C4(entity, *(u8 *)(pos + 0x24),
                              *(u8 *)(pos + 0x25)) == 0) {
                goto clear;
            }
        }

fail:
        *(s8 *)(obj + 0xAD) = 0;
        func_800ACB98(obj, context, pos, entity);
        func_800B2C44();
        return;

clear:
        *(s8 *)(entity + 0x6D) = 0;
    }

done:
    return;
}

/* MECHANISM: The pinned s3/context declaration precedes the pinned s2/pos
   declaration, making sched2 save and initialize s3/a1 before s2/a2.
   The held D_80083460 base and the seed's CFG preserve the exact 0x28 frame. */

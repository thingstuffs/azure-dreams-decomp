#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_8003DE58();
extern void func_80048A44();
extern void func_80091934();
extern void func_80092A08();
extern void func_80092AFC() __attribute__((noreturn));
extern void func_80092B98() __attribute__((noreturn));
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_8009929C();
extern s32 func_80099368();
extern s32 func_8009965C();
extern s32 func_80099734();
extern void func_80099F04();
extern void func_80099F70();
extern void func_800A5720();
extern void *func_800A8608(void *, void *, s32, s32, s32);

extern s16 D_80083228[12];
extern u8 D_80083460[12];
extern u8 D_8008ACDC[12];
extern u8 D_8008D470[12];
extern u8 D_800DD0B8[8];
extern u8 D_800E06EE[9];
extern u8 D_800E06F7[9];

void func_800927E4(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u16 pos[3];
    register void *obj ASM_REG("$3");
    void *prim;
    void *effect;
    void *entity;
    s32 text;
    s32 root;
    s32 state;
    u16 timer;
    register u8 *pageHi ASM_REG("$2");
    register s16 *page ASM_REG("$5");
    register s32 tailValue ASM_REG("$2");
    u8 *flagsBase;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        ASM_CLOBBER("$2");
        if (state == 0) {
            goto state_zero;
        }
        goto dflt;
    } else if (state == 2) {
        goto state_two;
    }
dflt:
    return;

state_zero:
        if (FIELD(arg0, u8, 0x9A) == 0x2C) {
            register void *callArg ASM_REG("$4") = arg2;
            register u8 *table ASM_REG("$5") = D_800DD0B8;
            register u8 *hitBase ASM_REG("$2");

            ASM_CLOBBER("$2");
            hitBase = (u8 *)0x80080000;
            ASM_KEEP(hitBase);
            FIELD(callArg, u8 *, 0x2C) = table;
            func_80048A44(
                callArg,
                table[((FIELD(hitBase, s16, 0x3228) +
                        FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0,
                1);
            tailValue = FIELD(arg0, u8, 0x9B) + 1;
            ASM_TAILSLOT_PIN_TIED(tailValue);
            func_80092AFC();
            return;
        }

        pageHi = (u8 *)0x80080000;
        ASM_KEEP(pageHi);
        page = (s16 *)(pageHi + 0x3160);
        ASM_KEEP(page);
        {
            register s32 pageCoord ASM_REG("$2") = FIELD(page, s16, 0xC8);
            register s32 coordSigned ASM_REG("$3") = FIELD(arg3, s16, 0x2A);
            register s32 coordUnsigned ASM_REG("$4");
            register s32 nextCoord ASM_REG("$2");

            ASM_MEM_BARRIER();
            coordUnsigned = FIELD(arg3, u16, 0x2A);
            if ((((pageCoord + coordSigned + 0x100) >> 9) & 7) == 2) {
            coordUnsigned = (s32)arg2;
            {
            register u8 *table ASM_REG("$3") = D_800DD0B8;

            FIELD((void *)coordUnsigned, u8 *, 0x2C) = table;
            func_80048A44(
                (void *)coordUnsigned,
                table[((FIELD(page, s16, 0xC8) +
                        FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0,
                1);
            tailValue = FIELD(arg0, u8, 0x9B) + 1;
            ASM_TAILSLOT_PIN_TIED(tailValue);
            func_80092AFC();
            return;
            }
            }

            nextCoord = coordUnsigned + 0x200;
            FIELD(arg3, u16, 0x2A) = nextCoord;
        }
        func_80092B98();
        return;

state_one:
        if (func_8003DE58(FIELD(arg2, s32, 8), arg2, pos, 0) == 0 &&
            !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }

        if (!(FIELD(arg3, s32, 0x1C) & 0x100000)) {
            register void *callA0 ASM_REG("$4") = (u8 *)arg0 - 0x20;
            register s32 zero ASM_REG("$6") = 0;
            ASM_KEEP_NV(callA0);
            ASM_KEEP_NV(zero);
            obj = func_800A8608(
                callA0, FIELD(arg0, void *, 0x110), zero, zero, 0);
            if (obj != 0) {
                register u8 *handler ASM_REG("$2") = (u8 *)0x80090000;

                ASM_KEEP(handler);
                handler -= 0x2B90;
                FIELD(obj, u8 *, 0x10) = handler;
                prim = FIELD(obj, void *, 8);
                FIELD(prim, u16, 2) = (FIELD(arg2, u8, 0x24) << 6) + 0x20;
                FIELD(prim, u16, 6) = (FIELD(arg2, u8, 0x25) << 6) + 0x20;

                if (FIELD(arg2, u16, 0x14) & 0x8000) {
                    effect = (u8 *)obj + 0x20;
                    ASM_KEEP(effect);
                    tailValue = FIELD(arg3, u16, 0x88) - 0x50;
                    ASM_TAILSLOT_PIN_TIED(tailValue);
                    func_80092A08(prim, effect);
                    return;
                }

                effect = (u8 *)obj + 0x20;
                ASM_KEEP(effect);
                FIELD(prim, u16, 2) += pos[0];
                FIELD(prim, u16, 6) += pos[1];
                FIELD(prim, s16, 0xA) = pos[2] + FIELD(arg3, u16, 0x88);
                FIELD(effect, s16, 0xA8) = 0x1E;
                FIELD(effect, s16, 0xAA) = 2;
                FIELD(effect, void *, 0x90) = arg2;
                FIELD(effect, s32, 0x8C) = arg1;
                FIELD(effect, void *, 0x9C) = (u8 *)arg0 + 0x108;

                entity = FIELD(arg0, void *, 0x110);
                if (entity != 0 && FIELD(entity, u8, 1) == 4 &&
                    FIELD(entity, s8, 2) != 0) {
                    FIELD(effect, s16, 0xAE) = 1;
                    FIELD(effect, s16, 0xA8) = 0x3C;
                }
            }

            root = func_800990FC();
            state = func_80099734(arg3, func_8009929C(8, root));
            state = func_80099194(D_800E06EE, state);
            state = func_80099368(FIELD(arg0, void *, 0x110), state);
            text = func_80099194(D_800E06F7, state);
            entity = FIELD(arg0, void *, 0x110);
            if (FIELD(entity, u8, 1) != 4) {
                text = func_8009965C(entity, text);
            }
            func_80099290(text);
            func_800A5720(root);
        }

        FIELD(arg0, u16, 0x96) = 0x1E;
        FIELD(arg0, u8, 0x9B)++;
        func_80092B98();
        return;

state_two:
        if ((FIELD(arg2, u16, 0x14) & 0x8000) ||
            (timer = FIELD(arg0, u16, 0x96) - 1,
             FIELD(arg0, u16, 0x96) = timer,
             (s32)(timer << 16) <= 0)) {
            if (FIELD(arg0, void *, 0x110) != 0) {
                func_80091934(arg0, arg1, arg2, arg3);
                func_80092B98();
                return;
            }
            func_80099F70(FIELD(arg3, s32, 0x5C));
            func_80099F04(FIELD(arg3, s32, 0x5C));
            flagsBase = D_80083460;
            ASM_KEEP(flagsBase);
            FIELD(flagsBase, u16, 2) |= 0x812;
            FIELD(arg0, u8 *, 0x8C) = D_8008ACDC;
        }
        return;
}

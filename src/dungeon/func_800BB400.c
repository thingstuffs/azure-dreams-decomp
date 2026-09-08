#include "common.h"

/* Aliased dungeon-engine row: true link base is 0x800C0B60 (all four external
 * j targets resolve to this function's own local joins there:
 *   0x800C0E68 -> local epilogue (return path)
 *   0x800C0CBC -> case join (sw flags; jal func_800D4FC8 continuation)
 *   0x800C0D9C -> loop join (sb slot; loop tail)
 *   0x800C0E2C -> message-chain merge (addiu %lo(D_80089380); ...)
 * At the synthetic base 0x800BB400 these are only reachable as sibcall tails;
 * all four callees are in config/sibcall_syms.dungeon.txt. */

extern void func_8008D330();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800A5F38();
extern void func_800D4FC8();
extern void func_80042984();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern s32 func_80099734();
extern void func_80099290();
extern void func_800A5720();
extern void func_80098B38();

/* shared-epilogue tail: NOT noreturn so SHAPE-C relocates the return value
 * materialization into the converted j delay slot. */
/* pin-arm joins: zero-arg noreturn (LEAD-18 side-channel jal->j). */
extern void func_800C0CBC(void) __attribute__((noreturn));
extern void func_800C0D9C(void) __attribute__((noreturn));
extern void func_800C0E2C(void) __attribute__((noreturn));

extern u8 *D_800E3D7C[];
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_8006DE24[];
extern u8 D_800E13FB[];
extern u8 D_800E1402[];
extern u8 D_800E1411[];
extern u8 D_800E1426[];
extern u8 D_80089380[];
extern u8 D_80083460[];

s32 func_800C0B60(u8 *arg0, u8 *arg1, s32 value)
{
    u8 *a0keep = arg0;
    register u8 *entity ASM_REG("$17") = a0keep;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *event = arg1;
    s32 saved;
    u8 *message;
    s32 t;
    s32 r;
    register s32 i ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *slot;

    if (entity == D_800E3D7C[0]) {
        *(u8 **)(entity + 0x110) = event;
        ASM_KEEP_NV(a0keep);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        func_8008D330(a0keep, D_80083780, D_80082E80, a0keep);
        return 0;
    }
    ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    if ((u32)entity <= 0x9FFFFFFF) {
        do { } while (0);
        func_800A63B8(entity, event, (s16)value);
        if (func_800AD6FC(entity, (D_800DDE84[entity[0x13]] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
        *(s32 *)(entity + 0x14) &= -8;
        *(s32 *)(entity + 0x1C) &= -8;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        {
        s32 ev0;
        ev0 = event[0];
        if (ev0 == 5) {
            {
                u8 *page;
                page = (u8 *)0x800E0000;
                ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                message = page + 0x13FB;
            }
            {
                u8 *pa0;
                s32 pa1;
                s32 pa2;
                s32 pv0;
                s32 pv1;
                pa0 = entity - 32;
                pa1 = 0xF0;
                pa2 = 0x81C;
                pv0 = *(s32 *)(entity + 0x14) | 1;
                pv1 = *(s32 *)(entity + 0x1C) | 1;
                ASM_USE(message);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pa0);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pa1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pa2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pv0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                ASM_TAILSLOT_PIN(pv1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                func_800C0CBC();
            }
        } else if (ev0 == 6) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            {
                u8 *page;
                page = (u8 *)0x800E0000;
                ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                message = page + 0x1402;
            }
            {
                u8 *pa0;
                s32 pa1;
                s32 pa2;
                s32 pv0;
                s32 pv1;
                pa0 = entity - 32;
                pa1 = 0xF00000;
                pa2 = 0x81C;
                pv0 = *(s32 *)(entity + 0x14) | 2;
                pv1 = *(s32 *)(entity + 0x1C) | 2;
                ASM_USE(message);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pa0);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pa1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pa2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(pv0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                ASM_TAILSLOT_PIN(pv1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                func_800C0CBC();
            }
        } else {
            {
                u8 *page;
                page = (u8 *)0x800E0000;
                ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                message = page + 0x140A;
            }
            *(s32 *)(entity + 0x14) |= 4;
            *(s32 *)(entity + 0x1C) |= 4;
            func_800D4FC8(entity - 32, 0xF000, 0x81C);
        }
        }
        func_80042984(entity);

        slot = entity + 8;
        for (i = 0; i < 3; i++, slot += 3) {
            if (slot[0] != 0) {
                s32 item = slot[0];
                s32 flags = *(s32 *)(entity + 0x14);

                if (((D_8006DE24[item * 20 + 16] & 7) & flags) == 0) {
                    if (flags & 1) {
                        s32 pv1;
                        pv1 = ((item - 1) / 3) * 3 + 1;
                        ASM_TAILSLOT_PIN(pv1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                        func_800C0D9C();
                    } else {
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                        if (flags & 2) {
                            s32 pv1;
                            pv1 = ((item - 1) / 3) * 3 + 2;
                            ASM_TAILSLOT_PIN(pv1);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                            func_800C0D9C();
                        } else {
                            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                            if (flags & 4) {
                                slot[0] = ((item - 1) / 3) * 3 + 3;
                            }
                        }
                    }
                }
            }
        }

        if (*(s32 *)(entity + 0x14) & 0x4000) {
            t = func_800990FC();
            {
                register u8 *pa0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                register s32 ta ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                pa0 = entity;
                ta = t;
                saved = ta;
                r = func_80099734(pa0, ta);
            }
            r = func_80099194(D_800E1411, r);
            r = func_80099194(message, r);
            ASM_USE(saved);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            {
                register u32 page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                page = 0x80090000;
                ASM_PAGEBASE_PIN(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                func_800C0E2C();
            }
        }
    } else {
        t = func_800990FC();
        {
            u8 *pa0;
            register s32 ta ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            pa0 = D_800E1426;
            ASM_KEEP(pa0);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            ta = t;
            saved = ta;
            r = func_80099194(pa0, ta);
        }
        r = func_80099734(entity, r);
        r = func_80099194(D_80089380, r);
        func_80099290(r);
        func_800A5720(saved);
    }

    func_80098B38(event);
    {
        u8 *counter;
        counter = D_80083460;
        *(u16 *)(counter + 0xA) -= 1;
    }
    return 1;
}

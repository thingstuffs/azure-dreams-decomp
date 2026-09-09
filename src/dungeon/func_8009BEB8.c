#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern void func_80048224(s16, s32, s32, s32);
extern u8 D_800E3DA0[];
extern u8 D_800E3DB0[];
extern u8 D_800E3DE0[];
u8 *func_800A1618(s32 arg0, s32 arg1) {
    u8 *r_v0;
    register u8 *r_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *r_a0;
    s32 var_a1;
    s32 var_a3;
    register s32 in_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_t0;
    register s32 var_t1 ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_a2;
    u8 *var_a0;
    u8 *var_s0;
    u8 *var_v1;
    var_t0 = arg0;
    var_s0 = 0;
    var_t1 = arg1;
    ASM_KEEP_NV(arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_a1 = arg1;
    in_a0 = arg0;
    ASM_KEEP_NV(in_a0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    in_a0 = (s16)in_a0;
    if (in_a0 == 0x38) {
        r_v1 = D_800E3DB0;
        r_v0 = r_v1 + 0x10;
        r_a0 = (u8 *)0x800E0000;
        ASM_KEEP4(r_v0, r_v1, r_a0, var_t1);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        r_v1[0x11] = 0;
        r_v1 = r_a0 + 0x3DA0;
        ASM_KEEP(r_v1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        r_v1[2] = 0;
        goto clear_flags;
    }
    var_a3 = 0x31;
    if (in_a0 == 0x31) {
        r_v1 = D_800E3DB0;
        r_v0 = r_v1 + 8;
        r_a0 = (u8 *)0x800E0000;
        ASM_KEEP4(r_v0, r_v1, r_a0, var_t1);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        r_v1[9] = 0;
        r_v1 = r_a0 + 0x3DA0;
        ASM_KEEP(r_v1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
clear_flags:
        r_v1[1] = 0;
        r_a0[0x3DA0] = 0;
        return r_v0;
    }
    if (in_a0 == 0x39) var_t0 = 2;
    if ((s16)var_a1 == 3) {
        u8 *r_v0;
        register u8 *r_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        r_v0 = (u8 *)0x800E0000;
        ASM_KEEP(r_v0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        r_v1 = r_v0 + 0x3DD0;
        ASM_KEEP_DEP_NV(r_v1, r_v0); /* MATCH: keep the address base in v0 and merged scan pointer in v1. */
        var_v1 = r_v1;
        var_a2 = 4;
        goto scan;
    }
    if ((s16)var_a1 == 2) {
        u8 *r_v0;
        r_v0 = D_800E3DE0;
        return r_v0;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    var_v1 = D_800E3DB0;
    if (var_v1[0x11] == 0x38) {
        register s32 r_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        r_a2 = 3;
        ASM_KEEP(r_a2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        var_v1 += 0x18;
        var_a2 = r_a2;
        goto scan;
    }
    ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    var_a2 = 0;
    if (var_v1[9] == 0x31) {
        var_v1 += 0x10;
        var_a2 = 2;
        goto scan;
    }
    ASM_KEEP(var_a2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
scan:
    if (var_a2 < 6) {
        s32 r_t4;
        s32 r_t3;
        s32 r_t2;
        s8 *data;
        var_a1 = (s16)var_t1;
        r_t4 = 1;
        r_t3 = 3;
        ASM_USE(var_t1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        var_a3 = (s16)var_t0;
        r_t2 = 2;
        data = (s8 *)D_800E3DA0;
        var_a0 = var_v1 + 1;
        do {
        if (((var_a1 != r_t4) && (var_a1 != r_t3)) || (*var_v1 == var_a1)) {
            if ((*var_a0 == 0) || (*var_a0 == var_a3)) {
                if (var_a1 == r_t2) {
                    register u8 *r_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    D_800E3DA0[6] = 0;
                    r_v0 = var_v1;
                    return r_v0;
                }
                var_s0 = var_v1;
                if ((*var_a0 == var_a3) || (*(s8 *)((unsigned long)var_a2 + (unsigned long)data) == var_a3)) break;
            }
        } else break;
            var_a2++; var_a0 += 8; var_v1 += 8;
        } while (var_a2 < 6);
    }
    if (var_s0) func_80048224((s16)var_t0, var_a1, var_a2, var_a3);
    return var_s0;
}

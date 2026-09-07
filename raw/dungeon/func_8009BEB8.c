#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern void func_80048224(s16, s32, s32, s32);
extern u8 *func_800A1684(u8 *, s32, s32);
extern u8 *func_800A1714();
extern u8 *func_800A17D4();
extern u8 D_800E3DA0[];
extern u8 D_800E3DB0[];
extern u8 D_800E3DE0[];
u8 *func_800A1618(s32 arg0, s32 arg1) {
    s32 var_a1;
    s32 var_a3;
    register s32 in_a0 ASM_REG("$4");
    register s32 var_t0 ASM_REG("$8");
    register s32 var_t1 ASM_REG("$9");
    s32 var_a2;
    u8 *var_a0;
    u8 *var_s0;
    u8 *var_v1;
    var_t0 = arg0;
    ASM_USE_NV(var_t0);
    var_s0 = 0;
    var_t1 = arg1;
    ASM_KEEP_NV(arg1);
    var_a1 = arg1;
    in_a0 = arg0;
    ASM_KEEP_NV(in_a0);
    in_a0 = (s16)in_a0;
    if (in_a0 == 0x38) {
        register u8 *r_v0 ASM_REG("$2");
        register u8 *r_v1 ASM_REG("$3");
        register u8 *r_a0 ASM_REG("$4");
        r_v1 = D_800E3DB0;
        r_v0 = r_v1 + 0x10;
        r_a0 = (u8 *)0x800E0000;
        ASM_KEEP4(r_v0, r_v1, r_a0, var_t1);
        r_v1[0x11] = 0;
        r_v1 = r_a0 + 0x3DA0;
        ASM_KEEP(r_v1);
        r_v1[2] = 0;
        return func_800A1684(r_a0, arg1, 0x38);
    }
    var_a3 = 0x31;
    if (in_a0 == 0x31) {
        register u8 *r_v0 ASM_REG("$2");
        register u8 *r_v1 ASM_REG("$3");
        register u8 *r_a0 ASM_REG("$4");
        r_v1 = D_800E3DB0;
        r_v0 = r_v1 + 8;
        r_a0 = (u8 *)0x800E0000;
        ASM_KEEP4(r_v0, r_v1, r_a0, var_t1);
        r_v1[9] = 0;
        r_v1 = r_a0 + 0x3DA0;
        ASM_KEEP(r_v1);
        r_v1[1] = 0;
        r_a0[0x3DA0] = 0;
        return func_800A17D4();
    }
    if (in_a0 == 0x39) var_t0 = 2;
    if ((s16)var_a1 == 3) {
        register u8 *r_v0 ASM_REG("$2");
        register u8 *r_v1 ASM_REG("$3");
        r_v0 = (u8 *)0x800E0000;
        ASM_KEEP(r_v0);
        r_v1 = r_v0 + 0x3DD0;
        ASM_KEEP4(r_v0, r_v1, in_a0, arg1);
        return func_800A1714(in_a0, arg1, 4);
    }
    if ((s16)var_a1 == 2) {
        register u8 *r_v0 ASM_REG("$2");
        r_v0 = D_800E3DE0;
        ASM_TAILSLOT_PIN(r_v0);
        return func_800A17D4();
    }
    ASM_SCHED_BARRIER();
    var_v1 = D_800E3DB0;
    if (var_v1[0x11] == 0x38) {
        register s32 r_a2 ASM_REG("$6");
        r_a2 = 3;
        ASM_KEEP(r_a2);
        var_v1 += 0x18;
        ASM_TAILSLOT_PIN(var_v1);
        return func_800A1714();
    }
    ASM_KEEP(var_s0);
    var_a2 = 0;
    if (var_v1[9] == 0x31) {
        var_v1 += 0x10;
        ASM_TAILSLOT_PIN(var_v1);
        return func_800A1714(in_a0, arg1, 2);
    }
    ASM_KEEP(var_a2);
    if (var_a2 < 6) {
        register s32 r_t4 ASM_REG("$12");
        register s32 r_t3 ASM_REG("$11");
        register s32 r_t2 ASM_REG("$10");
        s8 *data;
        var_a1 = (s16)var_t1;
        r_t4 = 1;
        r_t3 = 3;
        ASM_USE(var_t1);
        ASM_USE2(r_t4, r_t3);
        var_a3 = (s16)var_t0;
        r_t2 = 2;
        data = (s8 *)D_800E3DA0;
        ASM_USE(data);
        ASM_KEEP(r_t4);
        var_a0 = D_800E3DB0 + 1;
        do {
        if (((var_a1 != r_t4) && (var_a1 != r_t3)) || (*var_v1 == var_a1)) {
            if ((*var_a0 == 0) || (*var_a0 == var_a3)) {
                if (var_a1 == r_t2) {
                    register u8 *r_v0 ASM_REG("$2");
                    D_800E3DA0[6] = 0;
                    r_v0 = var_v1;
                    ASM_TAILSLOT_PIN(r_v0);
                    return func_800A17D4();
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

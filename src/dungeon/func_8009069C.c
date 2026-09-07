#include "common.h"

typedef struct {
    u8 pad0[0x9B];
    u8 state;
    u8 pad9C[0x100 - 0x9C];
    s16 h100;
} Actor;

typedef struct {
    u8 pad0[2];
    u16 f2;
    u8 pad4[8];
    u32 fC;
    u8 pad10[4];
    u16 f14;
} StructA;

extern StructA D_80083460;
extern u8 D_800E3648[];
extern u8 D_800E0B39[];
extern u8 D_80088B14[];
extern u8 D_800E0B4C[];

extern s32 func_800A2B5C(s32);
extern void func_80096088(Actor *, s32);
extern void func_80096058(void);
extern s32 func_800990FC(s32, s32, s32, s32);
extern s32 func_80099194(void *, s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099978(s32);
extern s32 func_80099368(void *, s32);
extern void func_800998C0(s32, s32);
extern s32 func_800999B0(s32);
extern void func_80099290(s32);
extern void func_800A5720(s32);
extern void func_800954E0(Actor *, s32, s32, s32);
extern s16 func_800B627C(s32, s32, s16, s32);

void func_80095DFC(Actor *a0, s32 a1, s32 a2, s32 arg3) {
    register u8 *entry ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    int st = a0->state;
    s32 a3 = arg3;
    if (st != 1) {
        if (st >= 2) {
            return;
        }
        if (st != 0) {
            return;
        }
        if (D_80083460.f2 & 0x1000) {
            return;
        }
        if ((s16) func_800A2B5C(a3) != 0) {
            return;
        }
        entry = &D_800E3648[a0->h100 * 4];
        if (entry[0] == 0) {
            func_80096088(a0, a3);
            D_80083460.fC = 0;
            D_80083460.f14--;
            D_80083460.f2 &= 0xFFF7;
            func_80096058();
            return;
        }
        if (!(entry[3] & 0x40)) {
            /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22):
             * retail's `jal 0x800990FC` at 0x80095EDC has a nop delay slot and
             * zero argument setup -- it forwards $a3 through (section 22 pins
             * are the missing name), and `need` is a positional SET so the call
             * carries positions 0..3 (section 21).
             * A BARE $4 pin does not work here: with no def, $4 is live from
             * function entry, which forbids hoisting `move a0,s3` into the
             * delay slot of the `bnez` 17 insns earlier -- one indel, 129 words
             * off (the known signature from the earlier shape of this row).
             * ASM_SET gives fa0 a zero-byte def inside this block, ending that
             * live range after the branch; the delay-slot fill comes back and
             * the row is byte-exact. */
            s32 fa0;
            register s32 fa1 ASM_REG("$5");   /* MATCH pin: retail delay-slot contents depend on it */
            register s32 fa2 ASM_REG("$6");   /* MATCH pin: retail delay-slot contents depend on it */
            register s32 fa3 ASM_REG("$7");   /* MATCH pin: retail delay-slot contents depend on it */
            s32 t;
            s32 h;
            s32 s0;
            s32 t2;
            ASM_SET(fa0);   /* MATCH pin: retail delay-slot contents depend on it */
            t = func_800990FC(fa0, fa1, fa2, fa3);
            h = t;
            t = func_80099978(func_80099194(D_800E0B39, func_8009929C(8, t)));
            s0 = t - 2;
            t = func_80099194(D_80088B14, t);
            t2 = t;
            t = func_80099368(&D_800E3648[a0->h100 * 4], t2);
            func_800998C0(s0, t2);
            func_80099290(func_800999B0(func_80099194(D_800E0B4C, func_8009929C(10, t))));
            func_800A5720(h);
        }
        a0->state++;
        func_800954E0(a0, a1, a2, a3);
    }
    if (D_800E3648[a0->h100 * 4] == 0) {
        func_80096088(a0, a3);
        D_80083460.fC = 0;
        D_80083460.f14--;
        D_80083460.f2 &= 0xFFF7;
        func_80096058();
        return;
    } else {
        s16 r = (s16) func_800B627C(D_800E3648[a0->h100 * 4], a3, a0->h100, 0);
        if (r != 0) {
            D_80083460.fC = 0;
            D_80083460.f14--;
            D_80083460.f2 &= 0xFFF7;
            if (r > 0) {
                func_80096088(a0, a3);
            }
            a0->state++;
        }
    }
}

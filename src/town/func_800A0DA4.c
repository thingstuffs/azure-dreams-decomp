#include "common.h"

extern u8 D_8009DEBC[];
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];
extern u8 D_800D0788[];
extern u8 D_80010000[];
extern u8 T_80010000[];
__asm__(".set D_80010000, 0x80010000");
__asm__(".set T_80010000, 0x80010000");

extern s32 func_8004A658();
extern void func_8008F0D4();
extern void func_8008F104();
extern void func_8009B218();
extern void func_8009DC8C();
extern void func_8009E588();
extern void func_8009E634();
extern void func_8009E654();
extern void func_8009E6F4();
extern void func_8009E6F8();
extern void func_8009F148();
extern s32 func_8009FF50();

#define BU(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define WD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define PP(p, off) (*(u8 **)((u8 *)(p) + (off)))
#define TB(idx, off) (D_80010000[(idx) * 4 + (off)])

void func_8009E504(void *arg0, s32 arg1, void *arg2)
{
    register u32 result ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    u8 t0;
    u8 t1;

    t0 = BU(arg0, 0x94);
    if (t0 == 0) {
        func_8008F0D4(arg0, arg1, D_800D073C);
        func_8009E588(arg0, arg1, arg2, D_800D076C);
        return;
    }
    if ((s8)t0 == -1) {
        register void *call_a0 ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register s32 call_a1 ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register void *call_a2 ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 call_a3;

        func_8008F104(arg0, arg1, D_800D073C);
        call_a0 = arg0;
        call_a1 = arg1;
        call_a2 = arg2;
        call_a3 = 0;
        ASM_KEEP(call_a3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8009B218(call_a0, call_a1, call_a2, call_a3);
        BU(arg0, 0x4C) = BU(arg0, 0x95);
        BU(arg0, 0x4D) = BU(arg0, 0x96);
        func_8009E634();
        return;
    }

    func_8008F0D4(arg0, arg1, D_800D073C);
    func_8009B218(arg0, arg1, arg2, D_800D0788);
    {
        register u8 *table ASM_REG("$7");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

        table = (u8 *)0x80010000;
        BU(arg0, 0x4C) = table[BU(arg0, 0x95) * 4 + 0x980];
        BU(arg0, 0x4D) = table[BU(arg0, 0x95) * 4 + 0x981];
        BU(arg0, 0x4E) = table[BU(arg0, 0x95) * 4 + 0x982];
        BU(arg0, 0x4F) = table[BU(arg0, 0x95) * 4 + 0x983];
    }
    func_8009F148(arg0, arg0, arg1, arg2);

    if (func_8009FF50() == 0) {
        result = 0x800A0000;
        ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8009E654();
        result -= 0x22C0;
        goto keep_return;
    }

    result = (u32)D_8009DEBC;
    PP(arg0, -0x10) = (u8 *)result;
    ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
    if ((u32)(BU(arg0, 0x4D) - 0x12) < 2U) {
        PP(arg0, 0xC) = D_800D0754;
    }

    t1 = BU(arg0, 0x4D);
    if (t1 == 0x12) {
        result = 0x80070000;
        ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8009E6F4();
        result -= 0x1DC0;
        goto keep_return;
    }
    if (t1 == 0x13) {
        u8 *base = (u8 *)0x80010000;

        func_8009DC8C(
            arg0,
            arg2,
            BU(arg0, 0x4C),
            *(s32 *)&base[
                ((base[BU(arg0, 0x95) * 4 + 0x983] & 0x3F) * 0x54)
                    + 0xA94]);
        func_8009E6F8();
        return;
    }

    result = func_8004A658(BU(arg0, 0x4D), BU(arg0, 0x4C));
    WD(arg2, 8) = result;

keep_return:
    ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
}

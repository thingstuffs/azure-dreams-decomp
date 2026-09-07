#include "common.h"

#include "common.h"

#ifdef NON_MATCHING
#define ASM_KEEP_OLD(var) ((void)0)
#else
#define ASM_KEEP_OLD(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

extern void DrawSync(s32);
extern void func_8003E4FC(s32, void *, void *);
extern void func_8003F320(void);
extern void func_80041344(void *, s32);
extern void func_80046E38(u8, void *);
extern void func_8003E140(void);

extern u8 D_800136B8[];
extern u8 D_80080BB4[16];
extern u8 D_80080BBC[16];
extern u8 D_80080BC4[16];
extern u8 D_80080BCC[16];
extern u8 D_80080BD4[16];
extern u8 D_80080BDC[16];
extern u8 D_80080BE4[16];
extern u8 D_80080BEC[16];
extern u8 D_80080BF4[16];
extern u8 D_80080BFC[16];
extern u8 D_80080C04[16];
extern u8 D_80080C0C[16];
extern u8 D_80080C14[16];
extern s32 D_80081480_0[3];
extern s32 D_80081480_1[3];
extern s32 D_80081480_2[3];
extern s32 D_80081480_3[3];
extern s32 D_80081480_4[3];
__asm__(".set D_80081480_0, 0x80081480\n.set D_80081480_1, 0x80081480\n.set D_80081480_2, 0x80081480\n.set D_80081480_3, 0x80081480\n.set D_80081480_4, 0x80081480");
extern u8 D_800D2FB4[32];
extern u8 D_800D381A[];
extern u8 D_8012F004[16];

void func_80051228(void)
{
    u8 sp10;
    u8 *var_a1;
    register s32 arg0 ASM_REG("$4");
    void *fp = func_8003E140;

    sp10 = 0;
    func_8003E4FC(6, D_80080BB4, 0);
    func_8003E4FC(0xFF, fp, &sp10);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480_0[0]);
    DrawSync(0);
    sp10 = 0;
    func_8003E4FC(6, D_80080BBC, 0);
    func_8003E4FC(0xFF, fp, &sp10);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480_1[0]);
    DrawSync(0);
    sp10 = 0;
    func_8003E4FC(6, D_80080BC4, 0);
    func_8003E4FC(0xFF, fp, &sp10);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480_2[0]);
    DrawSync(0);
    sp10 = 0;
    func_8003E4FC(6, D_80080BCC, 0);
    func_8003E4FC(0xFF, fp, &sp10);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480_3[0]);
    DrawSync(0);
    sp10 = 0;

    switch (D_800D381A[0]) {
    case 0:
    case 1:
    default:
        switch (D_800136B8[0]) {
        default: arg0 = 6; ASM_KEEP_OLD(arg0); var_a1 = D_80080BD4; break;
        case 11: arg0 = 6; var_a1 = D_80080BDC; break;
        case 12: arg0 = 6; var_a1 = D_80080BE4; break;
        case 13: arg0 = 6; var_a1 = D_80080BEC; break;
        }
        break;
    case 2:
        arg0 = 6; var_a1 = D_80080BF4;
        break;
    case 3:
        switch (D_800136B8[0]) {
        default: arg0 = 6; ASM_KEEP_OLD(arg0); var_a1 = D_80080BFC; break;
        case 11: arg0 = 6; var_a1 = D_80080C04; break;
        case 12: arg0 = 6; var_a1 = D_80080C0C; break;
        case 13: arg0 = 6; var_a1 = D_80080C14; break;
        }
        break;
    }

    func_8003E4FC(arg0, var_a1, 0);
    func_8003E4FC(0xFF, func_8003E140, &sp10);
    func_8003F320();
    func_80041344((void *)0x80020000, D_80081480_4[0]);
    DrawSync(0);
    {
        register u8 *base ASM_REG("$3") = D_800D2FB4;
        register u32 addr ASM_REG("$2");
        register u8 *arg1 ASM_REG("$5");
        u8 value;

        ASM_KEEP_OLD(base);
        addr = D_800D381A[0];
        ASM_KEEP_OLD(addr);
        arg1 = (u8 *)0x80130000;
        ASM_KEEP_OLD(arg1);
        addr = (addr << 5) + (u32)base;
        value = *(u8 *)addr;
        func_80046E38(value, arg1 - 0xFFC);
    }
}

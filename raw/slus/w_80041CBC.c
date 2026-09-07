#include "common.h"

#include "common.h"

extern void PutDispEnv(void *env);
extern void PutDrawEnv(void *env);
extern void DrawOTag(void *ot);
extern void ClearOTagR(void *ot, s32 n);
extern void DrawSync(s32 mode);
extern s32 GetRCnt(s32 counter);
extern void ResetRCnt(s32 counter);
extern void VSync(s32 mode);

extern void func_8003E2D8(void);
extern void func_8003E758(void);
extern void func_8003F6F4(void);
extern void func_800411AC(void);
extern void func_80048B28(void);
extern void func_800542BC(void);
extern void func_800894A0(void);

extern u16 D_80013714;
extern u8 D_80080A84;
extern u8 D_80080A85;
extern s8 D_80080A87;
extern s32 D_80081480;
extern s32 D_8008148C;
extern void *D_80083160;
extern u8 D_801C9E40;

void func_80041CBC(void)
{
    register s32 zero ASM_REG("$0");
    register s32 copied ASM_REG("$2");
    register void *current ASM_REG("$3");
    register u8 *page ASM_REG("$2");
    register u8 *mode_addr ASM_REG("$4");
    u8 *next;
    void *ot;
    s32 timer;
    u16 sync_flags;

    PutDispEnv((u8 *)D_80083160 + 0x5C);
    PutDrawEnv(D_80083160);
    if (!(D_80013714 & 2)) {
        ASM_KEEP(zero);
        DrawOTag((u8 *)D_80083160 + 0x8CC);
    }
    func_8003E758();
    func_800542BC();
    ASM_KEEP(zero);
    copied = D_8008148C;
#ifdef NON_MATCHING
    D_80081480 = copied;
#else
    {
        register s32 *copy_out ASM_REG("$1");
        copy_out = (s32 *)0x80080000;
        copy_out[0x520] = copied;
        ASM_KEEP(copy_out);
    }
#endif
    ASM_KEEP(zero);
    func_800411AC();
    func_8003E2D8();
    ASM_KEEP(zero);

#ifdef NON_MATCHING
    next = &D_801C9E40;
    current = D_80083160;
#else
    page = (u8 *)0x801D0000;
    ASM_KEEP(page);
    current = D_80083160;
    ASM_KEEP(page);
    next = page - 0x61C0;
    ASM_KEEP(next);
#endif
    ot = next + 0x70;
    if (current == next) {
        next += 0x108D4;
        ot = next + 0x70;
    }
    do { D_80083160 = next; } while (0);
    ClearOTagR(ot, 0x218);
    *(void **)((u8 *)D_80083160 + 0x8D0) =
        (u8 *)D_80083160 + 0x8D4;
    func_8003F6F4();
    func_800894A0();
    ASM_KEEP(zero);
    if (!(D_80013714 & 2)) {
        DrawSync(0);
    }
    func_80048B28();
    DrawSync(0);
    ASM_KEEP(zero);
    timer = GetRCnt(1) + 0xFF;
    sync_flags = *(volatile u16 *)&D_80013714;
    timer >>= 8;
#ifdef NON_MATCHING
    *(volatile s8 *)&D_80080A87 = (s8)timer;
#else
    {
        register s8 *timer_out ASM_REG("$1");
        timer_out = (s8 *)0x80080000;
        timer_out[0xA87] = (s8)timer;
    }
#endif
    if (!(sync_flags & 2)) {
        ASM_KEEP(zero);
        if (D_80080A85 == 0) {
            ASM_KEEP(zero);
#ifdef NON_MATCHING
            VSync((D_80080A84 != 1) * 2);
#else
            mode_addr = (u8 *)0x80080000;
            ASM_KEEP(mode_addr);
            VSync((mode_addr[0xA84] != 1) * 2);
#endif
        }
    }
    ResetRCnt(1);
}

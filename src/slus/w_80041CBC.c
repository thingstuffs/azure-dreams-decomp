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

/* Present the frame, switch draw buffers, and synchronize frame timing. */
void func_80041CBC(void)
{
    s32 zero = 0;
    s32 copied_value;
    void *current_buffer;
    u8 *buffer_page;
    register u8 *vsync_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *next_buffer;
    void *ordering_table;
    s32 frame_ticks;
    u16 sync_flags;

    PutDispEnv((u8 *)D_80083160 + 0x5C);
    PutDrawEnv(D_80083160);
    if (!(D_80013714 & 2)) {
        DrawOTag((u8 *)D_80083160 + 0x8CC);
    }
    func_8003E758();
    func_800542BC();
    copied_value = D_8008148C;
#ifdef NON_MATCHING
    D_80081480 = copied_value;
#else
    {
        register s32 *state_page ASM_REG("$1");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        state_page = (s32 *)0x80080000;
        state_page[0x520] = copied_value;
    }
#endif
    func_800411AC();
    func_8003E2D8();

#ifdef NON_MATCHING
    next_buffer = &D_801C9E40;
    current_buffer = D_80083160;
#else
    buffer_page = (u8 *)0x801D0000;
    current_buffer = D_80083160;
    ASM_KEEP(buffer_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    next_buffer = buffer_page - 0x61C0;
    ASM_KEEP(next_buffer);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
#endif
    ordering_table = next_buffer + 0x70;
    if (current_buffer == next_buffer) {
        next_buffer += 0x108D4;
        ordering_table = next_buffer + 0x70;
    }
    D_80083160 = next_buffer;
    ClearOTagR(ordering_table, 0x218);
    *(void **)((u8 *)D_80083160 + 0x8D0) =
        (u8 *)D_80083160 + 0x8D4;
    func_8003F6F4();
    func_800894A0();
    if (!(D_80013714 & 2)) {
        DrawSync(0);
    }
    func_80048B28();
    DrawSync(0);
    frame_ticks = GetRCnt(1) + 0xFF;
    sync_flags = *(volatile u16 *)&D_80013714;
    frame_ticks >>= 8;
#ifdef NON_MATCHING
    *(volatile s8 *)&D_80080A87 = (s8)frame_ticks;
#else
    {
        s8 *timer_page;
        timer_page = (s8 *)0x80080000;
        timer_page[0xA87] = (s8)frame_ticks;
    }
#endif
    if (!(sync_flags & 2)) {
        ASM_KEEP(zero);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (D_80080A85 == 0) {
#ifdef NON_MATCHING
            VSync((D_80080A84 != 1) * 2);
#else
            vsync_page = (u8 *)0x80080000;
            VSync((vsync_page[0xA84] != 1) * 2);
#endif
        }
    }
    ResetRCnt(1);
}

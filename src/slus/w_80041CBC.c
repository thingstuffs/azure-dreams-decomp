#include "common.h"
#include "shared/game_work.h"

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

extern u8 D_80080A84;
extern u8 D_80080A85;
extern s8 D_80080A87;
extern s32 D_80081480;
extern s32 D_8008148C;
extern u8 D_801C9E40[];
extern u16 D_80013714[];

/* Present the frame, switch draw buffers, and synchronize frame timing. */
void func_80041CBC(void)
{
    s32 copied_value;
    void *current_buffer;
    u8 *next_buffer;
    void *ordering_table;
    s32 frame_ticks;
    u16 sync_flags;

    PutDispEnv((u8 *)gameWork.unk_000 + 0x5C);
    PutDrawEnv(gameWork.unk_000);
    if (!(D_80013714[0] & 2)) {
        DrawOTag((u8 *)gameWork.unk_000 + 0x8CC);
    }
    func_8003E758();
    func_800542BC();
    copied_value = D_8008148C;
    D_80081480 = copied_value;
    func_800411AC();
    func_8003E2D8();

    next_buffer = D_801C9E40;
    current_buffer = gameWork.unk_000;
    if (current_buffer == next_buffer) {
        next_buffer += 0x108D4;
    }
    ordering_table = next_buffer + 0x70;
    gameWork.unk_000 = next_buffer;
    ClearOTagR(ordering_table, 0x218);
    *(void **)((u8 *)gameWork.unk_000 + 0x8D0) =
        (u8 *)gameWork.unk_000 + 0x8D4;
    func_8003F6F4();
    func_800894A0();
    if (!(D_80013714[0] & 2)) {
        DrawSync(0);
    }
    func_80048B28();
    DrawSync(0);
    frame_ticks = GetRCnt(1) + 0xFF;
    sync_flags = D_80013714[0];
    frame_ticks >>= 8;
    D_80080A87 = (s8)frame_ticks;
    if (!(sync_flags & 2)) {
        if (D_80080A85 == 0) {
            VSync((D_80080A84 != 1) * 2);
        }
    }
    ResetRCnt(1);
}

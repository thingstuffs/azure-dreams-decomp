#include "common.h"

extern void ClearImage(void *, s32, s32, s32);
extern void initDoubleBufferedGpuEnvironments(void);
extern void func_8004EB30(void);
extern void ResetCallback(void);
extern s32 D_80080A7C;
extern s32 D_80081480;
extern s32 D_8008148C;
extern u8 D_80126804[];

/* Reset callbacks, clear VRAM, and initialize buffer state. */
void resetCallbacksAndClearVram(void)
{
    s32 vram_rect[2];

    ResetCallback();
    func_8004EB30();
    initDoubleBufferedGpuEnvironments();
    vram_rect[0] = 0;
    vram_rect[1] = 0x02000400;
    ClearImage(vram_rect, 0, 0, 0);
    D_8008148C = (s32) D_80126804;
    D_80081480 = (s32) D_80126804;
    D_80080A7C = 0x38000;
}

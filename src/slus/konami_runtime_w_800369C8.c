#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x8D0];
    u8 *nextPrim;
} Func800369C8_State;

typedef struct {
    u16 r0;
    u16 r1;
    u16 r2;
    u16 r3;
} Func800369C8_DrawMode;

extern Func800369C8_State *D_80083160[3];
extern u16 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetDrawMode(void *p, s32 dfe, s32 abe, u16 tpage,
                        Func800369C8_DrawMode *env);
extern void AddPrim(void *ot, void *p);

/* Queue a draw mode primitive with a 64-by-32 texture window at the given ordering table index. */
void func_800369C8(s32 ot_index)
{
    void *draw_mode;
    Func800369C8_DrawMode texture_window;

    draw_mode = D_80083160[0]->nextPrim;
    D_80083160[0]->nextPrim = (u8 *)draw_mode + 0xC;

    texture_window.r0 = 0;
    texture_window.r1 = 0;
    texture_window.r2 = 0x40;
    texture_window.r3 = 0x20;
    SetDrawMode(draw_mode, 0, 0, GetTPage(0, 0, 0x1C0, 0x100), &texture_window);
    AddPrim((u8 *)D_80083160[0] + 0x70 + (ot_index << 2), draw_mode);
}

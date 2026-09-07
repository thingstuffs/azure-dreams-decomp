#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x8D0];
    u8 *nextPrim;
} Func80036A70_State;

typedef struct {
    u16 r0;
    u16 r1;
    u16 r2;
    u16 r3;
} Func80036A70_DrawMode;

extern Func80036A70_State *D_80083160[3];
extern u16 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetDrawMode(void *p, s32 dfe, s32 abe, u16 tpage,
                        Func80036A70_DrawMode *env);
extern void AddPrim(void *ot, void *p);

void func_80036A70(s32 arg0)
{
    void *prim;
    Func80036A70_DrawMode env;

    prim = D_80083160[0]->nextPrim;
    D_80083160[0]->nextPrim = (u8 *)prim + 0xC;

    env.r0 = 0;
    env.r1 = 0;
    env.r2 = 0;
    env.r3 = 0;
    SetDrawMode(prim, 0, 0, GetTPage(0, 0, 0x1C0, 0x100), &env);
    AddPrim((u8 *)D_80083160[0] + 0x70 + (arg0 << 2), prim);
}

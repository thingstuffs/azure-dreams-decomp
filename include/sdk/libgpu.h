/* Stand-in declarations for the Psy-Q SDK library libgpu. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */
/* Generated call contracts; maintained by tools/headers. */
#ifndef SDK_LIBGPU_H
#define SDK_LIBGPU_H

#include "common.h"

void AddPrim(void *, void *);
s32 ClearImage(void *, u8, u8, u8);
u32 * ClearOTagR(u32 *, s32);
void DrawOTag(void *);
void DrawPrim(void *);
s32 DrawSync(s32);
u16 GetClut(s32, s32);
u16 GetTPage(s32, s32, s32, s32);
s32 LoadImage(void *, u32 *);
s32 MoveImage(void *, s32, s32);
void * PutDispEnv(void *);
void * PutDrawEnv(void *);
s32 ResetGraph(s32);
void * SetDefDispEnv(void *, s32, s32, s32, s32);
void * SetDefDrawEnv(void *, s32, s32, s32, s32);
s32 SetDispMask(s32);
void SetDrawMode(void *, s32, s32, s32, void *);
s32 SetGraphDebug(s32);
void SetPolyF4(void *);
void SetPolyFT4(void *);
void SetPolyG4(void *);
void SetSemiTrans(void *, s32);
void SetSprt(void *);
void SetTile(void *);
s32 StoreImage(void *, u32 *);
u16 LoadTPage(u32 *, s32, s32, s32, s32, s32, s32);
u16 func_80066460(s32, s32, s32, s32);
void SetShadeTex(void *, s32);
void SetPolyF3(void *);
void SetPolyG3(void *);
void SetPolyGT4(void *);
void SetLineF2(void *);
void SetLineG2(void *);
void SetLineG4(void *);
void SetDrawArea(void *, void *);

#endif

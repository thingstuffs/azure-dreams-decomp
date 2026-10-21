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
u16 func_800661B0(u32 *, s32, s32, s32, s32, s32, s32);
u16 func_80066460(s32, s32, s32, s32);
u16 func_8006649C(s32, s32);
void func_8006658C(void *, void *);
void func_80066640(void *, s32);
void func_80066668(void *, s32);
void func_80066690(void *);
void func_800666B8(void *);
void func_800666E0(void *);
void func_800666F4(void *);
void func_80066708(void *);
void func_8006671C(void *);
void func_80066758(void *);
void func_800667A8(void *);
void func_800667BC(void *);
void func_800667D0(void *);
void func_80066844(void *);
s32 func_80066F78(s32);
s32 func_80067014(s32);
s32 func_800671A8(void *, u8, u8, u8);
s32 func_800672D8(void *, u32 *);
s32 func_8006733C(void *, u32 *);
s32 func_800673A0(void *, s32, s32);
void func_80067E2C(void *, void *);
void func_80067F20(void *, s32, s32, s32, void *);

#endif

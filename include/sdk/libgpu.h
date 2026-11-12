/* Stand-in declarations for the Psy-Q SDK library libgpu. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */
/* Generated call contracts; maintained by tools/headers. */
#ifndef SDK_LIBGPU_H
#define SDK_LIBGPU_H

#include "common.h"

/* Psy-Q record types (include/sdk/libgpu_types.h and libgpu_packets.h define them). */
struct RECT;
struct DR_MODE;
struct POLY_F4;
struct POLY_FT4;
struct POLY_G3;
struct POLY_G4;

void AddPrim(void *, void *);
s32 ClearImage(struct RECT *, u8, u8, u8);
u32 * ClearOTagR(u32 *, s32);
void DrawOTag(void *);
void DrawPrim(void *);
s32 DrawSync(s32);
u16 GetClut(s32, s32);
u16 GetTPage(s32, s32, s32, s32);
s32 LoadImage(struct RECT *, u32 *);
s32 MoveImage(struct RECT *, s32, s32);
void * PutDispEnv(void *);
void * PutDrawEnv(void *);
s32 ResetGraph(s32);
void * SetDefDispEnv(void *, s32, s32, s32, s32);
void * SetDefDrawEnv(void *, s32, s32, s32, s32);
s32 SetDispMask(s32);
void SetDrawMode(struct DR_MODE *, s32, s32, s32, struct RECT *);
s32 SetGraphDebug(s32);
void SetPolyF4(struct POLY_F4 *);
void SetPolyFT4(struct POLY_FT4 *);
void SetPolyG4(struct POLY_G4 *);
void SetSemiTrans(void *, s32);
void SetSprt(void *);
void SetTile(void *);
s32 StoreImage(struct RECT *, u32 *);
u16 LoadTPage(u32 *, s32, s32, s32, s32, s32, s32);
u16 func_80066460(s32, s32, s32, s32);
void SetShadeTex(void *, s32);
void SetPolyF3(void *);
void SetPolyG3(struct POLY_G3 *);
void SetPolyGT4(void *);
void SetLineF2(void *);
void SetLineG2(void *);
void SetLineG4(void *);
void SetDrawArea(void *, struct RECT *);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void SetTexWindow(void *, struct RECT *);

#endif

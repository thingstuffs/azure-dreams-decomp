/* Stand-in declarations for the Psy-Q SDK library libgte. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */
/* Generated call contracts; maintained by tools/headers. */
#ifndef SDK_LIBGTE_H
#define SDK_LIBGTE_H

#include "common.h"

void * ApplyMatrixSV(void *, void *, void *);
void * CompMatrix(void *, void *, void *);
void InitGeom(void);
s32 NormalClip(s32, s32, s32);
void PopMatrix(void);
void PushMatrix(void);
void * ReadRotMatrix(void *);
s32 RotAverage4(void *, void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
void * RotMatrix(void *, void *);
void RotTrans(void *, void *, s32 *);
s32 RotTransPers(void *, s32 *, s32 *, s32 *);
s32 RotTransPers4(void *, void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
void * ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
void * TransMatrix(void *, void *);
void * TransposeMatrix(void *, void *);
s32 rsin(s32);
s32 rcos(s32);
void SetFogFar(s32, s32);
s32 SquareRoot0(s32);
s32 SquareRoot12(s32);
void SetLightMatrix(void *);
void SetColorMatrix(void *);
void SetBackColor(s32, s32, s32);
void SetFarColor(s32, s32, s32);
void SetGeomOffset(s32, s32);
void SetGeomScreen(s32);
void * RotMatrixX(s32, void *);
void * RotMatrixY(s32, void *);
void * RotMatrixZ(s32, void *);
s32 ratan2(s32, s32);

#endif

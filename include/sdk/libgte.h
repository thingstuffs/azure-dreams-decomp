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
s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_80064624(s32, s32);
s32 func_80064710(s32);
s32 func_800647A0(s32);
void * func_80064840(void *, void *, void *);
void func_800649A0(void);
void func_80064A40(void);
void * func_80064AE0(void *);
void * func_80064B30(void *, void *, void *);
void * func_80064B90(void *, void *);
void * func_80064BC0(void *, void *);
void func_80064CF0(void *);
void func_80064D20(void *);
void func_80064D50(void *);
void func_80064D80(void *);
void func_80064EC0(s32, s32, s32);
void func_80064EE0(s32, s32, s32);
void func_80064F00(s32, s32);
void func_80064F20(s32);
s32 func_80065420(void *, s32 *, s32 *, s32 *);
void func_80065450(void *, void *, s32 *);
s32 func_80065480(s32, s32, s32);
s32 func_800654B0(void *, void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
s32 func_80065590(void *, void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
void * func_80065820(void *, void *);
void * func_80065AB0(s32, void *);
void * func_80065C50(s32, void *);
void * func_80065DF0(s32, void *);
s32 func_80065F90(s32, s32);
s32 ratan2(s32, s32);
s32 rcos(s32);
s32 rsin(s32);

#endif

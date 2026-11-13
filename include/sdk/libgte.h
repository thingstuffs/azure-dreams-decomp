/* Stand-in declarations for the Psy-Q SDK library libgte. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */
/* Generated call contracts; maintained by tools/headers. */
#ifndef SDK_LIBGTE_H
#define SDK_LIBGTE_H

#include "common.h"

/* Psy-Q record types (include/sdk/libgte_matrix.h defines them). */
struct MATRIX;
struct VECTOR;
struct SVECTOR;
struct CVECTOR;

struct SVECTOR * ApplyMatrixSV(struct MATRIX *, struct SVECTOR *, struct SVECTOR *);
struct MATRIX * CompMatrix(struct MATRIX *, struct MATRIX *, struct MATRIX *);
void InitGeom(void);
s32 NormalClip(s32, s32, s32);
void PopMatrix(void);
void PushMatrix(void);
struct MATRIX * ReadRotMatrix(struct MATRIX *);
s32 RotAverage4(struct SVECTOR *, struct SVECTOR *, struct SVECTOR *, struct SVECTOR *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
struct MATRIX * RotMatrix(struct SVECTOR *, struct MATRIX *);
void RotTrans(struct SVECTOR *, struct VECTOR *, s32 *);
s32 RotTransPers(struct SVECTOR *, s32 *, s32 *, s32 *);
s32 RotTransPers4(struct SVECTOR *, struct SVECTOR *, struct SVECTOR *, struct SVECTOR *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
struct MATRIX * ScaleMatrix(struct MATRIX *, struct VECTOR *);
void SetRotMatrix(struct MATRIX *);
void SetTransMatrix(struct MATRIX *);
struct MATRIX * TransMatrix(struct MATRIX *, struct VECTOR *);
struct MATRIX * TransposeMatrix(struct MATRIX *, struct MATRIX *);
s32 rsin(s32);
s32 rcos(s32);
void SetFogFar(s32, s32);
s32 SquareRoot0(s32);
s32 SquareRoot12(s32);
void SetLightMatrix(struct MATRIX *);
void SetColorMatrix(struct MATRIX *);
void SetBackColor(s32, s32, s32);
void SetFarColor(s32, s32, s32);
void SetGeomOffset(s32, s32);
void SetGeomScreen(s32);
struct MATRIX * RotMatrixX(s32, struct MATRIX *);
struct MATRIX * RotMatrixY(s32, struct MATRIX *);
struct MATRIX * RotMatrixZ(s32, struct MATRIX *);
s32 ratan2(s32, s32);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void NormalColorCol(struct SVECTOR *, struct CVECTOR *, struct CVECTOR *);
s32 ReadGeomScreen(void);

void RotTransSV(struct SVECTOR *, struct SVECTOR *, s32 *);

#endif

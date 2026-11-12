#ifndef SDK_LIBGTE_MATRIX_H
#define SDK_LIBGTE_MATRIX_H

#include "common.h"

/* Psy-Q rotation matrix: the translation words begin at offset 0x14. */
typedef struct MATRIX {
    s16 m[3][3];
    s32 t[3];
} MATRIX;

/* Psy-Q long vector: the translation and scale argument of TransMatrix and ScaleMatrix. */
typedef struct VECTOR {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} VECTOR;

/* Psy-Q short vector: the rotation angles of RotMatrix and the vertices of RotTransPers and RotAverage4. */
typedef struct SVECTOR {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVECTOR;

/* Psy-Q colour vector: red, green, blue and GPU code bytes (NormalColorCol). */
typedef struct CVECTOR {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} CVECTOR;

#endif

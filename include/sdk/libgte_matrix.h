#ifndef SDK_LIBGTE_MATRIX_H
#define SDK_LIBGTE_MATRIX_H

#include "common.h"

/* Psy-Q rotation matrix: the translation words begin at offset 0x14. */
typedef struct MATRIX {
    s16 m[3][3];
    s32 t[3];
} MATRIX;

#endif

#ifndef SDK_LIBGTE_MATRIX_H
#define SDK_LIBGTE_MATRIX_H

/* Psy-Q rotation matrix: the translation words begin at offset 0x14. */
typedef struct MATRIX {
    short m[3][3];
    int t[3];
} MATRIX;

/* Psy-Q long vector: the translation and scale argument of TransMatrix and ScaleMatrix. */
typedef struct VECTOR {
    int vx;
    int vy;
    int vz;
    int pad;
} VECTOR;

/* Psy-Q short vector: the rotation angles of RotMatrix and the vertices of RotTransPers and RotAverage4. */
typedef struct SVECTOR {
    short vx;
    short vy;
    short vz;
    short pad;
} SVECTOR;

/* Psy-Q colour vector: red, green, blue and GPU code bytes (NormalColorCol). */
typedef struct CVECTOR {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char cd;
} CVECTOR;

#endif

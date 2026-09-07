#include "common.h"

typedef struct {
    s16 m[3][3];
    s32 t[3];
} S_8003E0C4_MATRIX;

typedef struct {
    s16 vx, vy, vz, pad;
} S_8003E0C4_SVECTOR;

typedef struct {
    s32 vx, vy, vz;
} S_8003E0C4_VECTOR;

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void SetRotMatrix(S_8003E0C4_MATRIX *m);
extern void SetTransMatrix(S_8003E0C4_MATRIX *m);
extern void RotTrans(S_8003E0C4_SVECTOR *v0, S_8003E0C4_VECTOR *v1, s32 *flag);

/* Pushes the matrix stack, sets translation/rotation from *m, transforms
 * v0/v1 through the GTE (RotTrans), discarding the overflow flag, then pops
 * the matrix stack back. */
void func_8003E0C4(S_8003E0C4_MATRIX *m, S_8003E0C4_SVECTOR *v0, S_8003E0C4_VECTOR *v1) {
    s32 flag;

    PushMatrix();
    SetTransMatrix(m);
    SetRotMatrix(m);
    RotTrans(v0, v1, &flag);
    PopMatrix();
}

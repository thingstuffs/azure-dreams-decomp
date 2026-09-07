#include "common.h"

#include "common.h"

#include "common.h"

typedef struct
{
  s16 m[3][3];
  s32 t[3];
} MATRIX;

typedef struct
{
  s16 vx;
  s16 vy;
  s16 vz;
  s16 pad;
} SVECTOR;

typedef struct
{
  s32 vx;
  s32 vy;
  s32 vz;
} VECTOR;

/* D_80083178 is declared canonically (include/globals.h -> include/game.h). The
 * game.h struct doesn't expose the SVECTOR sub-fields this function needs, so use
 * the same local-cast reconcile the landed twin func_8004D294 uses
 * (src/w_8004D294.c:25): a private S_80083178_local layout cast over &D_80083178. */
typedef struct
{
  char pad0[0x94];
  SVECTOR field_94;
  SVECTOR field_9C;
  short f_A4;
  short f_A6;
  short f_A8;
  char pad_aa[0xAC - 0xAA];
  SVECTOR field_AC;
  void (*callback)(void);
  void *field_B8;
  char pad_bc[(0xD8 - 0xB8) - 4];
  void *ptr;
  char pad_dc[0x1C4 - 0xDC];
} S_80083178_local;

extern void RotMatrix(SVECTOR *r, MATRIX *m);
extern void SetRotMatrix(MATRIX *m);
extern void SetTransMatrix(MATRIX *m);
extern void TransMatrix(MATRIX *m, VECTOR *v);
extern void RotTrans(SVECTOR *v0, VECTOR *v1, s32 *flg);
extern void CompMatrix(MATRIX *m0, MATRIX *m1, MATRIX *m2);
extern void func_80041900(MATRIX *m);

void func_8004D4AC(void)
{
  S_80083178_local *p = (S_80083178_local *)&D_80083178;
  VECTOR vec;
  MATRIX matB;
  MATRIX matC;
  MATRIX matA;
  MATRIX *new_var;
  SVECTOR svec;
  s32 flag;
  matA.t[2] = 0;
  matA.t[1] = 0;
  matA.t[0] = 0;
  matB.t[2] = 0;
  new_var = &matA;
  matB.t[1] = 0;
  matB.t[0] = 0;
  RotMatrix(&p->field_AC, &matA);
  SetRotMatrix(new_var);
  SetTransMatrix(&matA);
  svec.vx = -p->f_A4;
  svec.vy = -p->f_A6;
  svec.vz = -p->f_A8;
  RotTrans(&svec, &vec, &flag);
  TransMatrix(&matA, &vec);
  RotMatrix(&p->field_9C, &matB);
  SetRotMatrix(&matB);
  SetTransMatrix(&matB);
  RotTrans(&p->field_94, &vec, &flag);
  TransMatrix(&matB, &vec);
  func_80041900(&matB);
  CompMatrix(&matB, &matA, &matC);
  SetTransMatrix(&matC);
  SetRotMatrix(&matC);
}
